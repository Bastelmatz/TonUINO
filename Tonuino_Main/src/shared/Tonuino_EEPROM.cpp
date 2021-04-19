
#include "Tonuino_EEPROM.h"

#include <EEPROM.h>

static const uint8_t flashAddress_RecentMusicDS = 0;
// Check MusicDataset struct to ensure the folder and track index/address is correct
static const uint8_t flashAddress_RecentFolder = 7;
static const uint8_t flashAddress_RecentTrack = 8;

void TonuinoEEPROM::resetEEPROM()
{
  Serial.println(F("Reset -> EEPROM wird gelöscht"));
  for (uint16_t i = 0; i < EEPROM.length(); i++) 
  {
    EEPROM.update(i, 0);
  }
}

MusicDataset TonuinoEEPROM::loadFromFlash_RecentMusicDS() 
{
  MusicDataset musicDS;
  Serial.println(F("Load recent dataset from flash"));
  EEPROM.get(flashAddress_RecentMusicDS, musicDS);
  
  TONUINO_STRUCTS::print(&musicDS);
  
  return musicDS;
}

void TonuinoEEPROM::writeToFlash_RecentMusicDS(MusicDataset musicDS) 
{
  Serial.println(F("Write recent dataset"));
  TONUINO_STRUCTS::print(&musicDS);
  EEPROM.put(flashAddress_RecentMusicDS, musicDS);
}

void TonuinoEEPROM::writeToFlash_RecentTrack(uint16_t track) 
{
  Serial.print(F("Write recent track: "));
  Serial.println(track);
  EEPROM.update(flashAddress_RecentTrack, track);
}

void TonuinoEEPROM::writeToFlash_RecentFolder(uint8_t folder) 
{
  Serial.print(F("Write recent folder: "));
  Serial.println(folder);
  EEPROM.update(flashAddress_RecentFolder, folder);
}




