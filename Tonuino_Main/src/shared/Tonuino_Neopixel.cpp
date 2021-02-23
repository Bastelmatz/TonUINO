
#include "Tonuino_Neopixel.h"

uint16_t loopCount = 0;
uint16_t loopCountWait = 0; 
uint8_t lastDetectedVolume = 0;
long lastAnimationTime = 0;
int16_t currentDelayMS = 0;
uint8_t ledsCount = 0;

void TonuinoNeopixel::setup(uint8_t ledCount, uint8_t dataPin)
{
	strip = Adafruit_NeoPixel(ledCount, dataPin, NEO_GRB + NEO_KHZ800);
	ledsCount = ledCount;
	
	if (ledCount < LED_COUNT)
	{
		Serial.print(F("ERROR in neopixel setup: Increase LED_COUNT to >= "));
		Serial.println(ledCount);
	}
	
	strip.begin();
	
	// brightness only on setup
	// - not intended for continuous animation/changes  
	// - checkout FastLED library for advanced RGB neopixel coding with e.g. animated brightness
	strip.setBrightness(150); // from 0..255
}

void TonuinoNeopixel::turnOff()
{
	strip.clear();
    strip.show();
}

void TonuinoNeopixel::animate()
{
	bool startAnim = millis() - lastAnimationTime > currentDelayMS;
		
	lsrAnimationMode = 0; // default looping animation
	// detect volume change and trigger one-time animation
    if (animConfig.volume != lastDetectedVolume)
    {
		startAnim = true;
		lsrAnimationMode = 2;
		lastDetectedVolume = animConfig.volume;
    }
	
	if (startAnim) 
	{
		defineAnimation();
		
		strip.show();
		lastAnimationTime = millis();
	}
}

void TonuinoNeopixel::defineColors_Rainbow() // hue spectrum (Rainbow)
{
	for (i = 0; i < ledsCount; i++)
	{
		lsrColors = strip.ColorHSV(i * 65536 / ledsCount, 255, 30);
		lsrColorR[i] = (lsrColors >> 16 & 0xFF);
		lsrColorG[i] = (lsrColors >> 8 & 0xFF);
		lsrColorB[i] = (lsrColors & 0xFF);
	}
}

void TonuinoNeopixel::defineColors_GreenToRed() // From green to red
{
	for (i = 0; i < ledsCount; i++)
	{
		lsrHueCalc = 21000 / (ledsCount - 1) / (ledsCount - 1);
		lsrColors = strip.ColorHSV(((ledsCount - 1) - i) * (ledsCount - 1) * lsrHueCalc, 255, 30);
		strip.setPixelColor(i, lsrColors);
		lsrColorR[i] = (lsrColors >> 16 & 0xFF);
		lsrColorG[i] = (lsrColors >> 8 & 0xFF);
		lsrColorB[i] = (lsrColors & 0xFF);
	}
}

void TonuinoNeopixel::defineAnimation()
{
	if (lsrAnimationMode == 0)
	{
		if (animConfig.musicLoaded)
		{
			defineColors_Rainbow();
			
			// While music playing
			if (animConfig.musicPlaying)
			{
				currentDelayMS = 200;                        

				// Rotation clockwise
				y++;
				if (y >= ledsCount)
				{
					y = 0;
				}
				for (i = 0; i < ledsCount; i++)
				{
					strip.setPixelColor((i + y) % ledsCount, lsrColorR[i], lsrColorG[i], lsrColorB[i]);
				}
			}
			// While music paused
			else
			{
				currentDelayMS = 300;                     
				strip.clear(); // only one point

				// Filling increase
				y++;
				if (y >= ledsCount)
				{
					y = 0;
					z++;
					strip.clear();
				}
				if (z >= ledsCount)
				{
					z = 0;
				}
				for (i = 0; i < y + 1 ; i++)
				{
					strip.setPixelColor( y , lsrColorR[y], lsrColorG[y], lsrColorB[y]);
				}
			}
		}
		// default - no music loaded
		else
		{
			currentDelayMS = 200;               
			
			// All LEDs alternating in hue spectrum
			y++;
			if (y >= (ledsCount * 8) )
			{
				y = 0;
			}
			strip.fill(strip.ColorHSV((y * 65536 / ledsCount / 8) , 255, 30), 0, 0);
		}
	}

	// One time animation for volume change
	if (lsrAnimationMode == 2)
	{
		y = 0; // reset loop animation
		currentDelayMS = 1500;

		volumeScope = (animConfig.volumeMax - animConfig.volumeMin);
		volumeScopeAmount = (animConfig.volume - animConfig.volumeMin) * (ledsCount - 1) / volumeScope; // Lautstärkenanzeige angepasst an die Anzahl der LEDs

		defineColors_GreenToRed();
		
		// percentual volume animation
		strip.clear();
		for (i = 0; i < volumeScopeAmount + 1; i++)
		{
			strip.setPixelColor(i, lsrColorR[i], lsrColorG[i], lsrColorB[i]);
		}
	}
}




