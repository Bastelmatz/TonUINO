
#include "Tonuino_DFPlayer.h"

TonuinoPlayer TonuinoDFPlayer::tonuinoPlayer;

uint8_t TonuinoDFPlayer::pin_Busy = 0;
bool TonuinoDFPlayer::hasGB32000B = false;
uint8_t TonuinoDFPlayer::activeFolder = 0;
uint16_t TonuinoDFPlayer::activeTrack = 0;
uint8_t TonuinoDFPlayer::lastStartedFolder = 0;
uint16_t TonuinoDFPlayer::lastStartedTrack = 0;
uint32_t TonuinoDFPlayer::timeLastFinished = 0;

uint8_t TonuinoDFPlayer::volume = 0;
uint8_t TonuinoDFPlayer::volumeMin = 0;
uint8_t TonuinoDFPlayer::volumeMax = 25;
uint8_t TonuinoDFPlayer::volumeIncrement = 1;

MusicDataset TonuinoDFPlayer::currentMusicDS = { 0 };
uint8_t TonuinoDFPlayer::currentMusicFolder = 0;
uint16_t TonuinoDFPlayer::numTracksInFolder = 0;
bool TonuinoDFPlayer::musicDSLoaded = false;
bool TonuinoDFPlayer::newMusisDS = false;

bool TonuinoDFPlayer::freezeDance_active = false;
unsigned long TonuinoDFPlayer::freezeDance_nextStopAtMillis = 0;

bool TonuinoDFPlayer::memoryMode_active = false;
bool TonuinoDFPlayer::quizMode_active = false;
bool TonuinoDFPlayer::playCompareTrack = false;

#define PLAYTRACK_DELAY 1000

static const uint8_t FOLDERCODE_MP3 = 0;
static const uint8_t FOLDERCODE_ADVERTISEMENT = 100;

static const uint8_t TRACKNUMBER_SILENCE = 0;

// ********************************************************************
// implement a notification class, its member methods will get called
// ********************************************************************
void TonuinoDFPlayer::Mp3Notify::OnError(uint16_t errorCode) 
{
	// see DfMp3_Error for code meaning
	Serial.print(F("DFPlayer Com Error "));
	Serial.println(errorCode);
}
void TonuinoDFPlayer::Mp3Notify::PrintlnSourceAction(DfMp3_PlaySources source, const char* action) 
{
	if (source & DfMp3_PlaySources_Sd) Serial.print(F("SD Karte "));
	if (source & DfMp3_PlaySources_Usb) Serial.print(F("USB "));
	if (source & DfMp3_PlaySources_Flash) Serial.print(F("Flash "));
	Serial.println(action);
}
void TonuinoDFPlayer::Mp3Notify::OnPlayFinished(DfMp3_PlaySources source, uint16_t track) 
{
	TonuinoDFPlayer().trackFinished();
}
void TonuinoDFPlayer::Mp3Notify::OnPlaySourceOnline(DfMp3_PlaySources source) 
{
	PrintlnSourceAction(source, "online");
}
void TonuinoDFPlayer::Mp3Notify::OnPlaySourceInserted(DfMp3_PlaySources source) 
{
	PrintlnSourceAction(source, "bereit");
}
void TonuinoDFPlayer::Mp3Notify::OnPlaySourceRemoved(DfMp3_PlaySources source) 
{
	PrintlnSourceAction(source, "entfernt");
}
// ********************************************************************

static SoftwareSerial playerSoftwareSerial = SoftwareSerial(2, 3); // TX, RX
static DFMiniMp3<SoftwareSerial, TonuinoDFPlayer::Mp3Notify> mp3(playerSoftwareSerial);
	
void TonuinoDFPlayer::setup(uint8_t pinBusy, bool hasChip_GB32000B)
{
	pin_Busy = pinBusy;
	hasGB32000B = hasChip_GB32000B;
	
	pinMode(pinBusy, INPUT);
	
	// DFPlayer Mini initialisieren
	mp3.begin();
	// Zwei Sekunden warten bis der DFPlayer Mini initialisiert ist
	delay(2000);
	
	tonuinoPlayer.pauseAndStandBy();
}

bool TonuinoDFPlayer::isPlaying() 
{
	return !digitalRead(pin_Busy);
}

void TonuinoDFPlayer::playMp3Track(uint16_t track)
{
	playTrack(FOLDERCODE_MP3, track);
	
}

