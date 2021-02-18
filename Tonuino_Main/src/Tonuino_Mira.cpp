
#include "Tonuino_Defines_Tools.h"

#ifdef TONUINO_MIRA

#include "Tonuino_Mira.h"
#include "shared/Tonuino_Config.h"
#include "shared/Tonuino_MainController.h"

TonuinoConfig getConfigMira()
{
	TonuinoConfig config;
	
	config.HW.Potentiometer = true;
	
	config.SW.VolumeMax = 10;  // reduce volume for stereo amplifier
	config.SW.StopPlayOnCardRemoval = false;
	
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
