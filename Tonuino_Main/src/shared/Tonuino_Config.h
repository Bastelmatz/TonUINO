
#include <SPI.h>
#include <DFMiniMp3.h>

#include "Tonuino_Structs.h"

// prevent multiple definitions
#ifndef TONUINO_CONFIG_INCLUDED
#define TONUINO_CONFIG_INCLUDED

class TonuinoPinConfig
{
	public:
	uint8_t ButtonPause = A1;
	uint8_t ButtonNext = A3;
	uint8_t ButtonPrevious = A4;
	uint8_t Poti = A2;  // 10kOhm Poti
	uint8_t OpenAnalog = A6;

	// For DFPlayer RX and TX (usually 2 and 3) see DFPlayer class
	uint8_t DFPlayer_Busy = 4;
	uint8_t Encoder_CLK = 5;
	uint8_t Encoder_DT = 8;
	uint8_t StopLED = 6;
	uint8_t Shutdown = 7;
	uint8_t SonicTrigger = 9;
	uint8_t SonicEcho  = 10;
	uint8_t NeopixelData = 11;
};

class TonuinoHWConfig
{
	public:
	bool CardReader = true;
	bool PowerOff = false;
	bool Potentiometer = false;
	bool RotaryEncoder = false;
	bool UltraSonic = false;
	bool NeopixelRing = false;
	
	uint8_t NeopixelLeds = 12;
};

class TonuinoSWConfig
{
	public:
	uint8_t StandbyTime = 0;
	uint8_t SleepTime = 0;
	uint8_t VolumeInit = 10;
	uint8_t VolumeMin = 1;
	uint8_t VolumeMax = 25;
	uint8_t VolumeIncrement = 1;
	DfMp3_Eq Equalizer = DfMp3_Eq_Normal;

	bool StopPlayOnCardRemoval = false;

	MusicDataset StartMusicDS { 0, 0, 0, 0 };
	MusicDataset ShortCuts[4] { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
};

class TonuinoConfig
{
	public:
	TonuinoPinConfig PINS;
	TonuinoHWConfig HW;
	TonuinoSWConfig SW;
};

#endif