void TonuinoDFPlayer::playMP3AndWait(uint16_t track)
{
	playMp3Track(track);
	waitForTrackToFinish();
}

void TonuinoDFPlayer::playTrack(uint8_t folder, uint16_t track)
{
	Serial.print(F("Play track "));
	Serial.print(track);
	Serial.print(F(" from folder "));
	Serial.println(folder);
	lastStartedFolder = folder;
	lastStartedTrack = track;
	if (folder == FOLDERCODE_ADVERTISEMENT)
	{
		mp3.playAdvertisement(track);
	}
	else
	{
		if (folder == 0 || folder == FOLDERCODE_MP3)
		{
			mp3.playMp3FolderTrack(track);
		}
		else
		{
			activeFolder = folder;
			activeTrack = track;
			if (track > 255)
			{
				if (folder > 0 && folder < 16)
				{
					mp3.playFolderTrack16(folder, track);
				}
				else
				{
					Serial.print(F("No large file support for that folder"));
				}
			}
			else
			{
				mp3.playFolderTrack(folder, track);
			}
			delay(PLAYTRACK_DELAY);
		}
	}
}

void TonuinoDFPlayer::playTrack(uint16_t track)
{
	if (track > 0)
	{ 
		playTrack(currentMusicFolder, track);
		tonuinoPlayer.playTitle();
		newMusisDS = false;
	}
}

void TonuinoDFPlayer::playCurrentTrack()
{  
    uint16_t track = tonuinoPlayer.currentTrack();
	playTrack(track);
}

ECOMPARERESULT TonuinoDFPlayer::playOrCompareTrack(MusicDataset * compareMusicDS, bool isNewCard, bool isCardGone, bool stopOnCardRemoval)
{
	uint8_t mode = compareMusicDS->mode;
	uint16_t currentTrack = tonuinoPlayer.currentTrack();
	bool activeMemoryOrQuiz = memoryMode_active || quizMode_active;
	bool match = currentTrack == compareMusicDS->startTrack && (currentMusicFolder == compareMusicDS->startFolder || currentMusicFolder == compareMusicDS->endFolder);
	bool useCompareFolder = playCompareTrack && (!memoryMode_active || isNewCard); // repeat first track on card return with active memory mode 
	bool isCardReturn = !isNewCard && !isCardGone;
	bool isFixPair = mode == UniDirectionalPair || mode == BiDirectionalPair;
	bool isRandomPair = mode == RandomUniDirectionalPair || mode == RandomBiDirectionalPair || mode == Section_RandomUniDirectionalPair || mode == Section_RandomBiDirectionalPair;
	bool isRandomSingle = mode == AudioDrama || mode == Section_AudioDrama;
	bool isAnyPair = isFixPair || isRandomPair;
	
	if (isCardGone)
	{
		// resolve pair (play second track on card removal)
		if (activeMemoryOrQuiz || !isAnyPair)
		{
			if (stopOnCardRemoval)
			{
				pauseAndStandBy();
			}
			return COMPARE_NOTSUPPORTED;
		}
	}
	if (isCardReturn)
	{
		if (!activeMemoryOrQuiz)
		{
			if (mode == RandomFolder_Album || mode == RandomFolder_Party)
			{
				loadAndPlayFolder(compareMusicDS);
				return COMPARE_NO;
			}
			if (!isFixPair)
			{
				if (stopOnCardRemoval || !isPlaying())
				{
					continueTitle();
				}
				else
				{
					nextTrack();
				}
				if (isAnyPair)
				{
					playCompareTrack = true;
				}
				return COMPARE_NO;
			}
		}
		if (quizMode_active)
		{
			if (!playCompareTrack) 
			{
				if (isRandomPair || isRandomSingle) // First quiz track must be random one
				{
					loadAndPlayFolder(compareMusicDS);
					playCompareTrack = true;
				}
				return COMPARE_NO;
			}
		}
	}
	if (isNewCard)
	{
		if (!activeMemoryOrQuiz)
		{
			loadAndPlayFolder(compareMusicDS);
			playCompareTrack = isAnyPair;
			return COMPARE_NO;
		}
		if (!playCompareTrack)
		{
			if (!quizMode_active || (isRandomPair || isRandomSingle)) // First quiz track must be random one
			{
				loadAndPlayFolder(compareMusicDS);
				playCompareTrack = true;
			}
			return COMPARE_NO;
		}
	}

	if (playCompareTrack && activeMemoryOrQuiz)
	{
		// - play match evaluation track (1) before actual compare track (2)
		// - both tracks (1+2) should be played and the first one should be awaited to finish
		// - as the evaluation track is fix and of short length, it doesn't block the loop as long as the compare track could
		playMP3AndWait(match ? 935 : 934);
	}
	tryPlayCompareTrack(compareMusicDS, useCompareFolder, match);
	return useCompareFolder && activeMemoryOrQuiz ? (match ? COMPARE_MATCH : COMPARE_WRONG) : COMPARE_NO;
}

