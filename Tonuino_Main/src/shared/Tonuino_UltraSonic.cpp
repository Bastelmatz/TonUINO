
#include "Tonuino_UltraSonic.h"

uint32_t sonic_duration = 0; 
uint16_t sonic_distance = 0; 
bool sendSonicWave = true;
bool timedOut = false;
uint32_t sendHighTime = 0;
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
		timedOut = false;
		sendHighTime = micros();
		receiveHighTime = sendHighTime;
		sonic_duration = 0;
	}
	else 
	{
		// wait for wave echo start
		if (digitalRead(pinEcho) == HIGH)
		{
			if (receiveHighTime == sendHighTime)
			{
				receiveHighTime = micros();
			}
		}
		sonic_duration = micros() - receiveHighTime; // time since sending high / receiving first high
		// wait for wave echo end
		if (receiveHighTime > sendHighTime)
		{
			if (digitalRead(pinEcho) == LOW) // sonic end
			{
				sendSonicWave = true;			
			}
		}
		if (receiveHighTime == sendHighTime ? 
		    sonic_duration > 100UL * 1000 :  // timout for missing high
			sonic_duration > 100UL * 1000) 	  // timout for missing low 
		{
			timedOut = true;
			sendSonicWave = true;
		}
	}
		
	sonic_distance = 0;
	// send distance only for first appearance
	if (sendSonicWave && !timedOut) // = sonic received here
	{
		sonic_distance = sonic_duration * 0.1716; //mm
		//Serial.print(F("Duration: "));
		//Serial.println(sonic_duration);
		if (sonic_distance < 2000)
		{
			Serial.print(F("Distance: "));
			Serial.println(sonic_distance);
		}
	}
	return sonic_distance;
}



