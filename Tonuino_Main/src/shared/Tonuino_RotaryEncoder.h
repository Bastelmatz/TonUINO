
#include <SPI.h>
#include <RotaryEncoder.h>

#include "Tonuino_Modifiers.h"

enum ERotation
{
	ROTATION_NoChange = 0,
	ROTATION_Plus = 1,
	ROTATION_Minus = -1,
};

class TonuinoRotaryEncoder
{
	public:
	void setup(uint8_t clkPIN, uint8_t dtPIN);
	ERotation getState();
	ModifierDataset getPlayerModification();
	ModifierDataset getMenuModification(uint8_t currentValue, uint8_t defaultValue, uint8_t numberOptions);
	
	private:	
	RotaryEncoder rotaryEncoder = RotaryEncoder(0,0);
	uint16_t rotEncPos = 0;
};
