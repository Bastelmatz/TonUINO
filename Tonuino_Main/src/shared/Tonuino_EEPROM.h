
#include "Tonuino_Structs.h"

// prevent multiple definitions
#ifndef TONUINO_EEPROM_INCLUDED
#define TONUINO_EEPROM_INCLUDED

// admin settings stored in eeprom
struct adminSettings {
  uint32_t cookie;
  byte version;
  long standbyTimer;
  musicDataset shortCuts[4];
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
	
	void loadSettingsFromFlash();
	musicDataset loadLastDatasetFromFlash();
	
	private:
	int flashAddress_Settings();
	int flashAddress_Track(uint8_t folder);
};

#endif