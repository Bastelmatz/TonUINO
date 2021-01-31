
#include "Tonuino_Config.h"

class TonuinoPotentiometer
{
	public:
	void setup(int pin);
	bool read();
	static int appliedValue; 
	
	private:
	static int pin;
	static int lastValue; 
	static int hysterese;
};
