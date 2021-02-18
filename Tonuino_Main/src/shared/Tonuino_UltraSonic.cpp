
#include "Tonuino_UltraSonic.h"

long sonic_duration = 0; 
long sonic_distance = 0; 
bool sendSonicWave = true;
bool receiveSonicWave = false;
long sonicSendTime = 0;

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
		receiveSonicWave = false;
		sonic_distance = 0;
	}
	else
	{
		if (digitalRead(pinEcho) == HIGH)
		{
			if (!receiveSonicWave)
			{
				sonicSendTime = micros();
			}
			receiveSonicWave = true;
		}
		if (receiveSonicWave)
		{
			sonic_duration = micros() - sonicSendTime;
			bool sonicEnd = digitalRead(pinEcho) == LOW;
			if (sonicEnd || sonic_duration > 1000 * 1000)
			{
				sendSonicWave = true;			
				sonic_distance = (sonic_duration/2) * 0.3432; //mm
				//Serial.print("Duration: ");
				//Serial.println(sonic_duration);
				if (sonic_distance < 2500)
				{
					Serial.print("Distance: ");
					Serial.println(sonic_distance);
				}
			}
		}
	}
	
	if (sendSonicWave) // = sonic received here
	{
		// send distance only for first appearance
		return sonic_distance; 
	}
	return 0;
}



