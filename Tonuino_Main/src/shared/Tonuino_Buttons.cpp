
#include "Tonuino_Buttons.h"

TonuinoJCButton TonuinoButtons::startStopButton;
TonuinoJCButton TonuinoButtons::nextButton;
TonuinoJCButton TonuinoButtons::previousButton;

void TonuinoButtons::setup(int pinStartStop, int pinNext, int pinPrevious)
{
	startStopButton.setup(pinStartStop, BUTTONCLICK_StartStop, BUTTONCLICK_LONG_StartStop);
	nextButton.setup(pinNext, BUTTONCLICK_Next, BUTTONCLICK_LONG_Next);
	previousButton.setup(pinPrevious, BUTTONCLICK_Previous, BUTTONCLICK_LONG_Previous);
}

int TonuinoButtons::readRaw()
{
	if (digitalRead(startStopButton.PIN) == LOW && 
		digitalRead(nextButton.PIN) == LOW && 
		digitalRead(previousButton.PIN) == LOW) 
	{
		return BUTTONDOWN_All;
	}
	return read();
}

int TonuinoButtons::read()
{
	int stateStartStop = startStopButton.readState();
	int stateNext = nextButton.readState();
	int statePrevious = previousButton.readState();
	
	// start-stop
	if (stateStartStop != BUTTONACTION_None) 
	{
		return stateStartStop;
	}
	// next
	if (stateNext != BUTTONACTION_None) 
	{
		return stateNext;
	}
	// previous
	if (statePrevious != BUTTONACTION_None) 
	{
		return statePrevious;
	}
	return BUTTONACTION_None;
}

ModifierDataset TonuinoButtons::getPlayerModification(bool isCurrentlyPlaying)
{
	int buttonState = read();
	ModifierDataset modiDS;
	modiDS.modi = MODI_None;
	modiDS.value = 0;
	
	// Buttons werden nun über JS_Button gehandelt, dadurch kann jede Taste doppelt belegt werden
	if (buttonState == BUTTONCLICK_StartStop)
	{
		modiDS.modi = MODI_TrackContinue;
		modiDS.value = 2;
	}
	if (buttonState == BUTTONCLICK_LONG_StartStop)
	{
		if (isCurrentlyPlaying) 
		{
			modiDS.modi = MODI_TrackNumber;
		}
		else 
		{
			modiDS.modi = MODI_ShortCut;
			modiDS.value = 0;
		}
	}
	if (buttonState == BUTTONCLICK_Next)
	{
		modiDS.modi = MODI_TrackNext;
	}
	if (buttonState == BUTTONCLICK_LONG_Next)
	{
		if (isCurrentlyPlaying) 
		{
			modiDS.modi = MODI_TrackLast;
		}
		else 
		{
			modiDS.modi = MODI_ShortCut;
			modiDS.value = 1;
		}
	}
	if (buttonState == BUTTONCLICK_Previous)
	{
		modiDS.modi = MODI_TrackPrevious;
	}
	if (buttonState == BUTTONCLICK_LONG_Previous)
	{
		if (isCurrentlyPlaying) 
		{
			modiDS.modi = MODI_TrackFirst;
		}
		else 
		{
			modiDS.modi = MODI_ShortCut;
			modiDS.value = 2;
		}
	}
	return modiDS;
}

ModifierDataset TonuinoButtons::getMenuModification(uint8_t currentValue, uint8_t defaultValue, uint8_t numberOptions)
{
	int buttonState = read();
	ModifierDataset modiDS;
	modiDS.modi = MODI_None;
	modiDS.value = 0;

	if (buttonState == BUTTONCLICK_LONG_StartStop) 
	{
		modiDS.modi = MODI_MENU_Cancel;
		modiDS.value = defaultValue;
	}
	if (buttonState == BUTTONCLICK_StartStop) 
	{
		modiDS.modi = MODI_MENU_Choose;
		modiDS.value = currentValue;
	}
	if (buttonState == BUTTONCLICK_LONG_Next) 
	{
		modiDS.modi = MODI_MENU_ChangeLarge;
		modiDS.value = min(currentValue + 10, numberOptions);
	} 
	if (buttonState == BUTTONCLICK_Next) 
	{
		modiDS.modi = MODI_MENU_ChangeSmall;
		modiDS.value = currentValue + 1 > numberOptions ? defaultValue : currentValue + 1;
	}
	if (buttonState == BUTTONCLICK_LONG_Previous) 
	{
		modiDS.modi = MODI_MENU_ChangeLarge;
		modiDS.value = max(currentValue - 10, 1);
	} 
	if (buttonState == BUTTONCLICK_Previous) 
	{
		modiDS.modi = MODI_MENU_ChangeSmall;
		uint8_t smallestValid = defaultValue + (defaultValue == 0 ? 1 : 0);
		modiDS.value = currentValue - 1 < smallestValid ? numberOptions : currentValue - 1;
	}
	return modiDS;
}

// ************************************
// JC Button
// ************************************

void TonuinoJCButton::setup(int pin, int codeClick, int codeLongPress)
{
	PIN = pin;
	CODE_Click = codeClick;
	CODE_LongPress = codeLongPress;
	
	jcButton = Button(pin);
	pinMode(pin, INPUT_PULLUP);
}

int TonuinoJCButton::readState()
{
	jcButton.read();
	
	if (jcButton.wasReleased()) 
	{
		if (ignore == false)
		{
			return CODE_Click;
		}
		ignore = false;
	} 
	else if (jcButton.pressedFor(LONG_PRESS) && ignore == false) 
	{
		ignore = true;
		return CODE_LongPress;
	}
	return BUTTONACTION_None;
}


