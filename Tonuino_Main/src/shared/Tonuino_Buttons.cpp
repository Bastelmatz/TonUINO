
#include "Tonuino_Buttons.h"

TonuinoButton TonuinoButtons::startStopButton;
TonuinoButton TonuinoButtons::nextButton;
TonuinoButton TonuinoButtons::previousButton;

void TonuinoButtons::setup(uint8_t pinStartStop, uint8_t pinNext, uint8_t pinPrevious)
{
	startStopButton.setup(pinStartStop, BUTTONCLICK_StartStop, BUTTONPRESSED_StartStop, BUTTONPRESSED_LONG_StartStop);
	nextButton.setup(pinNext, BUTTONCLICK_Next, BUTTONPRESSED_Next, BUTTONPRESSED_LONG_Next);
	previousButton.setup(pinPrevious, BUTTONCLICK_Previous, BUTTONPRESSED_Previous, BUTTONPRESSED_LONG_Previous);
}

void TonuinoButtons::stateHandled()
{
	startStopButton.stateHandled = true;
	nextButton.stateHandled = true;
	previousButton.stateHandled = true;
}

uint8_t TonuinoButtons::read()
{
	return read(false);
}

uint8_t TonuinoButtons::readOnce()
{
	return read(true);
}

uint8_t TonuinoButtons::read(bool onlyOnce)
{
	startStopButton.setState(onlyOnce);
	nextButton.setState(onlyOnce);
	previousButton.setState(onlyOnce);
	
	// all buttons
	if (startStopButton.isAnyPressed() && nextButton.isAnyPressed() && previousButton.isAnyPressed())
	{
		if (startStopButton.isPressedLong() && nextButton.isPressedLong() && previousButton.isPressedLong()
		)
		{
			return BUTTONPRESSED_LONG_All;
		}
		return BUTTONPRESSED_All;
	}
	// start-stop
	if (startStopButton.hasAnyState()) 
	{
		return startStopButton.state;
	}
	// next
	if (nextButton.hasAnyState()) 
	{
		return nextButton.state;
	}
	// previous
	if (previousButton.hasAnyState()) 
	{
		return previousButton.state;
	}
	return BUTTONACTION_None;
}

ModifierDataset TonuinoButtons::getPlayerModification(bool isCurrentlyPlaying)
{
	uint8_t buttonState = readOnce();
	ModifierDataset modiDS;
	modiDS.modi = MODI_None;
	modiDS.value = 0;
	
	// Buttons werden nun über JS_Button gehandelt, dadurch kann jede Taste doppelt belegt werden
	if (buttonState == BUTTONCLICK_StartStop)
	{
		modiDS.modi = MODI_TrackContinue;
		modiDS.value = MODI_BOOLVAL_Toggle;
	}
	if (buttonState == BUTTONPRESSED_LONG_StartStop)
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
	if (buttonState == BUTTONPRESSED_LONG_Next)
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
	if (buttonState == BUTTONPRESSED_LONG_Previous)
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
	uint8_t buttonState = readOnce();
	ModifierDataset modiDS;
	modiDS.modi = MODI_None;
	modiDS.value = 0;
	uint8_t largeChange = numberOptions > 255 ? 50 : 10;
	
	if (buttonState == BUTTONPRESSED_LONG_StartStop) 
	{
		modiDS.modi = MODI_MENU_Cancel;
		modiDS.value = defaultValue;
	}
	if (buttonState == BUTTONCLICK_StartStop) 
	{
		modiDS.modi = MODI_MENU_Choose;
		modiDS.value = currentValue;
	}
	if (buttonState == BUTTONPRESSED_LONG_Next) 
	{
		modiDS.modi = MODI_MENU_ChangeLarge;
		modiDS.value = min(currentValue + largeChange, numberOptions);
	} 
	if (buttonState == BUTTONCLICK_Next) 
	{
		modiDS.modi = MODI_MENU_ChangeSmall;
		modiDS.value = currentValue + 1 > numberOptions ? defaultValue : currentValue + 1;
	}
	if (buttonState == BUTTONPRESSED_LONG_Previous) 
	{
		modiDS.modi = MODI_MENU_ChangeLarge;
		modiDS.value = max(currentValue - largeChange, 1);
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
// Tonuino Button
// ************************************

void TonuinoButton::setup(uint8_t pin, uint8_t codeClick, uint8_t codePressed, uint8_t codeLongPressed)
{
	PIN = pin;
	CODE_Click = codeClick;
	CODE_Pressed = codePressed;
	CODE_LongPressed = codeLongPressed;
	
	pinMode(pin, INPUT_PULLUP);
}

bool TonuinoButton::hasAnyState()
{
	return state != BUTTONACTION_None;
}

bool TonuinoButton::isAnyPressed()
{
	return state == CODE_Pressed || state == CODE_LongPressed;
}

bool TonuinoButton::isPressedLong()
{
	return state == CODE_LongPressed;
}

void TonuinoButton::setState(bool onlyOnce)
{
	long currentTime = millis();
	if (currentTime - lastCheckTime > 100)
	{
		lastCheckTime = currentTime;
		isPressed = digitalRead(PIN) == LOW;
		if (isPressed)
		{
			lastPressedTime = currentTime;
		}
		else
		{
			lastReleasedTime = currentTime;
		}
	}
	bool isWithinClickTime = currentTime - lastPressedTime < 1000;
	
	if (stateHandled)
	{
		stateHandled = isPressed || isWithinClickTime;
		state = BUTTONACTION_None;
		return;
	}

	uint8_t currentState = BUTTONACTION_None;
	if (isPressed)
	{
		ignore = false;
		if (currentTime - lastReleasedTime > LONG_PRESS)
		{
			currentState = CODE_LongPressed;
		}
		else
		{
			currentState = CODE_Pressed;
		}
	}
	else
	{
		if (isWithinClickTime)
		{
			if (!onlyOnce || ignore == false)
			{
				if (onlyOnce)
				{
					ignore = true;
				}
				currentState = CODE_Click;
			}
		}
	}

	state = currentState;
}


