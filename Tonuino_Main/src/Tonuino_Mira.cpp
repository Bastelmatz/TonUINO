
#include "Tonuino_Defines_Tools.h"

#ifdef TONUINO_MIRA

#include "Tonuino_Mira.h"
#include "shared/Tonuino_Config.h"
#include "shared/Tonuino_MainController.h"

TonuinoConfig getConfigMira()
{
	TonuinoConfig config;
	
	config.UseCardReader = false;
	config.HasPotentiometer = true;
	config.HasUltraSonic = true;
	
	config.StopPlayOnCardRemoval = false;
	
	config.StartMusicDS.folder = 10;
	config.StartMusicDS.mode = 1;
	
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
