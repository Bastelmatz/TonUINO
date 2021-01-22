
#include "Tonuino_EEPROM.h"

#include <EEPROM.h>

static const int lastFolderSize = 4;

adminSettings TonuinoEEPROM::settings;

void TonuinoEEPROM::resetEEPROM()
{
  Serial.println(F("Reset -> EEPROM wird gelöscht"));
  for (int i = 0; i < EEPROM.length(); i++) 
  {
    EEPROM.update(i, 0);
  }
}

int TonuinoEEPROM::flashAddress_Track(uint8_t folder) 
{
  return lastFolderSize + folder;
}

int TonuinoEEPROM::flashAddress_Settings() 
{
  musicDataset musicDS;
  return lastFolderSize + sizeof(musicDS.folder) * 100;
}

void TonuinoEEPROM::writeLastDatasetToFlash(musicDataset musicDS) 
{
  Serial.println("Write last dataset to flash");
  EEPROM.put(0, musicDS);
}

musicDataset TonuinoEEPROM::loadLastDatasetFromFlash() 
{
  musicDataset musicDS;
  Serial.println("Load last dataset from flash");
  EEPROM.get(0, musicDS);
  
  Serial.print(F("Last folder: "));
  Serial.println(musicDS.folder);
  Serial.print(F("Last mode: "));
  Serial.println(musicDS.mode);
  Serial.print(F("Last special: "));
  Serial.println(musicDS.special);
  Serial.print(F("Last special2: "));
  Serial.println(musicDS.special2);
  
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

void TonuinoEEPROM::writeSettingsToFlash() 
{
  Serial.println(F("=== writeSettingsToFlash()"));
  int address = flashAddress_Settings();
  EEPROM.put(address, settings);
}

void TonuinoEEPROM::resetSettings() 
{
  Serial.println(F("=== resetSettings()"));
  settings.cookie = cardCookie;
  settings.version = 2;
  settings.maxVolume = 10;
  settings.minVolume = 1;
  settings.initVolume = 5;
  settings.eq = 1;
  settings.locked = false;
  settings.standbyTimer = 0;
  settings.shortCuts[0].folder = 0;
  settings.shortCuts[1].folder = 0;
  settings.shortCuts[2].folder = 0;
  settings.shortCuts[3].folder = 0;
  settings.adminMenuLocked = 0;
  settings.adminMenuPin[0] = 1;
  settings.adminMenuPin[1] = 1;
  settings.adminMenuPin[2] = 1;
  settings.adminMenuPin[3] = 1;

  writeSettingsToFlash();
}

void TonuinoEEPROM::migrateSettings(int oldVersion) 
{
  if (oldVersion == 1) {
    Serial.println(F("=== resetSettings()"));
    Serial.println(F("1 -> 2"));
    settings.version = 2;
    settings.adminMenuLocked = 0;
    settings.adminMenuPin[0] = 1;
    settings.adminMenuPin[1] = 1;
    settings.adminMenuPin[2] = 1;
    settings.adminMenuPin[3] = 1;
    writeSettingsToFlash();
  }
}

void TonuinoEEPROM::loadSettingsFromFlash() 
{
  Serial.println(F("=== loadSettingsFromFlash()"));
  int address = flashAddress_Settings();
  EEPROM.get(address, settings);
  if (settings.cookie != cardCookie)
  {
    resetSettings();
  }
  migrateSettings(settings.version);

  Serial.print(F("Version: "));
  Serial.println(settings.version);

  Serial.print(F("Maximal Volume: "));
  Serial.println(settings.maxVolume);

  Serial.print(F("Minimal Volume: "));
  Serial.println(settings.minVolume);

  Serial.print(F("Initial Volume: "));
  Serial.println(settings.initVolume);

  Serial.print(F("EQ: "));
  Serial.println(settings.eq);

  Serial.print(F("Locked: "));
  Serial.println(settings.locked);

  Serial.print(F("Sleep Timer: "));
  Serial.println(settings.standbyTimer);

  Serial.print(F("Admin Menu locked: "));
  Serial.println(settings.adminMenuLocked);

  Serial.print(F("Admin Menu Pin: "));
  Serial.print(settings.adminMenuPin[0]);
  Serial.print(settings.adminMenuPin[1]);
  Serial.print(settings.adminMenuPin[2]);
  Serial.println(settings.adminMenuPin[3]);
}



