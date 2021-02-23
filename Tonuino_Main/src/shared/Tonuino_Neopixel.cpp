
#include "Tonuino_Neopixel.h"

uint16_t loopCount = 0;
uint16_t loopCountWait = 0; 
uint8_t lastDetectedVolume = 0;
long lastAnimationTime = 0;
int16_t currentDelayMS = 0;

void TonuinoNeopixel::setup(uint8_t ledCount, uint8_t dataPin)
{
	strip = Adafruit_NeoPixel(ledCount, dataPin, NEO_GRB + NEO_KHZ800);
	
	if (ledCount < LED_COUNT)
	{
		Serial.print("ERROR in neopixel setup: Increase LED_COUNT to >= ");
		Serial.println(ledCount);
	}
	
	strip.begin();
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

void TonuinoNeopixel::defineColors_Rainbow(bool reset) // hue spectrum (Rainbow)
{
	if (reset)
	{
		x = 0;
	}
	do
	{
		for (i = 0; i < strip.numPixels(); i++)
		{
			lsrColors = strip.ColorHSV(i * 65536 / strip.numPixels(), 255, 30);
			lsrColorR[i] = (lsrColors >> 16 & 0xFF);
			lsrColorG[i] = (lsrColors >> 8 & 0xFF);
			lsrColorB[i] = (lsrColors & 0xFF);
		}
		x++;
	} while (x < strip.numPixels());
}

void TonuinoNeopixel::defineColors_GreenToRed() // From green to red
{
	x = 0;
	do
	{
		for (i = 0; i < strip.numPixels(); i++)
		{
			lsrHueCalc = 21000 / (strip.numPixels() - 1) / (strip.numPixels() - 1);
			lsrColors = strip.ColorHSV(((strip.numPixels() - 1) - i) * (strip.numPixels() - 1) * lsrHueCalc, 255, 30);
			strip.setPixelColor(i, lsrColors);
			lsrColorR[i] = (lsrColors >> 16 & 0xFF);
			lsrColorG[i] = (lsrColors >> 8 & 0xFF);
			lsrColorB[i] = (lsrColors & 0xFF);
		}
		x++;
	}
	while (x < strip.numPixels());
}

void TonuinoNeopixel::defineAnimation()
{
	if (lsrAnimationMode == 0)
	{
		if (animConfig.musicLoaded)
		{
			// While music playing
			if (animConfig.musicPlaying)
			{
				currentDelayMS = 100;                        

				defineColors_Rainbow(false);

				// Rotation clockwise
				y++;
				x = 0;
				if (y >= strip.numPixels())
				{
					y = 0;
				}
				do
				{
					for (i = 0; i < strip.numPixels(); i++)
					{
						strip.setPixelColor((i + y) % strip.numPixels(), lsrColorR[i], lsrColorG[i], lsrColorB[i]);
					}
					x++;
				}
				while (x < strip.numPixels());
			}
			// While music paused
			else
			{
				currentDelayMS = 150;                     

				strip.clear(); // only one point
				
				defineColors_Rainbow(true);

				// Filling increase
				y++;
				if (y >= strip.numPixels())
				{
					y = 0;
					z++;
					strip.clear();
				}
				if (z >= strip.numPixels())
				{
					z = 0;
				}

				x = 0;
				do
				{
					for (i = 0; i < y + 1 ; i++)
					{
						strip.setPixelColor( y , lsrColorR[y], lsrColorG[y], lsrColorB[y]);
					}
					x++;
				}
				while (x < y + 1);
			}
		}
		// default - no music loaded
		else
		{
			currentDelayMS = 200;               

			// All LEDs alternating in hue spectrum
			y++;
			if (y >= (strip.numPixels() * 8) )
			{
				y = 0;
			}
			strip.fill(strip.ColorHSV((y * 65536 / strip.numPixels() / 8) , 255, 30), 0, 0);
		}
	}

	// One time animation for volume change
	if (lsrAnimationMode == 2)
	{
		y = 0;
		currentDelayMS = 3000;

		volumeScope = (animConfig.volumeMax - animConfig.volumeMin);
		volumeScopeAmount = (animConfig.volume - animConfig.volumeMin) * (LED_COUNT - 1) / volumeScope; // Lautstärkenanzeige angepasst an die Anzahl der LEDs

		defineColors_GreenToRed();
		
		// percentual volume animation
		strip.clear();
		x = 0;
		do
		{
			for (i = 0; i < volumeScopeAmount + 1; i++)
			{
				strip.setPixelColor(i, lsrColorR[i], lsrColorG[i], lsrColorB[i]);
			}
			x++;
		}
		while (x < (volumeScopeAmount + 1));
	}
}



