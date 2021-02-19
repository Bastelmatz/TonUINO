
#ifndef TONUINO_BUTTONS_INCLUDED
#define TONUINO_BUTTONS_INCLUDED

typedef enum EBUTTONSTATE
{
	BUTTONACTION_None = 0,
	BUTTONCLICK_StartStop = 1,
	BUTTONCLICK_Next = 2,
	BUTTONCLICK_Previous = 3,
	BUTTONCLICK_All = 4,
	
	BUTTONCLICK_LONG_StartStop = 10,
	BUTTONCLICK_LONG_Next = 11,
	BUTTONCLICK_LONG_Previous = 12,
	BUTTONCLICK_LONG_All = 13,
	
	BUTTONDOWN_StartStop = 20,
	BUTTONDOWN_Next = 21,
	BUTTONDOWN_Previous = 22,
	BUTTONDOWN_All = 23,
};

#define LONG_PRESS 1000

#include "Tonuino_Modifiers.h"

#include <JC_Button.h>

class TonuinoJCButton
{
	public:
	int PIN;
	
	void setup(int pin, int codeClick, int codeLongPress);
	int readState();
	
	private:
	Button jcButton = Button(0);
	int CODE_Click;
	int CODE_LongPress;
	bool ignore;
};

class TonuinoButtons
{
	public:
	void setup(int pinStartStop, int pinNext, int pinPrevious);
	int read();
	int readRaw();
	ModifierDataset getPlayerModification(bool isCurrentlyPlaying);
	
	private:
	static TonuinoJCButton startStopButton;
	static TonuinoJCButton nextButton;
	static TonuinoJCButton previousButton;
};

#endif