void TonuinoDFPlayer::tryPlayCompareTrack(MusicDataset * compareMusicDS, bool useCompareFolder, bool useMatchingTrack)
{
	bool activeMemoryOrQuiz = memoryMode_active || quizMode_active;
	
	uint16_t track = tonuinoPlayer.currentTrack();
	if (!useMatchingTrack && activeMemoryOrQuiz)
	{
		track = compareMusicDS->startTrack;
	}
	uint8_t mode = compareMusicDS->mode;
	if (mode == Single)
	{
		playTrack(compareMusicDS->startFolder, track);
	}
	if (mode == UniDirectionalPair || mode == RandomUniDirectionalPair || mode == Section_RandomUniDirectionalPair)
	{
		uint8_t folder = useCompareFolder ? compareMusicDS->endFolder : compareMusicDS->startFolder;
		playTrack(folder, track);
	}
	if (mode == BiDirectionalPair || mode == RandomBiDirectionalPair || mode == Section_RandomBiDirectionalPair)
	{
		uint8_t oppositeFolder = currentMusicFolder == compareMusicDS->startFolder ? compareMusicDS->endFolder : compareMusicDS->startFolder;
		uint8_t folder = useCompareFolder ? oppositeFolder : currentMusicFolder;
		playTrack(folder, track);
	}
	
	if (useCompareFolder || !activeMemoryOrQuiz)
	{
		if (!quizMode_active || useMatchingTrack) // for quiz: stay in compare mode until rigth answer was shown (match)
		{
			playCompareTrack = !playCompareTrack;
		}
	}
}

void TonuinoDFPlayer::loadFolder(MusicDataset * dataset, ETRACKDIRECTION trackDir)
{
	bool isFirstLoad = trackDir == TRACKDIR_None;
	uint16_t currentTrack = tonuinoPlayer.currentTrack();
	uint8_t mode = dataset->mode;
	bool randomFolderForNextTrack = (mode == AudioDrama || mode == Party) &&
									dataset->endFolder > dataset->startFolder;
	bool randomFolderForFirstLoad = mode == RandomFolder_Album || 
									mode == RandomFolder_Party;
	bool changeFolderOnLimits = (mode == Album || mode == AudioBook) &&
								 dataset->endFolder > dataset->startFolder;
	bool isBiDirectionalPair = mode == BiDirectionalPair || mode == RandomBiDirectionalPair || mode == Section_RandomBiDirectionalPair;
	
	uint8_t newFolder = currentMusicFolder;
	if (isFirstLoad)
	{
		newFolder = dataset->startFolder;
		uint8_t recentFolder = dataset->recentFolder;
		if (recentFolder > newFolder && recentFolder <= dataset->endFolder)
		{
			newFolder = recentFolder;
		}
	}
	if (isBiDirectionalPair)
	{
		newFolder = random(0, 2) == 0 ? dataset->startFolder : dataset->endFolder;
	}
	if ((randomFolderForNextTrack && trackDir == TRACKDIR_Next)|| 
	    (randomFolderForFirstLoad && isFirstLoad))
	{
		newFolder = random(dataset->startFolder, dataset->endFolder + 1);
	}
	ETRACKDIRECTION newTrackDir = TRACKDIR_None;
	if (changeFolderOnLimits)
	{
		if (trackDir == TRACKDIR_Next && currentTrack == numTracksInFolder)
		{
			newFolder = newFolder < dataset->endFolder ? newFolder + 1 : dataset->startFolder;
			newTrackDir = TRACKDIR_First;
		}
		if (trackDir == TRACKDIR_Previous && currentTrack == 1)
		{
			newFolder = newFolder > dataset->startFolder ? newFolder - 1 : dataset->endFolder;
			newTrackDir = TRACKDIR_Last;
		}
		if (trackDir == TRACKDIR_First)
		{
			newFolder = dataset->startFolder;
			newTrackDir = TRACKDIR_First;
		}
		if (trackDir == TRACKDIR_Last)
		{
			newFolder = dataset->endFolder;
			newTrackDir = TRACKDIR_Last;
		}
	}
	
	bool doLoad = isFirstLoad || newFolder != currentMusicFolder;
	if (doLoad)
	{
		currentMusicFolder = newFolder;
		currentMusicDS = *dataset;
		numTracksInFolder = getFolderTrackCount(currentMusicFolder);
		
		Serial.print(F("Load folder "));
		Serial.print(currentMusicFolder);
		Serial.print(F(" with mode "));
		Serial.println(currentMusicDS.mode);
		tonuinoPlayer.loadFolder(numTracksInFolder, &currentMusicDS);
		musicDSLoaded = true;
		newMusisDS = true;
	}
	if (newTrackDir != TRACKDIR_None)
	{
		tonuinoPlayer.goToTrack(newTrackDir);
	}
}

