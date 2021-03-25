
// prevent multiple definitions
#ifndef TONUINO_MODIFIERS_INCLUDED
#define TONUINO_MODIFIERS_INCLUDED

enum EModifier
{
	MODI_None = 0,
	MODI_TrackContinue = 1, 
	MODI_TrackNext = 2,
	MODI_TrackPrevious = 3,
	MODI_TrackFirst = 4,
	MODI_TrackLast = 5,
	MODI_TrackNumber = 6,
	
	MODI_ShortCut = 10,
	MODI_Advertisement = 11,
	
	MODI_Player_StandbyTime = 20,
	MODI_Player_SleepTime = 21,
	MODI_Player_Volume = 22,
	MODI_Player_VolumeUp = 23,
	MODI_Player_VolumeDown = 24,
	
	MODI_Player_Random = 30,
	MODI_Player_RepeatSingle = 31,
	MODI_Player_RepeatAll = 32,
	MODI_Player_ListenToEnd = 33,
	MODI_Player_StopOnCardRemoval = 34,
	MODI_Player_FreezeDance = 35,
	
	MODI_LockAll = 40,
	MODI_LockButtons = 41,
	
	MODI_SetupCard = 50,
	MODI_ResetCard = 51,
	MODI_ResetEEPROM = 52,
	
	MODI_MENU_ChangeSmall = 60,
	MODI_MENU_ChangeLarge = 61,
	MODI_MENU_Choose = 62,
	MODI_MENU_Cancel = 63,
};

enum EModifierBoolValue
{
	MODI_BOOLVAL_None = 0,
	MODI_BOOLVAL_Set = 1, 
	MODI_BOOLVAL_Undo = 2,
	MODI_BOOLVAL_Toggle = 3,
	
	MODI_BOOLVAL_OnRemoval_Set = 10,
	MODI_BOOLVAL_OnRemoval_Undo = 11,
	MODI_BOOLVAL_OnRemoval_Toggle = 12,
	
	MODI_BOOLVAL_Set_OnRemoval_Undo = 20,
	MODI_BOOLVAL_Undo_OnRemoval_Set = 21,
	MODI_BOOLVAL_Toggle_OnRemoval_Toggle = 22,
};

class TONUINOMODIFIER
{
	public:
	static bool isBoolModifer(EModifier modi)
	{
		switch (modi)
		{
			case MODI_TrackContinue:
			case MODI_Player_Random:
			case MODI_Player_RepeatSingle:
			case MODI_Player_RepeatAll:
			case MODI_Player_ListenToEnd:
			case MODI_Player_StopOnCardRemoval:
			case MODI_Player_FreezeDance:
			case MODI_LockAll:
			case MODI_LockButtons: return true;
		}
		return false;
	}
};

#include <SPI.h>

struct ModifierDataset 
{
	EModifier modi;
	uint16_t value;
};

#endif