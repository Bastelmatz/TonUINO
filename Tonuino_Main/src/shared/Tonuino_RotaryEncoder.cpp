
#include "Tonuino_RotaryEncoder.h"

void TonuinoRotaryEncoder::setup(uint8_t clkPin, uint8_t dtPin)
{
	rotaryEncoder = RotaryEncoder(dtPin, clkPin, RotaryEncoder::LatchMode::FOUR3);
}

ModifierDataset TonuinoRotaryEncoder::getPlayerModification()
{
	rotaryEncoder.tick();
	uint16_t newPos = rotaryEncoder.getPosition();

	ModifierDataset modiDS;
	modiDS.modi = MODI_None;
	modiDS.value = 0;
	if (newPos != rotEncPos)
	{
		modiDS.modi = newPos > rotEncPos ? MODI_Player_VolumeUp : MODI_Player_VolumeDown;

		Serial.print(F("Pos: "));
		Serial.println(newPos);
		rotEncPos = newPos;
	}  
	return modiDS;
}