void TonuinoDFPlayer::reloadFolder(ETRACKDIRECTION trackDir)
{
	loadFolder(trackDir);
}

void TonuinoDFPlayer::loadFolder(MusicDataset * dataset)
{
	playCompareTrack = false;
	loadFolder(dataset, TRACKDIR_None);
}

void TonuinoDFPlayer::loadFolder(ETRACKDIRECTION trackDir)
{
	loadFolder(&currentMusicDS, trackDir);
}

void TonuinoDFPlayer::loadAndPlayFolder(MusicDataset * dataset)
{
	loadFolder(dataset);
	playCurrentTrack();
}

void TonuinoDFPlayer::continueTitle()
{
	if (!musicDSLoaded)
	{
		return;
	}
	if (tonuinoPlayer.currentTrackStarted)
	{
		start(); // Continue
		tonuinoPlayer.playTitle();
	}
	else
	{
		playCurrentTrack();
	}
}

void TonuinoDFPlayer::pauseAndStandBy()
{
	mp3.pause();
	tonuinoPlayer.pauseAndStandBy();
}

void TonuinoDFPlayer::togglePlay()
{
	if (isPlaying()) 
	{
		pauseAndStandBy();
	}
	else 
	{
		continueTitle();
	}
}

void TonuinoDFPlayer::goToTrack(ETRACKDIRECTION trackDir)
{
	if (playCompareTrack)
	{
		if (quizMode_active)
		{
			tryPlayCompareTrack(&currentMusicDS, true, true);
			return;
		}
		playCompareTrack = false;
	}
	if (tonuinoPlayer.goToTrack(trackDir))
	{
		reloadFolder(trackDir);
		playCurrentTrack();
		if (quizMode_active)
		{
			playCompareTrack = true;
		}
	}
}

void TonuinoDFPlayer::nextTrack() 
{
	if (newMusisDS)
	{
		playCurrentTrack();
	}
	else
	{
		goToTrack(TRACKDIR_Next);
	}
}

void TonuinoDFPlayer::previousTrack()
{
	goToTrack(TRACKDIR_Previous);
}

void TonuinoDFPlayer::firstTrack()
{
	goToTrack(TRACKDIR_First);
}

void TonuinoDFPlayer::lastTrack()
{
	goToTrack(TRACKDIR_Last);
}

void TonuinoDFPlayer::trackFinished()
{
	if (hasGB32000B && (lastStartedFolder == FOLDERCODE_ADVERTISEMENT || lastStartedFolder == FOLDERCODE_MP3))
	{
		Serial.print(F("Last started track "));
		Serial.print(lastStartedTrack);
		Serial.print(F(" in folder "));
		Serial.println(lastStartedFolder);
		lastStartedFolder = activeFolder;
		lastStartedTrack = activeTrack;
		return;
	}
	
	Serial.print(F("Active track "));
	Serial.print(activeTrack);
	Serial.print(F(" in folder "));
	Serial.print(activeFolder);
	Serial.print(F(", Current track "));
	Serial.println(tonuinoPlayer.currentTrack());
	
	// Somehow the DFPlayer finished event is raised twice
	// Ignore the second finish event 
	// (every new track would have the play track delay)
	if (millis() - timeLastFinished < PLAYTRACK_DELAY)
	{
		Serial.println(F("Finish event ignored!"));
		return;
	}
	bool isCurrentTrack = activeTrack == tonuinoPlayer.currentTrack();
	activeTrack = 0;
	if (isCurrentTrack)
	{
		tonuinoPlayer.trackFinished();
		if (tonuinoPlayer.isPlaying && musicDSLoaded)
		{
			nextTrack();
		}
	}
	timeLastFinished = millis();
}

