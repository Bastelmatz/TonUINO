
#include "Tonuino_Config.h"

class TonuinoPotentiometer
{
	public:
	void setup();
	int read();
	
	private:
	static int hysterese; 
	static int lastValue; 
};
