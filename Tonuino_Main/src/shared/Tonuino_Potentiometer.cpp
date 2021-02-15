
#include "Tonuino_Potentiometer.h"

int TonuinoPotentiometer::pin = 0;
int TonuinoPotentiometer::min = 0;
int TonuinoPotentiometer::max = 0;

int TonuinoPotentiometer::appliedValue = 0;  // old Poti Value, Volume
int TonuinoPotentiometer::lastValue = 0;
int TonuinoPotentiometer::hysterese = 1;

void TonuinoPotentiometer::setup(int potiPin, int minScale, int maxScale)
{
	pin = potiPin;
	min = minScale;
	max = maxScale;
	
	pinMode(pin, INPUT_PULLUP);
}

bool TonuinoPotentiometer::read()
{
    int valueRaw = analogRead(pin);
    int value = map(valueRaw, 0, 1024, min, max);
	lastValue = value;
	
    if (valueRaw < 1023 && // ignore highest raw value, as it might occur occasionally
	   (appliedValue == 0 // for first call
	     || (value > appliedValue + hysterese && value <= max) // Compare current value with last incl. hysterese
         || (value < appliedValue - hysterese && value >= min)))  
    {
		Serial.print("Potentiometer Value: ");
		Serial.println(value);  
		Serial.println(valueRaw);			
		appliedValue = value;
		return true;
    }
	return false;
}



