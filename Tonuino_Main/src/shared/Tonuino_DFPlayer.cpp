
#include "Tonuino_DFPlayer.h"

#define busyPin 4
SoftwareSerial mySoftwareSerial(2, 3); // RX, TX

TonuinoPlayer TonuinoDFPlayer::tonuinoPlayer;

uint8_t TonuinoDFPlayer::volume = 0;
uint8_t TonuinoDFPlayer::volumeMin = 0;
uint8_t TonuinoDFPlayer::volumeMax = 30;

musicDataset TonuinoDFPlayer::musicDS;
bool TonuinoDFPlayer::musicDSLoaded = false;
bool TonuinoDFPlayer::newMusisDS = false;
bool TonuinoDFPlayer::feedbackOnVolumeChange = false;
bool TonuinoDFPlayer::listenUntilTrackEnds = false;

bool TonuinoDFPlayer::freezeDance_active = false;
unsigned long TonuinoDFPlayer::freezeDance_nextStopAtMillis = 0;

// implement a notification class,
// its member methods will get called
//
class Mp3Notify {
  public:
    static void OnError(uint16_t errorCode) {
      // see DfMp3_Error for code meaning
      Serial.println();
      Serial.print("Com Error ");
      Serial.println(errorCode);
    }
    static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action) {
      if (source & DfMp3_PlaySources_Sd) Serial.print("SD Karte ");
      if (source & DfMp3_PlaySources_Usb) Serial.print("USB ");
      if (source & DfMp3_PlaySources_Flash) Serial.print("Flash ");
      Serial.println(action);
    }
    static void OnPlayFinished(DfMp3_PlaySources source, uint16_t track) {
      TonuinoDFPlayer().trackFinished();
    }
    static void OnPlaySourceOnline(DfMp3_PlaySources source) {
      PrintlnSourceAction(source, "online");
    }
    static void OnPlaySourceInserted(DfMp3_PlaySources source) {
      PrintlnSourceAction(source, "bereit");
    }
    static void OnPlaySourceRemoved(DfMp3_PlaySources source) {
      PrintlnSourceAction(source, "entfernt");
    }
};

static DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(mySoftwareSerial);


void TonuinoDFPlayer::setup()
{
	pinMode(busyPin, INPUT);
	
	// DFPlayer Mini initialisieren
	mp3.begin();
	// Zwei Sekunden warten bis der DFPlayer Mini initialisiert ist
	delay(2000);
	
	tonuinoPlayer.pauseAndStandBy();
}

bool TonuinoDFPlayer::isPlaying() 
{
	return !digitalRead(busyPin);
}

void TonuinoDFPlayer::playMP3AndWait(uint16_t track)
{
	mp3.playMp3FolderTrack(track);
	waitForTrackToFinish();
}

void TonuinoDFPlayer::playTrack(uint8_t track)
{
	if (track > 0)
	{ 
		Serial.print(F("Spiele Titel:"));
		Serial.println(track);
		mp3.playFolderTrack(musicDS.folder, track);
		tonuinoPlayer.playTitle();
		delay(1000);
		newMusisDS = false;
	}
}

void TonuinoDFPlayer::playCurrentTrack()
{  
    uint8_t track = tonuinoPlayer.currentTrack();
	playTrack(track);
}

void TonuinoDFPlayer::loadFolder(musicDataset dataset, uint8_t lastTrack)
{
	musicDS = dataset;
	uint16_t numTracks = mp3.getFolderTrackCount(musicDS.folder);
	if (lastTrack == 0 || lastTrack > numTracks) 
	{
		lastTrack = 1;
	}
	Serial.println(musicDS.folder);
	tonuinoPlayer.loadFolder(numTracks, musicDS.mode, musicDS.special, musicDS.special2, lastTrack);
	musicDSLoaded = true;
	newMusisDS = true;
}

void TonuinoDFPlayer::loadAndPlayFolder(musicDataset dataset, uint8_t lastTrack)
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

void TonuinoDFPlayer::nextTrack() 
{
	if (newMusisDS)
	{
		playCurrentTrack();
	}
	else
	{
		if (tonuinoPlayer.goToNextTrack())
		{
			playCurrentTrack();
		}
	}
}

void TonuinoDFPlayer::previousTrack()
{
	if (tonuinoPlayer.goToPreviousTrack())
	{
		playCurrentTrack();
	}
}

void TonuinoDFPlayer::trackFinished()
{
	tonuinoPlayer.trackFinished();

	if (tonuinoPlayer.isPlaying && musicDSLoaded)
	{
		nextTrack();
	}
}

void TonuinoDFPlayer::waitForTrackToFinish() 
{
	long currentTime = millis();
	#define TIMEOUT 1000
	do 
	{
		mp3.loop();
	} while (!isPlaying() && millis() < currentTime + TIMEOUT);
	delay(1000);
	do 
	{
		mp3.loop();
	} while (isPlaying());
}

void TonuinoDFPlayer::playAdvertisement(int advertisement)
{
	if (isPlaying()) 
	{
		mp3.playAdvertisement(advertisement);
	}
	else 
	{
		mp3.start();
		delay(100);
		mp3.playAdvertisement(advertisement);
		delay(100);
		mp3.pause();
	}
}

void TonuinoDFPlayer::volumeUp()
{
	setVolume(volume + 1);
}

void TonuinoDFPlayer::volumeDown()
{
	setVolume(volume - 1);
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
		if (feedbackOnVolumeChange)
		{
			mp3.playAdvertisement(volume);
			delay(500);
		}
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
	Serial.print("Freeze dance - next stop in seconds: ");
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
			Serial.println("Freeze - pause playing ...");
			setNextStopAtMillis();
			togglePlay();
		}
	}

	mp3.loop();
}

void TonuinoDFPlayer::pause()
{
	mp3.pause();
}

void TonuinoDFPlayer::sleep()
{
	mp3.sleep();
}

void TonuinoDFPlayer::playTrack(uint8_t folder, uint8_t track)
{
	mp3.playFolderTrack(folder, track);
}

void TonuinoDFPlayer::playMp3Track(uint16_t track)
{
	mp3.playMp3FolderTrack(track);
}

uint16_t TonuinoDFPlayer::getFolderTrackCount(uint16_t folder)
{
	return mp3.getFolderTrackCount(folder);
}





