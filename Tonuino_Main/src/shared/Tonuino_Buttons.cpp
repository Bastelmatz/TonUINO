
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


