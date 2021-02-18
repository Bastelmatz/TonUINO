
// prevent multiple definitions
#ifndef TONUINO_DFPLAYER_INCLUDED
#define TONUINO_DFPLAYER_INCLUDED

#include "Tonuino_Structs.h"
#include "Tonuino_Player.h"

#include <DFMiniMp3.h>
#include <SoftwareSerial.h>
#include <SPI.h>

class TonuinoDFPlayer
{
	public:
	
	class Mp3Notify {
	  public:
		static void OnError(uint16_t errorCode);
		static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action);
		static void OnPlayFinished(DfMp3_PlaySources source, uint16_t track);
		static void OnPlaySourceOnline(DfMp3_PlaySources source);
		static void OnPlaySourceInserted(DfMp3_PlaySources source);
		static void OnPlaySourceRemoved(DfMp3_PlaySources source);
	};

	static MusicDataset musicDS;
	static TonuinoPlayer tonuinoPlayer;
	static uint8_t volume;
	static uint8_t volumeMin;
	static uint8_t volumeMax;
	static bool musicDSLoaded;
	static bool freezeDance_active;
			
	void setup(uint8_t pinBusy);
	bool isPlaying();
	void loadFolder(MusicDataset dataset, uint8_t lastTrack);
	void loadAndPlayFolder(MusicDataset dataset, uint8_t lastTrack);
	void continueTitle();
	void pauseAndStandBy();
	void togglePlay();
	void goToTrack(int trackDir);
	void nextTrack();
	void previousTrack();
	void firstTrack();
	void lastTrack();
	void waitForTrackToFinish();
	void playAdvertisement(int advertisement);
	void playMP3AndWait(uint16_t track);
	void volumeUp();
	void volumeDown();
	void setVolume(uint8_t vol);
	void setEqualizer(DfMp3_Eq eq);
	void trackFinished();
		
	void start();
	void loop();
	void pause();
	void sleep();
	void playTrack(uint8_t folder, uint8_t track);
	void playMp3Track(uint16_t track);
	uint16_t getFolderTrackCount(uint16_t folder);
	
	void setFreezeDance(bool active);

	private:
	static uint8_t pin_Busy;
	static uint8_t activeFolder;
	static uint16_t activeTrack;
	static bool newMusisDS;
	static bool feedbackOnVolumeChange;
	static unsigned long freezeDance_nextStopAtMillis;

	void playCurrentTrack();
	void playTrack(uint8_t track);
	void setNextStopAtMillis();
};

#endif