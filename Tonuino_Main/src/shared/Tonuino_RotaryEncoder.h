
#include <SPI.h>
#include <RotaryEncoder.h>

#include "Tonuino_Modifiers.h"

class TonuinoRotaryEncoder
{
	public:
	void setup(uint8_t clkPIN, uint8_t dtPIN);
	ModifierDataset getPlayerModification();
	
	private:	
	RotaryEncoder rotaryEncoder = RotaryEncoder(0,0);
	uint16_t rotEncPos = 0;
};