void TonuinoDFPlayer::waitForTrackToFinish() 
{
	// give the player some time to actually start the track
	long currentTime = millis();
	#define TIMEOUT 1000
	do 
	{
		mp3.loop();
	} while (!isPlaying() && millis() < currentTime + TIMEOUT);
	delay(1000);
	// now wait until the player is not busy anymore
	Serial.println(F("Wait for track to finish..."));
	do 
	{
		// to do:
		// main controller loop is not handled during wait
		// solution: 
		// - Set an IsWaiting flag here to true
		// - call main controller loop 
		// - Adjust main controller loop: 
		//      - Consider IsWaiting where any cross sequence interaction should be prevented, 
		//        e.g. only allow/call LED animations, but handle no inputs like buttons
		//      - Set IsWaiting to false if DFPlayer IsPlaying is false
		mp3.loop();
	} while (isPlaying());
}


void TonuinoDFPlayer::playAdvertisement(uint16_t advertisement, bool wait)
{
	Serial.print(F("Play advertisement "));
	Serial.println(advertisement);
	bool wasNotPlaying = !isPlaying();
	if (wasNotPlaying) 
	{
		if (hasGB32000B)
		{
			return;
		}
		start();
	}
	playTrack(FOLDERCODE_ADVERTISEMENT, advertisement);
	if (wait)
	{
		waitForTrackToFinish();
	}
	if (wasNotPlaying) 
	{
		delay(100);
		pause();
	}
}

void TonuinoDFPlayer::playAdvertisement(uint16_t advertisement)
{
	playAdvertisement(advertisement, false);
}

void TonuinoDFPlayer::playAdvertisementAndWait(uint16_t advertisement)
{
	playAdvertisement(advertisement, true);
}

void TonuinoDFPlayer::volumeUp()
{
	setVolume(min(volume + volumeIncrement, volumeMax));
}

void TonuinoDFPlayer::volumeDown()
{
	setVolume(max(volume - volumeIncrement, volumeMin));
}

void TonuinoDFPlayer::setVolume(uint8_t vol)
{
	if (vol < volumeMin || vol > volumeMax)
	{
		return;
	}
	if (volume != vol)
	{
		volume = vol;
		mp3.setVolume(volume);
		Serial.print(F("Volume: "));
		Serial.println(volume);
	}
}

void TonuinoDFPlayer::setEqualizer(DfMp3_Eq eq)
{
	mp3.setEq(eq);
}

void TonuinoDFPlayer::start()
{
	if (!isPlaying())
	{
		Serial.println(F("Start player"));
		mp3.start();
		delay(800);
	}
}

void TonuinoDFPlayer::setNextStopAtMillis() 
{
	uint16_t seconds = random(5, 30 + 1);
	Serial.print(F("Freeze dance - next stop in seconds: "));
	Serial.println(seconds);
	freezeDance_nextStopAtMillis = millis() + seconds * 1000;
}
	
void TonuinoDFPlayer::setFreezeDance(bool active)
{
	freezeDance_active = active;
	if (active)
	{
		playAdvertisementAndWait(300);
		delay(500);
		setNextStopAtMillis();
	}
}

void TonuinoDFPlayer::setMemoryMode(bool active)
{
	memoryMode_active = active;
	playAdvertisementAndWait(active ? 261 : 260);
	playCompareTrack = false;
}

void TonuinoDFPlayer::setQuizMode(bool active)
{
	quizMode_active = active;
	playAdvertisementAndWait(active ? 261 : 260);
	playCompareTrack = false;
}

void TonuinoDFPlayer::loop()
{
	if (freezeDance_active)
	{
		if (millis() > freezeDance_nextStopAtMillis) 
		{
			Serial.println(F("Freeze - pause playing ..."));
			setNextStopAtMillis();
			togglePlay();
		}
	}

	mp3.loop();
}

void TonuinoDFPlayer::pause()
{
	Serial.println(F("Pause player"));
	mp3.pause();
	tonuinoPlayer.pauseAndStandBy();
}

void TonuinoDFPlayer::sleep()
{
	mp3.sleep();
}

uint16_t TonuinoDFPlayer::getFolderTrackCount(uint16_t folder)
{
	if (hasGB32000B)
	{
		playTrack(folder, TRACKNUMBER_SILENCE);
		delay(100);
		mp3.pause();
	}
	return mp3.getFolderTrackCount(folder);
}





