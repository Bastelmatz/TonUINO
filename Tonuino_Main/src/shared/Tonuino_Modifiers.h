
// prevent multiple definitions
#ifndef TONUINO_MODIFIERS_INCLUDED
#define TONUINO_MODIFIERS_INCLUDED

typedef enum EModifier
{
	MODI_TrackPlay = 1,
	MODI_TrackPause = 2,
	MODI_TrackToggle = 3,
	MODI_TrackNext = 4,
	MODI_TrackPrevious = 5,
	MODI_TrackFirst = 6,
	MODI_TrackLast = 7,
	
	MODI_Player_StandbyTime = 10,
	MODI_Player_SleepTime = 11,
	MODI_Player_Random = 20,
	MODI_Player_RepeatSingle = 21,
	MODI_Player_RepeatAll = 22,
	MODI_Player_ListenToEnd = 23,
	MODI_Player_StopOnCardRemoval = 24,
	
	MODI_LockAll = 30,
	MODI_LockButtons = 31,
	
	MODI_ResetCard = 40,
	MODI_ResetEEPROM = 41,
};

#endif