
#include "Tonuino_Defines_Tools.h"

#ifdef TONUINO_MIRA_COINBOX

#include "Tonuino_Mira_Coinbox.h"
#include "shared/Tonuino_Config.h"
#include "shared/Tonuino_MainController.h"

TonuinoConfig getConfigMira()
{
	TonuinoConfig config;
	
	config.PINS.StopLED = 11; // 6
	config.PINS.Shutdown = 12; // 7

	config.PINS.Encoder_CLK = 6; // 5
	config.PINS.Encoder_DT = 7;  // 8

	config.PINS.NeopixelData = 5; // 11
	
	config.HW.CardReader = false;
	config.HW.UltraSonic = true;
	config.HW.RotaryEncoder = true;
	config.HW.NeopixelRing = true;
	config.HW.GB32000B = true;
	
	config.SW.StartMusicDS.startFolder = 10;
	config.SW.StartMusicDS.mode = 1;
	config.SW.VolumeIncrement = 2;
	config.SW.VolumeInit = 14;
	
	return config;
}

void setupMira()
{
	TonuinoConfig config = getConfigMira();
	
	setupTonuino(config);
}

void loopMira()
{
	loopTonuino();
}

#endif
