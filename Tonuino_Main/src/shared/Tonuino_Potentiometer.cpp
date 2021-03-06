
#include "Tonuino_Potentiometer.h"

void TonuinoPotentiometer::setup(uint8_t potiPin, uint8_t minScale, uint8_t maxScale)
{
	pin = potiPin;
	min = minScale * 2;
	max = maxScale * 2;
	
	pinMode(pin, INPUT_PULLUP);
}

bool TonuinoPotentiometer::read()
{
    uint16_t valueRaw = analogRead(pin);
    uint8_t value = map(valueRaw, 0, 1024, min, max);
	
    if (valueRaw < 1023 && // ignore highest raw value, as it might occur occasionally
	   (appliedValue == 0 // for first call
	     || (value > appliedValue * 2 + hysterese && value <= max) // Compare current value with last incl. hysterese
         || (value < appliedValue * 2 - hysterese && value >= min)))  
    {
		appliedValue = value / 2;
		Serial.print(F("Potentiometer Value: "));
		Serial.println(appliedValue);  
		Serial.println(valueRaw);			
		return true;
    }
	return false;
}



