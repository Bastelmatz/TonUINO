
#ifndef TONUINO_BUTTONS_INCLUDED
#define TONUINO_BUTTONS_INCLUDED

enum EBUTTONSTATE
{
	BUTTONACTION_None = 0,
	BUTTONCLICK_StartStop = 1,
	BUTTONCLICK_Next = 2,
	BUTTONCLICK_Previous = 3,
	BUTTONCLICK_All = 4,
	
	BUTTONPRESSED_StartStop = 10,
	BUTTONPRESSED_Next = 11,
	BUTTONPRESSED_Previous = 12,
	BUTTONPRESSED_All = 13,
	
	BUTTONPRESSED_LONG_StartStop = 20,
	BUTTONPRESSED_LONG_Next = 21,
	BUTTONPRESSED_LONG_Previous = 22,
	BUTTONPRESSED_LONG_All = 23,
};

#define LONG_PRESS 1000

#include "Tonuino_Modifiers.h"

class TonuinoButton
{
	public:
	uint8_t PIN;
	uint8_t state;
		
	void setup(uint8_t pin, uint8_t codeClick, uint8_t codeIsPressed, uint8_t codeLongPress);
	void setState(bool onlyOnce);
	bool hasAnyState();
	bool isAnyPressed();
	bool isPressedLong();
	
	private:
	bool isPressed;
	uint32_t lastCheckTime = 0;
	uint32_t lastPressedTime = 0;
	uint32_t lastReleasedTime = 0;
	uint8_t CODE_Click;
	uint8_t CODE_Pressed;
	uint8_t CODE_LongPressed;
	bool ignore;
};

class TonuinoButtons
{
	public:
	void setup(uint8_t pinStartStop, uint8_t pinNext, uint8_t pinPrevious);
	uint8_t read();
	ModifierDataset getPlayerModification(bool isCurrentlyPlaying);
	ModifierDataset getMenuModification(uint8_t currentValue, uint8_t defaultValue, uint8_t numberOptions);
	
	private:
	static TonuinoButton startStopButton;
	static TonuinoButton nextButton;
	static TonuinoButton previousButton;
	
	uint8_t readOnce();
	uint8_t read(bool onlyOnce);
};

#endif