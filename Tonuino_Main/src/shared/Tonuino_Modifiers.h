
// prevent multiple definitions
#ifndef TONUINO_MODIFIERS_INCLUDED
#define TONUINO_MODIFIERS_INCLUDED

typedef enum EModifier
{
	TrackPlay = 1,
	TrackPause = 2,
	TrackToggle = 3,
	TrackNext = 4,
	TrackPrevious = 5,
	TrackFirst = 6,
	TrackLast = 7,
	
	Player_StandbyTime = 10,
	Player_SleepTime = 11,
	Player_Random = 20,
	Player_RepeatSingle = 21,
	Player_RepeatAll = 22,
	Player_ListenToEnd = 23,
	
	LockAll = 30,
	LockButtons = 31,
	
	ResetCard = 40,
	ResetEEPROM = 41,
};

#endif