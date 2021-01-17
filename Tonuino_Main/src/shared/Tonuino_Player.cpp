
#include "Tonuino_Player.h"

bool TonuinoPlayer::anyFolderStarted = false;
bool TonuinoPlayer::isPlaying = false;

uint8_t TonuinoPlayer::mode = 0;

uint8_t TonuinoPlayer::numTracksInFolder = 0;
uint8_t TonuinoPlayer::currentTrackIndex = 0;
uint8_t TonuinoPlayer::firstTrack = 0;
uint8_t TonuinoPlayer::lastTrackFinished  = 0;
uint8_t TonuinoPlayer::queue[255];

// *********************************
// Timer Class
unsigned long TonuinoTimer::activeTime = 0;
static long TonuinoTimer::timeInMin = 0;

void TonuinoTimer::activate()
{
	Serial.println(F("Activate timer"));
	if (timeInMin > 0)
	{
		activeTime = millis() + (timeInMin * 60 * 1000);
	}
	else
	{
		activeTime = 0;
	}
	Serial.println(activeTime);
}

void TonuinoTimer::disable()
{
	activeTime = 0;
}
// *********************************

TonuinoTimer TonuinoPlayer::standbyTimer;
TonuinoTimer TonuinoPlayer::sleepTimer;

uint8_t TonuinoPlayer::allTracksCount()
{
	return numTracksInFolder - firstTrack + 1;
}

bool TonuinoPlayer::useSection()
{
	return mode == Section_AudioDrama || mode == Section_Party || Section_Album;
}

bool TonuinoPlayer::useSingleTrack()
{
	return mode == AudioDrama || mode == Section_AudioDrama || mode == Single;
}

bool TonuinoPlayer::useRandomSingle()
{
	return mode == AudioDrama || mode == Section_AudioDrama;
}

bool TonuinoPlayer::useRandomQueue()
{
	return mode == Party || mode == Section_Party;
} 

bool TonuinoPlayer::reShuffleOnEnd()
{
	return true;
}

bool TonuinoPlayer::useAllRepetition()
{
	return false;
}

bool TonuinoPlayer::useSingleRepetition()
{
	return false;
}

uint8_t TonuinoPlayer::currentTrack()
{
  if (useRandomQueue()) 
  {
    return queue[currentTrackIndex - 1];
  }
  return currentTrackIndex;
}

uint8_t TonuinoPlayer::currentTrackInRange()
{
	if (useSection())
	{
		return currentTrack() - firstTrack + 1;
	}
	return currentTrack();
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
    uint8_t j = random (0, allTracks);
    uint8_t t = queue[i];
    queue[i] = queue[j];
    queue[j] = t;
  }
}

void TonuinoPlayer::playTitle()
{
	isPlaying = true;
	standbyTimer.disable();
	sleepTimer.activate();
}

void TonuinoPlayer::pauseNoStandBy()
{
	isPlaying = false;
	standbyTimer.disable();
	sleepTimer.disable();
}

void TonuinoPlayer::pauseAndStandBy()
{
	isPlaying = false;
	standbyTimer.activate();
	sleepTimer.disable();
}

bool TonuinoPlayer::playNextTrack() 
{
	Serial.print("Track finished: ");
	Serial.println(currentTrack());

	if (currentTrackIndex == lastTrackFinished) 
	{
		return;
	}
	lastTrackFinished = currentTrackIndex;

	Serial.println(F("=== nextTrack()"));

	if (useSingleTrack()) 
	{
		Serial.println(F("Nur einen Titel spielen -> keinen neuen Titel spielen"));
		pauseAndStandBy();
	}
	else
	{
		if (useRandomQueue()) 
		{
			if (currentTrackIndex < allTracksCount()) 
			{
				Serial.println(F("Weiter in der Queue"));
				currentTrackIndex++;
			} 
			else 
			{
				Serial.println(F("Ende der Queue -> beginne von vorne"));
				currentTrackIndex = 1;
				if (reShuffleOnEnd())
				{
					Serial.println(F("Ende der Queue -> mische neu"));
					shuffleQueue();
				}
			}
		}
		else // fixed numerical order
		{
			if (currentTrackIndex < numTracksInFolder) 
			{
				currentTrackIndex++;
			} 
			else
			{ 
				pauseAndStandBy();
			}
		}
	}

  return isPlaying;
}

void TonuinoPlayer::playPreviousTrack() 
{
	Serial.println(F("=== previousTrack()"));

	if (useSingleTrack()) 
	{
		return;
	}
	else
	{
		if (useRandomQueue()) 
		{
			if (currentTrackIndex > 1) 
			{
				Serial.println(F("Zurück in der Queue"));
				currentTrackIndex--;
			}
			else
			{
				Serial.println(F("Anfang der Queue -> springe ans Ende"));
				currentTrackIndex = allTracksCount();
			}
		}
		else // fixed numerical order
		{
			Serial.println(F("Vorheriger Titel"));
			if (currentTrackIndex > firstTrack) 
			{
				currentTrackIndex--;
			}
		}
	}
}

void TonuinoPlayer::loadFolder(uint8_t numTracks, uint8_t folderMode, uint8_t startTrack, uint8_t endTrack, uint8_t lastTrack) 
{
  Serial.println(F("== loadFolder()")) ;
  mode = folderMode;
  lastTrackFinished = 0;
  numTracksInFolder = numTracks;
  firstTrack = 1;
  Serial.print(numTracksInFolder);
  Serial.println(F(" Dateien in Ordner "));

  if (useSection())
  {
	Serial.println(F("Spezialmodus Von-Bis:"));
    Serial.print(startTrack);
    Serial.print(F(" bis "));
    Serial.println(endTrack);
    firstTrack = startTrack;
    numTracksInFolder = endTrack;
  }
  
  currentTrackIndex = firstTrack;
	
  if (useRandomQueue())
  {
	Serial.println(F("Alle Titel in zufälliger Reihenfolge wiedergeben"));
    currentTrackIndex = 1;
	shuffleQueue();
  }
  if (useRandomSingle()) 
  {
    Serial.println(F("Einen zufälligen Titel wiedergeben"));
    currentTrackIndex = random(firstTrack, numTracksInFolder + 1);
  }
  
  if (mode == Single) 
  {
    Serial.println(F("Einzel Modus -> eine Datei aus dem Odrdner abspielen"));
    currentTrackIndex = startTrack;
  }
  if (mode == AudioBook) 
  {
    Serial.println(F("Hörbuch Modus -> kompletten Ordner spielen und Fortschritt merken"));
    currentTrackIndex = lastTrack;
  }

  Serial.println(currentTrackIndex);
}

uint8_t TonuinoPlayer::playFolder() 
{
    anyFolderStarted = true;
  
    Serial.println(F("== playFolder()")) ;
    playTitle();
       
    return currentTrack();
}



