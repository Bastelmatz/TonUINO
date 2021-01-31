
#include "Tonuino_Potentiometer.h"

int TonuinoPotentiometer::appliedValue = CONFIG_VolumeInit;  // old Poti Value, Volume
int TonuinoPotentiometer::pin = 0;
int TonuinoPotentiometer::lastValue = 0;
int TonuinoPotentiometer::hysterese = 1;

void TonuinoPotentiometer::setup(int potiPin)
{
	pin = potiPin;
	pinMode(pin, INPUT_PULLUP);
}

bool TonuinoPotentiometer::read()
{
    int valueRaw = analogRead(pin);
    int value = map(valueRaw, 0, 1024, CONFIG_VolumeMin, CONFIG_VolumeMax);
	lastValue = value;
	
    if (valueRaw < 1023 && // ignore highest raw value, as it might occur occasionally
	   ((value > appliedValue + hysterese && value <= CONFIG_VolumeMax) // Compare current value with last incl. hysterese
         || (value < appliedValue - hysterese && value >= CONFIG_VolumeMin)))  
    {
		Serial.print("Potentiometer Value: ");
		Serial.println(value);  
		Serial.println(valueRaw);			
		appliedValue = value;
		return true;
    }
	return false;
}



