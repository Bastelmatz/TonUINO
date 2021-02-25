
#include "Tonuino_RotaryEncoder.h"

void TonuinoRotaryEncoder::setup(uint8_t clkPin, uint8_t dtPin)
{
	rotaryEncoder = RotaryEncoder(dtPin, clkPin, RotaryEncoder::LatchMode::FOUR3);
}

ERotation TonuinoRotaryEncoder::getState()
{
	rotaryEncoder.tick();
	uint16_t newPos = rotaryEncoder.getPosition();
	if (newPos != rotEncPos)
	{
		bool decreased = (newPos < rotEncPos && (rotEncPos != 65535 || newPos != 0)) || (newPos == 65535 && rotEncPos == 0);	
		Serial.print(F("Pos: "));
		Serial.println(newPos);
		rotEncPos = newPos;
		return decreased ? ROTATION_Minus : ROTATION_Plus;
	}  
	return ROTATION_NoChange;
}

ModifierDataset TonuinoRotaryEncoder::getPlayerModification()
{
	ModifierDataset modiDS;
	modiDS.modi = MODI_None;
	modiDS.value = 0;
	ERotation rotEncoderState = getState();
	if (rotEncoderState == ROTATION_Plus)
	{
		modiDS.modi = MODI_Player_VolumeUp;
	}
	if (rotEncoderState == ROTATION_Minus)
	{
		modiDS.modi = MODI_Player_VolumeDown;
	}
	return modiDS;
}

ModifierDataset TonuinoRotaryEncoder::getMenuModification(uint8_t currentValue, uint8_t defaultValue, uint8_t numberOptions)
{
	ModifierDataset modiDS;
	modiDS.modi = MODI_None;
	modiDS.value = 0;
	ERotation rotEncoderState = getState();
	if (rotEncoderState == ROTATION_Plus)
	{
		modiDS.modi = MODI_MENU_ChangeSmall;
		modiDS.value = currentValue + 1 > numberOptions ? defaultValue : currentValue + 1;
	}
	if (rotEncoderState == ROTATION_Minus)
	{
		modiDS.modi = MODI_MENU_ChangeSmall;
		uint8_t smallestValid = defaultValue + (defaultValue == 0 ? 1 : 0);
		modiDS.value = currentValue - 1 < smallestValid ? numberOptions : currentValue - 1;
	}
	return modiDS;
}

