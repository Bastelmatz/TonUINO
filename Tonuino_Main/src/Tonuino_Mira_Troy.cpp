
#include "Tonuino_Defines_Tools.h"

#ifdef TONUINO_MIRA_TROY

#include "Tonuino_Mira_Troy.h"
#include "shared/Tonuino_Config.h"
#include "shared/Tonuino_MainController.h"

TonuinoConfig getConfigMira()
{
	TonuinoConfig config;
	
	return config;
}

void setupMira()
{
	TonuinoConfig config = getConfigMira();
	
	config.SW.VolumeInit = 24; // volume is controlled externally, same value as max somehow crashed dfplayer?!
	
	setupTonuino(config);
}

void loopMira()
{
	loopTonuino();
}

#endif
