
#include "Tonuino_RFID.h"

static Tonuino_RFID_Reader tonuinoRFID;

class Tonuino_RFID_Tool_Core
{
	public:
	#define READBYTESMAX 32
	#define WRITEBYTESMAX 16
	static char readSerialString[READBYTESMAX];
	
	void transmitCardData(nfcTagStruct * nfcTag);
	void transmitCardRemoval();
	void listen();
	
	private:
	void transmitTrigger(bool startTrigger);
	void writeCard(byte bytesToWrite[]);
	void handleCommand();
};

 