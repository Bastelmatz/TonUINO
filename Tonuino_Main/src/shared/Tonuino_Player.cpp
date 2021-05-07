
#include "Tonuino_Player.h"

bool TonuinoPlayer::isPlaying = false;
bool TonuinoPlayer::currentTrackStarted = false;
bool TonuinoPlayer::currentTrackFinished = false;

uint8_t TonuinoPlayer::mode = 0;

uint16_t TonuinoPlayer::currentTrackIndex = 0;
uint16_t TonuinoPlayer::firstTrack = 0;
uint16_t TonuinoPlayer::secondTrack = 0;
uint16_t TonuinoPlayer::thirdTrack = 0;
uint16_t TonuinoPlayer::endTrack = 0;

uint8_t TonuinoPlayer::tracksPlayedInARow = 0;

// Array size can be reduced (e.g. to 100) to free dynamic memory.
// As queue is only used for random play and reshuffled at the end, 
//  ... it shouldn't be noticable for the user that not all tracks are played once before repetition
uint16_t TonuinoPlayer::queue[queueSize];

uint16_t TonuinoPlayer::queueLimit()
{
	return allTracksCount() > queueSize ? queueSize : allTracksCount();
}
uint16_t TonuinoPlayer::allTracksCount()
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
// Counter Class
// *********************************

void TonuinoCounter::activate()
{
	activeTarget = target;
}

void TonuinoCounter::disable()
{
	activeTarget = 0;
}

// *********************************

TonuinoTimer TonuinoPlayer::standbyTimer;
TonuinoTimer TonuinoPlayer::sleepTimer;
TonuinoCounter TonuinoPlayer::sleepCounter;

// *********************************
// Settings
// *********************************

bool TonuinoPlayer::useQueue = false;
bool TonuinoPlayer::playRandom = false;
bool TonuinoPlayer::singleTrack = false;
bool TonuinoPlayer::fixSingleTrio = false;
bool TonuinoPlayer::singleRepetition = false;
bool TonuinoPlayer::listenUntilTrackEnds = false;

// *********************************

void TonuinoPlayer::setRandomPlay(bool bValue)
{
	if (useQueue)
	{
		// track index conversion
		if (bValue) // convert track index to index in random queue
		{
			for (uint8_t x = 0; x < queueSize; x++)
			{
				if (queue[x] = currentTrackIndex)
				{
					currentTrackIndex = x;
					break;
				}
			}
		}
		else // convert index in random queue to track index
		{
			currentTrackIndex = queue[currentTrackIndex - 1];
		}
	}
	playRandom = bValue;
}

uint16_t TonuinoPlayer::currentTrack()
{
	if (useQueue && playRandom) 
	{
		return queue[currentTrackIndex - 1];
	}
	return currentTrackIndex;
}

uint16_t TonuinoPlayer::currentTrackInRange()
{
	return currentTrack() - firstTrack + 1;
}

void TonuinoPlayer::shuffleQueue() 
{
	Serial.println(F("Shuffle queue"));
	uint16_t allTracks = allTracksCount();
	uint16_t limitHigh = queueLimit();
	// Queue für die Zufallswiedergabe erstellen
	for (uint16_t x = 0; x < limitHigh; x++)
	{
		queue[x] = x + firstTrack;
	}
	// Rest mit 0 auffüllen
	for (uint16_t x = allTracks; x < queueSize; x++)
	{
		queue[x] = 0;
	}
	// Queue mischen
	for (uint16_t i = 0; i < limitHigh; i++)
	{
		uint16_t j = random(0, limitHigh);
		uint16_t t = queue[i];
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
		showTimerInfo(sleepTimer.timeInMin);
	}
	if (standbyTimer.timeInMin > 0)
	{
		Serial.print(F("Standby timer: "));
		showTimerInfo(standbyTimer.timeInMin);
	}
	if (sleepCounter.target > 0)
	{
		Serial.print(F("Sleep counter: "));
		showTimerInfo(sleepCounter.target);
	}
}

void TonuinoPlayer::showTimerInfo(uint8_t value)
{
	Serial.print(value);
	Serial.println(value > 0 ? "" : " = disabled");
}

void TonuinoPlayer::playTitle()
{
	currentTrackStarted = true;
	currentTrackFinished = false;
	tracksPlayedInARow++;
	continueTitle();
}

void TonuinoPlayer::continueTitle()
{
	isPlaying = true;
	standbyTimer.disable();
	sleepTimer.activate();
	sleepCounter.activate();
	showTimerInfo();
}

