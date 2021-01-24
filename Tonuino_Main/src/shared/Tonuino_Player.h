
// prevent multiple definitions
#ifndef TONUINO_PLAYER_INCLUDED
#define TONUINO_PLAYER_INCLUDED

#include <SPI.h>

typedef enum EPlayerMode
{
	AudioDrama = 1, 	// Hörspielmodus: eine zufällige Datei aus dem Ordner
	Album = 2,			// Album Modus: kompletten Ordner spielen
	Party = 3,			// Party Modus: Ordner in zufälliger Reihenfolge
	Single = 4,			// Einzel Modus: eine Datei aus dem Ordner abspielen
	AudioBook = 5,		// Hörbuch Modus: kompletten Ordner spielen und Fortschritt merken
	AdminMenu = 6,
	Section_AudioDrama = 7,	// Spezialmodus Von-Bis: Hörspiel: eine zufällige Datei aus dem Ordner
	Section_Album = 8,		// Spezialmodus Von-Bis: Album: alle Dateien zwischen Start und Ende spielen
	Section_Party = 9,		// Spezialmodus Von-Bis: Party Ordner in zufälliger Reihenfolge
	Section_Audiobook = 10
};

class TonuinoTimer
{
	public:
	static unsigned long activeTime;
	static uint8_t timeInMin;
	
	void activate();
	void disable();
};

class TonuinoPlayer
{
	public:	
	static TonuinoTimer sleepTimer;
	static TonuinoTimer standbyTimer;
	
	static bool isPlaying;
	static bool useSingleRepetition;
		
	uint8_t currentTrack();
	uint8_t currentTrackInRange();
	static bool currentTrackStarted;
		
	void playTitle();
	void pauseNoStandBy();
	void pauseAndStandBy();
	void trackFinished();
	
	bool goToNextTrack();
	bool goToPreviousTrack();
	
	void loadFolder(uint8_t numTracks, uint8_t folderMode, uint8_t startTrack, uint8_t endTrack, uint8_t lastTrack);
	
	private:
	static uint8_t mode;
	
	static uint8_t currentTrackIndex;
	static uint8_t firstTrack;
	static uint8_t endTrack;
	static bool currentTrackFinished;
	
	static uint8_t queue[255];
	static long standbyTimeInMin;

	uint8_t allTracksCount();
	bool useSection();
	bool useRandomSingle();
	bool useRandomQueue();
	bool useSingleTrack();
	static bool reShuffleOnEnd;
	static bool goToTrackOnPause;
	
	void shuffleQueue();
	bool goToTrack(bool next);
};

#endif