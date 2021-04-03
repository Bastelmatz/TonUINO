
#include "Tonuino_Structs.h"

// prevent multiple definitions
#ifndef TONUINO_EEPROM_INCLUDED
#define TONUINO_EEPROM_INCLUDED

class TonuinoEEPROM
{
	public:
	void resetEEPROM();
	
	void writeToFlash_RecentMusicDS(MusicDataset dataset);
	void writeToFlash_RecentTrack(uint8_t track);
	void writeToFlash_RecentFolder(uint8_t folder);
	
	MusicDataset loadFromFlash_RecentMusicDS();
};

#endif