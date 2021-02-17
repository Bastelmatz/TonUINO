
#include "Tonuino_Defines_Tools.h"

#ifdef TONUINO_MIRA_COINBOX

#include "Tonuino_Mira_Coinbox.h"
#include "shared/Tonuino_Config.h"
#include "shared/Tonuino_MainController.h"

TonuinoConfig getConfigMira()
{
	TonuinoConfig config;
	
	config.UseCardReader = false;
	config.HasUltraSonic = true;
	
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
