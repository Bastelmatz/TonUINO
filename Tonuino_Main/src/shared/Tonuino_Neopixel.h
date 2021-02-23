
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

struct AnimationConfig
{
	uint8_t mode;
	
	uint8_t volume;
	uint8_t volumeMin;
	uint8_t volumeMax;
	
	bool musicLoaded;
	bool musicLoading;
	bool musicPlaying;
};

class TonuinoNeopixel
{
	public:
		void setup(uint8_t ledCount, uint8_t dataPin);
		void turnOff();
		void animate();
		
		Adafruit_NeoPixel strip;
		AnimationConfig animConfig;
		bool limitedAnimationFinished;
		
	private:
		void defineAnimation();
		void defineColors_GreenToRed();
		void defineColors_Rainbow();
		
		long lastAnimationTimeMS;
		uint16_t currentDelayMS;
		uint8_t updateCounter;
		uint8_t updateCounterTarget;
		uint8_t y;
		uint8_t i;

		uint8_t lastDetectedVolume;     
		uint8_t volumeScope;             
		uint8_t volumeScopeAmount;       
		uint32_t lsrHueCalc;             
		uint32_t lsrColors;      

		#define LED_COUNT 12   // this value must be >= number of leds (no harm if it is greater except from memory consumption)
		uint8_t lsrColorR[LED_COUNT];    
		uint8_t lsrColorG[LED_COUNT];    
		uint8_t lsrColorB[LED_COUNT];  
		};
