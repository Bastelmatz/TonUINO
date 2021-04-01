
#include "Tonuino_EEPROM.h"

#include <EEPROM.h>

static const int lastFolderSize = 4;

void TonuinoEEPROM::resetEEPROM()
{
  Serial.println(F("Reset -> EEPROM wird gelöscht"));
  for (uint16_t i = 0; i < EEPROM.length(); i++) 
  {
    EEPROM.update(i, 0);
  }
}

int TonuinoEEPROM::flashAddress_Track(uint8_t folder) 
{
  return lastFolderSize + folder;
}

void TonuinoEEPROM::writeLastDatasetToFlash(MusicDataset musicDS) 
{
  Serial.println(F("Write last dataset to flash"));
  EEPROM.put(0, musicDS);
}

MusicDataset TonuinoEEPROM::loadLastDatasetFromFlash() 
{
  MusicDataset musicDS;
  Serial.println(F("Load last dataset from flash"));
  EEPROM.get(0, musicDS);
  
  TONUINO_STRUCTS::print(musicDS);
  
  return musicDS;
}

void TonuinoEEPROM::writeLastTrackToFlash(uint8_t track, uint8_t folder) 
{
  Serial.println(F("=== writeLastTrackToFlash()"));
  EEPROM.update(flashAddress_Track(folder), track);
}

uint8_t TonuinoEEPROM::loadLastTrackFromFlash(uint8_t folder) 
{
  Serial.println(F("=== loadLastTrackFromFlash()"));
  uint8_t track = EEPROM.read(flashAddress_Track(folder));
  
  Serial.print(F("Last track: "));
  Serial.println(track);
  return track;
}



