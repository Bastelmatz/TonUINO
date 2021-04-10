
#include "Tonuino_Player.h"

bool TonuinoPlayer::isPlaying = false;
bool TonuinoPlayer::currentTrackStarted = false;
bool TonuinoPlayer::currentTrackFinished = false;

uint8_t TonuinoPlayer::mode = 0;

uint8_t TonuinoPlayer::currentTrackIndex = 0;
uint8_t TonuinoPlayer::firstTrack = 0;
uint8_t TonuinoPlayer::endTrack = 0;
uint8_t TonuinoPlayer::queue[255];

uint8_t TonuinoPlayer::allTracksCount()
{
	return endTrack - firstTrack + 1;
}

// *********************************
// Timer Class
// *********************************

void TonuinoTimer::activate()
{
	if (timeInMin > 0)
	{
		activeTime = millis() + (timeInMin * 60UL * 1000UL);
	}
	else
	{
		activeTime = 0;
	}
}

void TonuinoTimer::disable()
{
	activeTime = 0;
}
// *********************************

TonuinoTimer TonuinoPlayer::standbyTimer;
TonuinoTimer TonuinoPlayer::sleepTimer;

// *********************************
// Settings
// *********************************

bool TonuinoPlayer::useQueue = false;
bool TonuinoPlayer::playRandom = false;
bool TonuinoPlayer::singleTrack = false;

bool TonuinoPlayer::reShuffleOnEnd = true;
bool TonuinoPlayer::singleRepetition = false;
bool TonuinoPlayer::listenUntilTrackEnds = false;

// *********************************

uint8_t TonuinoPlayer::currentTrack()
{
	if (useQueue) 
	{
		return queue[currentTrackIndex - 1];
	}
	return currentTrackIndex;
}

uint8_t TonuinoPlayer::currentTrackInRange()
{
	return currentTrack() - firstTrack + 1;
}

void TonuinoPlayer::shuffleQueue() 
{
	uint8_t allTracks = allTracksCount();
	// Queue für die Zufallswiedergabe erstellen
	for (uint8_t x = 0; x < allTracks; x++)
	{
		queue[x] = x + firstTrack;
	}
	// Rest mit 0 auffüllen
	for (uint8_t x = allTracks; x < sizeof(queue); x++)
	{
		queue[x] = 0;
	}
	// Queue mischen
	for (uint8_t i = 0; i < allTracks; i++)
	{
		uint8_t j = random(0, allTracks);
		uint8_t t = queue[i];
		queue[i] = queue[j];
		queue[j] = t;
	}
}

void TonuinoPlayer::showTimerInfo()
{
	// Show debug info if timers are used
	if (sleepTimer.timeInMin > 0)
	{
		Serial.print(F("Sleep timer: "));
		Serial.print(sleepTimer.activeTime);
		Serial.println(sleepTimer.activeTime > 0 ? "" : " = disabled");
	}
	if (standbyTimer.timeInMin > 0)
	{
		Serial.print(F("Standby timer: "));
		Serial.print(standbyTimer.activeTime);
		Serial.println(standbyTimer.activeTime > 0 ? "" : " = disabled");
	}
}

void TonuinoPlayer::playTitle()
{
	isPlaying = true;
	currentTrackStarted = true;
	currentTrackFinished = false;
	standbyTimer.disable();
	sleepTimer.activate();
	showTimerInfo();
}

void TonuinoPlayer::pauseNoStandBy()
{
	isPlaying = false;
	standbyTimer.disable();
	sleepTimer.disable();
	showTimerInfo();
}

void TonuinoPlayer::pauseAndStandBy()
{
	isPlaying = false;
	standbyTimer.activate();
	sleepTimer.disable();
	showTimerInfo();
}

void TonuinoPlayer::trackFinished()
{
	currentTrackFinished = true;
	
	// repeat current track
	if (singleRepetition)
	{
		return;
	}
	
	if (singleTrack) 
	{
		Serial.println(F("Nur einen Titel spielen -> keinen neuen Titel spielen"));
		pauseAndStandBy();
	}
}

