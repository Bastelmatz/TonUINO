
#include <SPI.h>

class TonuinoUltraSonic
{
	public:
	void setup(uint8_t triggerPIN, uint8_t echoPIN);
	uint16_t read();
	
	private:
	uint8_t pinTrigger = 0;
	uint8_t pinEcho = 0;
};
