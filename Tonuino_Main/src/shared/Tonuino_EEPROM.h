
#include "Tonuino_Structs.h"

// prevent multiple definitions
#ifndef TONUINO_EEPROM_INCLUDED
#define TONUINO_EEPROM_INCLUDED

// admin settings stored in eeprom
struct adminSettings {
  uint32_t cookie;
  byte version;
  uint8_t maxVolume;
  uint8_t minVolume;
  uint8_t initVolume;
  uint8_t eq;
  bool locked;
  long standbyTimer;
  musicDataset shortCuts[4];
  uint8_t adminMenuLocked;
  uint8_t adminMenuPin[4];
};

class TonuinoEEPROM
{
	public:
	static adminSettings settings;
	
	void resetEEPROM();
	
	void writeLastDatasetToFlash(musicDataset dataset);
	void writeLastTrackToFlash(uint8_t track, uint8_t folder);
	uint8_t loadLastTrackFromFlash(uint8_t folder);
	
	void writeSettingsToFlash();
	void resetSettings();
	void migrateSettings(int oldVersion);
	
	void loadSettingsFromFlash();
	musicDataset loadLastDatasetFromFlash();
	
	private:
	int flashAddress_Settings();
	int flashAddress_Track(uint8_t folder);
};

#endif