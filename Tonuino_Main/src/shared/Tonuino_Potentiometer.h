
#include <SPI.h>

class TonuinoPotentiometer
{
	public:
	void setup(int pin, int min, int max);
	bool read();
	static int appliedValue; 
	
	private:
	static int pin;
	static int min;
	static int max;
	static int lastValue; 
	static int hysterese;
};
