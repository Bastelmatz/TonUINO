
#include "Tonuino_Config.h"

class TonuinoPotentiometer
{
	public:
	void setup(int pin);
	int read();
	
	private:
	static int pin;
	static int hysterese; 
	static int lastValue; 
};