void TonuinoPlayer::pauseAndStandBy()
{
	isPlaying = false;
	standbyTimer.activate();
	sleepTimer.disable();
	sleepCounter.disable();
	showTimerInfo();
	tracksPlayedInARow = 0;
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
	
	if (sleepCounter.activeTarget > 0 && tracksPlayedInARow >= sleepCounter.activeTarget)
	{
		Serial.println(F("Sleep by counter"));
		pauseAndStandBy();
		// set standby timer to current time to immediately trigger shutdown
		if (standbyTimer.timeInMin > 0)
		{
			standbyTimer.activeTime = millis();
		}
	}
}

bool TonuinoPlayer::goToTrack(ETRACKDIRECTION trackDirection) 
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
	if (fixSingleTrio)
	{
		if (currentTrackIndex == firstTrack && secondTrack > 0)
		{
			currentTrackIndex = secondTrack;
		}
		else
		{
			if (currentTrackIndex == secondTrack && thirdTrack > 0)
			{
				currentTrackIndex = thirdTrack;
			}
			else
			{
				currentTrackIndex = firstTrack;
			}
		}
		return true;
	}
	
	bool useQueueIndex = useQueue && playRandom;
	uint16_t limitLow = useQueueIndex ? 1 : firstTrack;
	uint16_t limitHigh = useQueueIndex ? queueLimit() : endTrack;
	
	if (next)
	{
		if (currentTrackIndex < limitHigh) 
		{
			currentTrackIndex++;
		} 
		else 
		{
			Serial.println(F("Springe an Anfang"));
			currentTrackIndex = limitLow;
			if (useQueue)
			{
				shuffleQueue();
			}
		}
	}
	if (previous)
	{
		if (currentTrackIndex > limitLow) 
		{
			currentTrackIndex--;
		}
		else
		{
			Serial.println(F("Springe ans Ende"));
			currentTrackIndex = limitHigh;
		}
	}
	if (first)
	{
		currentTrackIndex = limitLow;
	}
	if (last)
	{
		currentTrackIndex = limitHigh;
	}
	
	return true;
}

void TonuinoPlayer::loadFolder(uint16_t numTracksInFolder, MusicDataset * musicDS) 
{
	mode = musicDS->mode;
	endTrack = numTracksInFolder;
	firstTrack = 1;
	
	bool isRandomSectionPair = mode == Section_RandomUniDirectionalPair || mode == Section_RandomBiDirectionalPair;
	bool isAnyRandomPair = isRandomSectionPair || mode == RandomUniDirectionalPair || mode == RandomBiDirectionalPair;
	bool useSection = mode == Section_AudioDrama || mode == Section_Party || mode == Section_Album || mode == Section_Audiobook || isRandomSectionPair;
	fixSingleTrio =  mode == Single || mode == UniDirectionalPair || mode == BiDirectionalPair;
	singleTrack = mode == AudioDrama || mode == Section_AudioDrama || fixSingleTrio || isAnyRandomPair;
	useQueue = mode == AudioDrama || mode == Section_AudioDrama || 
			   mode == Party || mode == Section_Party || mode == RandomFolder_Party || 
			   isAnyRandomPair;
	playRandom = useQueue;
	
	if (useSection)
	{
		Serial.println(F("Spezialmodus Von-Bis:"));
		Serial.print(musicDS->startTrack);
		Serial.print(F(" bis "));
		Serial.println(musicDS->endTrack);
		firstTrack = musicDS->startTrack;
		endTrack = musicDS->endTrack;
	}
	if (fixSingleTrio)
	{
		Serial.println(F("Bestimmten Titel wiedergeben"));
		firstTrack = musicDS->startTrack;
		secondTrack = musicDS->endTrack;
		thirdTrack = musicDS->recentTrack;
	}
	else
	{
		secondTrack = thirdTrack = firstTrack;
	}
	
	currentTrackIndex = firstTrack;

	if (useQueue)
	{
		Serial.println(F("Titel in zufälliger Reihenfolge"));
		currentTrackIndex = 1;
		shuffleQueue();
	}

	if (mode == AudioBook || mode == Section_Audiobook) 
	{
		Serial.println(F("Kompletten Ordner spielen und Fortschritt merken"));
		uint16_t recentTrack = musicDS->recentTrack;
		if (recentTrack >= firstTrack && recentTrack <= endTrack) 
		{
			currentTrackIndex = recentTrack;
		}
	}

	Serial.print(F("Current track: "));
	Serial.println(currentTrackIndex);
}




