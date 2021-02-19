
#include <SPI.h>

class TonuinoPotentiometer
{
	public:
	void setup(uint8_t pin, uint8_t min, uint8_t max);
	bool read();
	uint8_t appliedValue = 0; 
	
	private:
	uint8_t pin = 0;
	uint8_t min = 0;
	uint8_t max = 0;
	uint8_t hysterese = 1;
};