bool TonuinoPlayer::goToTrack(int trackDirection) 
{
	if (currentTrackStarted && !currentTrackFinished && listenUntilTrackEnds)
	{
		return false;
	}
		
	currentTrackStarted = false;
	
	bool next = trackDirection == TRACKDIR_Next;
	bool previous = trackDirection == TRACKDIR_Previous;
	bool first = trackDirection == TRACKDIR_First;
	bool last = trackDirection == TRACKDIR_Last;
	
	// repeat current track
	if (singleRepetition)
	{
		return true;
	}
	
	if (singleTrack) 
	{
		if (playRandom) 
		{
			Serial.println(F("Einen zufälligen Titel wiedergeben"));
			currentTrackIndex = random(firstTrack, endTrack + 1);
		}
	}
	else
	{
		if (useQueue) 
		{
			if (next)
			{
				if (currentTrackIndex < allTracksCount()) 
				{
					currentTrackIndex++;
				} 
				else 
				{
					Serial.println(F("Ende der Queue -> beginne von vorne"));
					currentTrackIndex = 1;
					if (reShuffleOnEnd)
					{
						Serial.println(F("Ende der Queue -> mische neu"));
						shuffleQueue();
					}
				}
			}
			if (previous)
			{
				if (currentTrackIndex > 1) 
				{
					currentTrackIndex--;
				}
				else
				{
					Serial.println(F("Anfang der Queue -> springe ans Ende"));
					currentTrackIndex = allTracksCount();
				}
			}
			if (first)
			{
				currentTrackIndex = 1;
			}
			if (last)
			{
				currentTrackIndex = allTracksCount();
			}
		}
		else // fixed numerical order
		{
			if (next)
			{
				if (currentTrackIndex < endTrack) 
				{
					currentTrackIndex++;
				} 
				else
				{ 
					currentTrackIndex = firstTrack;
				}
			}
			if (previous)
			{
				if (currentTrackIndex > firstTrack) 
				{
					currentTrackIndex--;
				}
				else
				{
					currentTrackIndex = endTrack;
				}
			}
			if (first)
			{
				currentTrackIndex = firstTrack;
			}
			if (last)
			{
				currentTrackIndex = endTrack;
			}
		}
	}
	
	return true;
}

void TonuinoPlayer::loadFolder(uint8_t numTracksInFolder, MusicDataset musicDS) 
{
	mode = musicDS.mode;
	endTrack = numTracksInFolder;
	firstTrack = 1;
	Serial.print(numTracksInFolder);
	Serial.println(F(" files in folder "));
	
	bool isRandomSectionPair = mode == Section_RandomUniDirectionalPair || mode == Section_RandomBiDirectionalPair;
	bool isAnyRandomPair = isRandomSectionPair || mode == RandomUniDirectionalPair || mode == RandomBiDirectionalPair;
	bool useSection = mode == Section_AudioDrama || mode == Section_Party || mode == Section_Album || mode == Section_Audiobook || isRandomSectionPair;
	singleTrack = mode == AudioDrama || mode == Section_AudioDrama || mode == Single || 
				  mode == UniDirectionalPair || mode == BiDirectionalPair || isAnyRandomPair;
	playRandom = mode == AudioDrama || mode == Section_AudioDrama || 
				 mode == Party || mode == Section_Party || mode == RandomFolder_Party || 
				 isAnyRandomPair;
	useQueue = mode == Party || mode == Section_Party || mode == RandomFolder_Party;
	
	if (useSection)
	{
		Serial.println(F("Spezialmodus Von-Bis:"));
		Serial.print(musicDS.startTrack);
		Serial.print(F(" bis "));
		Serial.println(musicDS.endTrack);
		firstTrack = musicDS.startTrack;
		endTrack = musicDS.endTrack;
	}

	currentTrackIndex = firstTrack;

	if (useQueue && playRandom)
	{
		Serial.println(F("Alle Titel in zufälliger Reihenfolge wiedergeben"));
		currentTrackIndex = 1;
		shuffleQueue();
	}
	if (singleTrack) 
	{
		if (playRandom)
		{
			Serial.println(F("Einen zufälligen Titel wiedergeben"));
			currentTrackIndex = random(firstTrack, endTrack + 1);
		}
		else
		{
			Serial.println(F("Einen bestimmten Titel wiedergeben"));
			currentTrackIndex = musicDS.startTrack;
		}
	}
	if (mode == AudioBook) 
	{
		Serial.println(F("Kompletten Ordner spielen und Fortschritt merken"));
		uint8_t recentTrack = musicDS.recentTrack;
		if (recentTrack > 0 && recentTrack < numTracksInFolder) 
		{
			currentTrackIndex = recentTrack;
		}
	}

	Serial.println(currentTrackIndex);
}




