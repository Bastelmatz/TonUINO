
#include "Tonuino_RotaryEncoder.h"

void TonuinoRotaryEncoder::setup(uint8_t clkPin, uint8_t dtPin)
{
	rotaryEncoder = RotaryEncoder(dtPin, clkPin, RotaryEncoder::LatchMode::FOUR3);
}

void TonuinoRotaryEncoder::read()
{
	static int rotEncPos = 0;
	rotaryEncoder.tick();
	int newPos = rotaryEncoder.getPosition();

	if (newPos != rotEncPos)
	{
		Serial.print("Pos: ");
		Serial.println(newPos);
		rotEncPos = newPos;
	}   
}



