
#include "Tonuino_Player.h"

bool TonuinoPlayer::anyFolderStarted = false;
bool TonuinoPlayer::isPlaying = false;

uint8_t TonuinoPlayer::mode = 0;

uint8_t TonuinoPlayer::numTracksInFolder = 0;
uint8_t TonuinoPlayer::currentTrackIndex = 0;
uint8_t TonuinoPlayer::firstTrack = 0;
uint8_t TonuinoPlayer::lastTrackFinished  = 0;
uint8_t TonuinoPlayer::queue[255];

unsigned long TonuinoPlayer::activeStandbyTime = 0;
long TonuinoPlayer::standbyTimeInMin = 0;

uint8_t TonuinoPlayer::allTracksCount()
{
	return numTracksInFolder - firstTrack + 1;
}

bool TonuinoPlayer::useRandomQueue()
{
	return mode == Party || mode == Section_Party;
} 

bool TonuinoPlayer::useSection()
{
	return mode == Section_AudioDrama || mode == Section_Party || Section_Album;
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
	disableStandbyTimer();
}

void TonuinoPlayer::pauseNoStandBy()
{
	isPlaying = false;
	disableStandbyTimer();
}

void TonuinoPlayer::pauseAndStandBy()
{
	isPlaying = false;
	activateStandbyTimer();
}

void TonuinoPlayer::activateStandbyTimer() 
{
	Serial.println(F("=== activateStandbyTimer()"));
	if (standbyTimeInMin > 0)
	{
		activeStandbyTime = millis() + (standbyTimeInMin * 60 * 1000);
	}
	else
	{
		activeStandbyTime = 0;
	}
	Serial.println(activeStandbyTime);
}

void TonuinoPlayer::setStandbyTimer(long timeInMin) 
{
	standbyTimeInMin = timeInMin;
}

void TonuinoPlayer::disableStandbyTimer() 
{
	Serial.println(F("=== disableStandby()"));
	activeStandbyTime = 0;
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

  if (mode == AudioDrama || mode == Section_AudioDrama || mode == Single) 
  {
    Serial.println(F("Nur einen Titel spielen -> keinen neuen Titel spielen"));
    pauseAndStandBy();
  }
  if (mode == Album || mode == Section_Album || mode == AudioBook) 
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
      //// Wenn am Ende der Queue neu gemischt werden soll bitte die Zeilen wieder aktivieren
      //     Serial.println(F("Ende der Queue -> mische neu"));
      //     shuffleQueue();
    }
  }

  return isPlaying;
}

void TonuinoPlayer::playPreviousTrack() 
{
  Serial.println(F("=== previousTrack()"));

  if (mode == Album || mode == Section_Album) 
  {
    Serial.println(F("Albummodus ist aktiv -> vorheriger Titel"));
    if (currentTrackIndex > firstTrack) 
	{
      currentTrackIndex = currentTrackIndex - 1;
    }
  }
  if (useRandomQueue()) 
  {
    if (currentTrackIndex > 1) 
	{
      Serial.println(F("Party Modus ist aktiv -> zurück in der Queue "));
      currentTrackIndex--;
    }
    else
    {
      Serial.println(F("Anfang der Queue -> springe ans Ende "));
      currentTrackIndex = allTracksCount();
    }
  }
  if (mode == AudioBook) 
  {
    Serial.println(F("Hörbuch Modus ist aktiv -> vorheriger Titel"));
    if (currentTrackIndex > 1) 
	{
      currentTrackIndex--;
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
  currentTrackIndex = 1;
  Serial.print(numTracksInFolder);
  Serial.println(F(" Dateien in Ordner "));

  if (mode == AudioDrama) 
  {
    Serial.println(F("Hörspielmodus -> zufälligen Titel wiedergeben"));
    currentTrackIndex = random(1, numTracksInFolder + 1);
  }
  if (mode == Album) 
  {
    Serial.println(F("Album Modus -> kompletten Ordner wiedergeben"));
    currentTrackIndex = 1;
  }
  if (mode == Party) 
  {
    Serial.println(F("Party Modus -> Ordner in zufälliger Reihenfolge wiedergeben"));
    currentTrackIndex = 1;
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
  if (mode == Section_AudioDrama) 
  {
    Serial.println(F("Spezialmodus Von-Bin: Hörspiel -> zufälligen Titel wiedergeben"));
    Serial.print(startTrack);
    Serial.print(F(" bis "));
    Serial.println(endTrack);
	firstTrack = startTrack;
    numTracksInFolder = endTrack;
    currentTrackIndex = random(startTrack, numTracksInFolder + 1);
  }
  if (mode == Section_Album) 
  {
    Serial.println(F("Spezialmodus Von-Bis: Album: alle Dateien zwischen Start- und Enddatei spielen"));
    Serial.print(startTrack);
    Serial.print(F(" bis "));
    Serial.println(endTrack);
	firstTrack = startTrack;
    numTracksInFolder = endTrack;
    currentTrackIndex = startTrack;
  }
  if (mode == Section_Party) 
  {
    Serial.println(F("Spezialmodus Von-Bis: Party -> Ordner in zufälliger Reihenfolge wiedergeben"));
    firstTrack = startTrack;
    numTracksInFolder = endTrack;
    currentTrackIndex = 1;
  }
  if (useRandomQueue())
  {
    shuffleQueue();
  }

  Serial.println(currentTrackIndex);
}

uint8_t TonuinoPlayer::playFolder() 
{
    anyFolderStarted = true;
  
    Serial.println(F("== playFolder()")) ;
    disableStandbyTimer();
       
    return currentTrack();
}



