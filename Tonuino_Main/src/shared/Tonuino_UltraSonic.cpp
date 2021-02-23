
#include "Tonuino_UltraSonic.h"

uint32_t sonic_duration = 0; 
uint16_t sonic_distance = 0; 
bool sendSonicWave = true;
uint32_t receiveHighTime = 0;

void TonuinoUltraSonic::setup(uint8_t triggerPIN, uint8_t echoPIN)
{
	pinTrigger = triggerPIN;
	pinEcho = echoPIN;
	
	pinMode(pinTrigger, OUTPUT); 
	pinMode(pinEcho, INPUT); 
	digitalWrite(pinEcho, LOW); 
}

uint16_t TonuinoUltraSonic::read()
{
	//sonic_duration = pulseIn(pinEcho, HIGH); // blocks current thread -> breaks encoder timing
	if (sendSonicWave)
	{
		digitalWrite(pinTrigger, HIGH); 
		digitalWrite(pinTrigger, LOW);
		sendSonicWave = false;
		receiveHighTime = 0;
		sonic_distance = 0;
	}
	else
	{
		if (digitalRead(pinEcho) == HIGH)
		{
			if (receiveHighTime == 0)
			{
				receiveHighTime = micros();
			}
		}
		sonic_duration = micros() - receiveHighTime;
		if (receiveHighTime > 0)
		{
			if (digitalRead(pinEcho) == LOW) // sonic end
			{
				sendSonicWave = true;			
				sonic_distance = (sonic_duration/2) * 0.3432; //mm
				//Serial.print(F("Duration: "));
				//Serial.println(sonic_duration);
				if (sonic_distance < 2500)
				{
					Serial.print(F("Distance: "));
					Serial.println(sonic_distance);
				}
			}
		}
		if (sonic_duration > 1000 * 1000)
		{
			sendSonicWave = true;
		}
	}
	
	if (sendSonicWave) // = sonic received here
	{
		// send distance only for first appearance
		return sonic_distance; 
	}
	return 0;
}



