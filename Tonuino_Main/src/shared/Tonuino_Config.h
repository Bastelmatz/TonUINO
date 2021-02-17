
#include <SPI.h>
#include <DFMiniMp3.h>

#include "Tonuino_Structs.h"

// prevent multiple definitions
#ifndef TONUINO_CONFIG_INCLUDED
#define TONUINO_CONFIG_INCLUDED

class TonuinoConfig
{
	public:
	uint8_t StandbyTime = 0;
	uint8_t SleepTime = 0;
	uint8_t VolumeInit = 10;
	uint8_t VolumeMin = 1;
	uint8_t VolumeMax = 25;
	DfMp3_Eq Equalizer = DfMp3_Eq_Normal;

	bool UseCardReader = true;
	bool UsePowerOff = false;
	bool HasPotentiometer = false;
	bool HasUltraSonic = false;

	bool StopPlayOnCardRemoval = false;

	MusicDataset StartMusicDS { 0, 0, 0, 0 };
	MusicDataset ShortCuts[4];
};
  
#define PIN_ButtonPause A1
#define PIN_ButtonNext A3
#define PIN_ButtonPrevious A4
#define PIN_StopLED 6
#define PIN_Shutdown 7
#define PIN_SonicTrigger 5 
#define PIN_SonicEcho 8 
#define PIN_OpenAnalog A6

#define PIN_Poti A2  // 10kOhm Poti

#define PIN_DFPlayer_Busy 4
#define PIN_DFPlayer_RX 3  
#define PIN_DFPlayer_TX 2  
#endif