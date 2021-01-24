
#include "Tonuino_Structs.h"

// prevent multiple definitions
#ifndef TONUINO_EEPROM_INCLUDED
#define TONUINO_EEPROM_INCLUDED

class TonuinoEEPROM
{
	public:
	void resetEEPROM();
	
	void writeLastDatasetToFlash(MusicDataset dataset);
	void writeLastTrackToFlash(uint8_t track, uint8_t folder);
	uint8_t loadLastTrackFromFlash(uint8_t folder);
	
	MusicDataset loadLastDatasetFromFlash();
	
	private:
	int flashAddress_Track(uint8_t folder);
};

#endif