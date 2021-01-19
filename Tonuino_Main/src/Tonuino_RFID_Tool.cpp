
#include "Tonuino_Defines_Tools.h"

#ifdef TONUINO_RFID_TOOL

#include "shared/Tonuino_RFID_Tool_Core.h"

Tonuino_RFID_Tool_Core tonuinoRFIDTool;

void setupTool() 
{
  Serial.begin(115200);

  // Dieser Hinweis darf nicht entfernt werden
  Serial.println(F("\n _____         _____ _____ _____ _____"));
  Serial.println(F("|_   _|___ ___|  |  |     |   | |     |"));
  Serial.println(F("  | | | . |   |  |  |-   -| | | |  |  |"));
  Serial.println(F("  |_| |___|_|_|_____|_____|_|___|_____|\n"));
  Serial.println(F("TonUINO RFID Tool"));
  Serial.println(F("created by Bastelmatz."));
  // give some time to transmit serial
  delay(1000);
  
  tonuinoRFID.setupRFID();
}

void handleCardReader()
{
  byte pollCardResult = tonuinoRFID.tryPollCard();

  if (pollCardResult == MODIFIERCARD_NEW || pollCardResult == MUSICCARD_NEW || pollCardResult == MUSICCARD_IS_BACK)
  {
  	// transmit data over serial for Tonuino RFID Tool
  	tonuinoRFIDTool.transmitCardData(tonuinoRFID.readCardData);
  }
  switch (pollCardResult)
  {
	case MUSICCARD_NEW:
		// placeholder: do something on new card detection
		break;

	case ALLCARDS_GONE:
	{
		tonuinoRFIDTool.transmitCardRemoval();
		break;
	}

	case MUSICCARD_IS_BACK:
		// placeholder: do somethind if music card is back
		break;
  }    
}

void loopTool() 
{
	tonuinoRFIDTool.listen();
	
	handleCardReader();
}

#endif
