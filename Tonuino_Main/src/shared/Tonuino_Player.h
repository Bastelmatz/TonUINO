
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
	Section_Audiobook = 10,
	
	RandomFolder_Album = 11, // Einen zufälligen Ordner im Album Modus wiedergeben
	RandomFolder_Party = 12, // Einen zufälligen Ordner im Party Modus wiedergeben
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

class TonuinoPlayer
{
	public:	
	static TonuinoTimer sleepTimer;
	static TonuinoTimer standbyTimer;
	
	static bool isPlaying;
	static bool singleRepetition;
	static bool playRandom;
	static bool useQueue;
	static bool singleTrack;
	static bool listenUntilTrackEnds;
	
	static uint8_t mode;
	uint8_t currentTrack();
	uint8_t currentTrackInRange();
	static bool currentTrackStarted;
		
	void playTitle();
	void pauseNoStandBy();
	void pauseAndStandBy();
	void trackFinished();
	
	bool goToTrack(int trackDir);
	
	void loadFolder(uint8_t numTracks, MusicDataset musicDS);
	
	private:
	static uint8_t currentTrackIndex;
	static uint8_t firstTrack;
	static uint8_t endTrack;
	static bool currentTrackFinished;
	
	static uint8_t queue[255];

	uint8_t allTracksCount();
	static bool reShuffleOnEnd;
	
	void showTimerInfo();
	void shuffleQueue();
	bool goToTrack(bool next);
};

#endif