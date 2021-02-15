
#include <SPI.h>

class TonuinoPotentiometer
{
	public:
	void setup(int pin, int min, int max);
	bool read();
	int appliedValue = 0; 
	
	private:
	int pin = 0;
	int min = 0;
	int max = 0;
	int hysterese = 1;
};
