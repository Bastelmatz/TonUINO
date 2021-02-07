
#include "Tonuino_Defines_Tools.h"

#ifdef TONUINO_MIRA

#include "Tonuino_Mira.h"
#include "shared/Tonuino_Config.h"
#include "shared/Tonuino_MainController.h"

void setConfigMira()
{
	CONFIG_StandbyTime = 0;
	
	CONFIG_UseCardReader = false;
	CONFIG_HasPotentiometer = true;
	CONFIG_HasUltraSonic = true;
	
	CONFIG_StopPlayOnCardRemoval = false;
}

void setupMira()
{
	setConfigMira();
	
	setupTonuino();
}

void loopMira()
{
	loopTonuino();
}

#endif
