
#include "Tonuino_DFPlayer.h"

TonuinoPlayer TonuinoDFPlayer::tonuinoPlayer;

uint8_t TonuinoDFPlayer::pin_Busy = 0;
uint8_t TonuinoDFPlayer::activeFolder = 0;
uint16_t TonuinoDFPlayer::activeTrack = 0;

uint8_t TonuinoDFPlayer::volume = 0;
uint8_t TonuinoDFPlayer::volumeMin = 0;
uint8_t TonuinoDFPlayer::volumeMax = 25;
uint8_t TonuinoDFPlayer::volumeIncrement = 1;

MusicDataset TonuinoDFPlayer::musicDS;
bool TonuinoDFPlayer::musicDSLoaded = false;
bool TonuinoDFPlayer::newMusisDS = false;

bool TonuinoDFPlayer::freezeDance_active = false;
unsigned long TonuinoDFPlayer::freezeDance_nextStopAtMillis = 0;

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
	
void TonuinoDFPlayer::setup(uint8_t pinBusy)
{
	pin_Busy = pinBusy;
	
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
	Serial.print(F("Play MP3 "));
	Serial.println(track);
	activeFolder = 0;
	activeTrack = track;
	mp3.playMp3FolderTrack(track);
}

void TonuinoDFPlayer::playMP3AndWait(uint16_t track)
{
	playMp3Track(track);
	waitForTrackToFinish();
}

void TonuinoDFPlayer::playTrack(uint8_t folder, uint8_t track)
{
	Serial.print(F("Play track "));
	Serial.print(track);
	Serial.print(F(" from folder "));
	Serial.println(folder);
	activeFolder = folder;
	activeTrack = track;
	mp3.playFolderTrack(folder, track);
	delay(1000);
}

void TonuinoDFPlayer::playTrack(uint8_t track)
{
	if (track > 0)
	{ 
		playTrack(musicDS.folder, track);
		tonuinoPlayer.playTitle();
		newMusisDS = false;
	}
}

void TonuinoDFPlayer::playCurrentTrack()
{  
    uint8_t track = tonuinoPlayer.currentTrack();
	playTrack(track);
}

void TonuinoDFPlayer::loadFolder(MusicDataset dataset, uint8_t lastTrack)
{
	musicDS = dataset;
	uint16_t numTracks = mp3.getFolderTrackCount(musicDS.folder);
	if (lastTrack == 0 || lastTrack > numTracks) 
	{
		lastTrack = 1;
	}

	Serial.print(F("Load folder "));
	Serial.print(musicDS.folder);
	Serial.print(F(" with mode "));
	Serial.println(musicDS.mode);
	tonuinoPlayer.loadFolder(numTracks, musicDS.mode, musicDS.special, musicDS.special2, lastTrack);
	musicDSLoaded = true;
	newMusisDS = true;
}

void TonuinoDFPlayer::loadAndPlayFolder(MusicDataset dataset, uint8_t lastTrack)
{
	loadFolder(dataset, lastTrack);
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
		mp3.start(); // Continue
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

void TonuinoDFPlayer::goToTrack(int trackDir)
{
	if (tonuinoPlayer.goToTrack(trackDir))
	{
		playCurrentTrack();
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
	Serial.print(F("Finished track "));
	Serial.print(activeTrack);
	Serial.print(F(" in folder "));
	if (activeFolder > 0)
	{
		Serial.println(activeFolder);
	}
	else
	{
		Serial.println(F("MP3"));
	}
	
	Serial.print(F("Current track "));
	Serial.println(tonuinoPlayer.currentTrack());
	if (activeTrack == tonuinoPlayer.currentTrack())
	{
		tonuinoPlayer.trackFinished();
		
		if (tonuinoPlayer.isPlaying && musicDSLoaded)
		{
			nextTrack();
		}
	}
	activeTrack = 0;
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
	do 
	{
		mp3.loop();
	} while (isPlaying());
}

void TonuinoDFPlayer::playAdvertisement(uint16_t advertisement)
{
	Serial.print(F("Play advertisement "));
	Serial.println(advertisement);
	if (isPlaying()) 
	{
		mp3.playAdvertisement(advertisement);
		waitForTrackToFinish();
	}
	else 
	{
		mp3.start();
		mp3.playAdvertisement(advertisement);
		delay(100);
		mp3.pause();
	}
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
	mp3.start();
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
		setNextStopAtMillis();
	}
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
	mp3.pause();
	tonuinoPlayer.pauseAndStandBy();
}

void TonuinoDFPlayer::sleep()
{
	mp3.sleep();
}

uint16_t TonuinoDFPlayer::getFolderTrackCount(uint16_t folder)
{
	return mp3.getFolderTrackCount(folder);
}





