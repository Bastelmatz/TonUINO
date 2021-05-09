
// prevent multiple definitions
#ifndef TONUINO_PLAYER_INCLUDED
#define TONUINO_PLAYER_INCLUDED

#include <SPI.h>
#include "Tonuino_Structs.h"

enum EPlayerMode
{
	AudioDrama = 1, 	// Hörspielmodus: eine zufällige Datei aus dem Ordner
	Album = 2,			// Album Modus: kompletten Ordner spielen
	Party = 3,			// Party Modus: Ordner in zufälliger Reihenfolge
	Single = 4,			// Einzel Modus: eine Datei aus dem Ordner abspielen
	AudioBook = 5,		// Hörbuch Modus: kompletten Ordner spielen und Fortschritt merken

	Section_AudioDrama = 7,	// Spezialmodus Von-Bis: Hörspiel
	Section_Album = 8,		// Spezialmodus Von-Bis: Album
	Section_Party = 9,		// Spezialmodus Von-Bis: Party
	Section_Audiobook = 10, // Spezialmodus Von-Bis: Hörbuch
	
	RandomFolder_Album = 20, // Einen zufälligen Ordner im Album Modus wiedergeben
	RandomFolder_Party = 21, // Einen zufälligen Ordner im Party Modus wiedergeben
	
	UniDirectionalPair = 30, // Frage-Antwort Paar
	BiDirectionalPair = 31,  // TitelA-TitelB Paar
	
	RandomUniDirectionalPair = 35, // Zufälliges Frage-Antwort Paar
	RandomBiDirectionalPair = 36,  // Zufälliges TitelA-TitelB Paar
	Section_RandomUniDirectionalPair = 37, // Spezialmodus Von-Bis: Zufälliges Frage-Antwort Paar
	Section_RandomBiDirectionalPair = 38,  // Spezialmodus Von-Bis: Zufälliges TitelA-TitelB Paar
};

enum ETRACKDIRECTION
{
	TRACKDIR_None = 0,
	TRACKDIR_Next = 1, 	
	TRACKDIR_Previous = 2,
	TRACKDIR_First = 3,
	TRACKDIR_Last = 4,
};

class TonuinoTimer
{
	public:
	unsigned long activeTime = 0;
	uint8_t timeInMin = 0;
	
	void activate();
	void disable();
};

class TonuinoCounter
{
	public:
	uint8_t activeTarget = 0;
	uint8_t target = 0;
	
	void activate();
	void disable();
};

class TonuinoPlayer
{
	public:	
	static TonuinoTimer sleepTimer;
	static TonuinoTimer standbyTimer;
	static TonuinoCounter sleepCounter;
	
	static bool isPlaying;
	static bool singleRepetition;
	static bool playRandom;
	static bool listenUntilTrackEnds;
	
	static uint8_t mode;
	uint16_t currentTrack();
	uint16_t currentTrackInRange();
	static bool currentTrackStarted;
	static bool currentTrackFinished;
			
	void playTitle();
	void continueTitle();
	void pauseAndStandBy();
	void trackFinished();
	void setRandomPlay(bool bValue);
	
	bool goToTrack(ETRACKDIRECTION trackDir);
	
	void loadFolder(uint16_t numTracks, MusicDataset * musicDS);
	
	private:
	static uint16_t currentTrackIndex;
	static uint16_t firstTrack;
	static uint16_t secondTrack;
	static uint16_t thirdTrack;
	static uint16_t endTrack;
	static uint8_t tracksPlayedInARow;
	
	static const uint8_t queueSize = 100;
	static uint16_t queue[queueSize];
	static bool useQueue;
	static bool singleTrack;
	static bool fixSingleTrio;
	uint16_t allTracksCount();
	uint16_t queueLimit();
	
	void showTimerInfo();
	void showTimerInfo(uint8_t value);
	void shuffleQueue();
	bool goToTrack(bool next);
};

#endif