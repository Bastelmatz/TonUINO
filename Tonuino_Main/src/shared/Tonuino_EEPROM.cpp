
#include "Tonuino_EEPROM.h"

#include <EEPROM.h>

static const int lastFolderSize = 4;

adminSettings TonuinoEEPROM::mySettings;

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
  folderSettings folderSet;
  return lastFolderSize + sizeof(folderSet.folder) * 100;
}

void TonuinoEEPROM::writeLastFolderToFlash(folderSettings folder) 
{
  Serial.println(F("=== writeLastFolderToFlash()"));
  EEPROM.put(0, folder);
}

folderSettings TonuinoEEPROM::loadLastFolderFromFlash() 
{
  folderSettings folder;
  Serial.println(F("=== loadLastFolderFromFlash()"));
  EEPROM.get(0, folder);
  
  Serial.print(F("Last folder: "));
  Serial.println(folder.folder);
  Serial.print(F("Last mode: "));
  Serial.println(folder.mode);
  Serial.print(F("Last special: "));
  Serial.println(folder.special);
  Serial.print(F("Last special2: "));
  Serial.println(folder.special2);
  
  return folder;
}

void TonuinoEEPROM::writeLastTrackToFlash(uint8_t track, uint8_t folder) 
{
  Serial.println(F("=== writeLastTrackToFlash()"));
  EEPROM.update(flashAddress_Track(folder), track);
}

uint16_t TonuinoEEPROM::loadLastTrackFromFlash(uint8_t folder) 
{
  Serial.println(F("=== loadLastTrackFromFlash()"));
  uint16_t track = EEPROM.read(flashAddress_Track(folder));
  
  Serial.print(F("Last track: "));
  Serial.println(track);
  return track;
}

void TonuinoEEPROM::writeSettingsToFlash() 
{
  Serial.println(F("=== writeSettingsToFlash()"));
  int address = flashAddress_Settings();
  EEPROM.put(address, mySettings);
}

void TonuinoEEPROM::resetSettings() 
{
  Serial.println(F("=== resetSettings()"));
  mySettings.cookie = cardCookie;
  mySettings.version = 2;
  mySettings.maxVolume = 10;
  mySettings.minVolume = 1;
  mySettings.initVolume = 5;
  mySettings.eq = 1;
  mySettings.locked = false;
  mySettings.standbyTimer = 0;
  mySettings.shortCuts[0].folder = 0;
  mySettings.shortCuts[1].folder = 0;
  mySettings.shortCuts[2].folder = 0;
  mySettings.shortCuts[3].folder = 0;
  mySettings.adminMenuLocked = 0;
  mySettings.adminMenuPin[0] = 1;
  mySettings.adminMenuPin[1] = 1;
  mySettings.adminMenuPin[2] = 1;
  mySettings.adminMenuPin[3] = 1;

  writeSettingsToFlash();
}

void TonuinoEEPROM::migrateSettings(int oldVersion) 
{
  if (oldVersion == 1) {
    Serial.println(F("=== resetSettings()"));
    Serial.println(F("1 -> 2"));
    mySettings.version = 2;
    mySettings.adminMenuLocked = 0;
    mySettings.adminMenuPin[0] = 1;
    mySettings.adminMenuPin[1] = 1;
    mySettings.adminMenuPin[2] = 1;
    mySettings.adminMenuPin[3] = 1;
    writeSettingsToFlash();
  }
}

void TonuinoEEPROM::loadSettingsFromFlash() 
{
  Serial.println(F("=== loadSettingsFromFlash()"));
  int address = flashAddress_Settings();
  EEPROM.get(address, mySettings);
  if (mySettings.cookie != cardCookie)
  {
    resetSettings();
  }
  migrateSettings(mySettings.version);

  Serial.print(F("Version: "));
  Serial.println(mySettings.version);

  Serial.print(F("Maximal Volume: "));
  Serial.println(mySettings.maxVolume);

  Serial.print(F("Minimal Volume: "));
  Serial.println(mySettings.minVolume);

  Serial.print(F("Initial Volume: "));
  Serial.println(mySettings.initVolume);

  Serial.print(F("EQ: "));
  Serial.println(mySettings.eq);

  Serial.print(F("Locked: "));
  Serial.println(mySettings.locked);

  Serial.print(F("Sleep Timer: "));
  Serial.println(mySettings.standbyTimer);

  Serial.print(F("Admin Menu locked: "));
  Serial.println(mySettings.adminMenuLocked);

  Serial.print(F("Admin Menu Pin: "));
  Serial.print(mySettings.adminMenuPin[0]);
  Serial.print(mySettings.adminMenuPin[1]);
  Serial.print(mySettings.adminMenuPin[2]);
  Serial.println(mySettings.adminMenuPin[3]);
}



