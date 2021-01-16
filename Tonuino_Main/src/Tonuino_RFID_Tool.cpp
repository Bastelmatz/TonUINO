
#include "Tonuino_Defines_Tools.h"

#ifdef TONUINO_RFID_TOOL

#include "shared/Tonuino_RFID.h"
#include <SPI.h>
#include <avr/sleep.h>

char readSerialString[20];

Tonuino_RFID_Reader tonuinoRFID;

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

  tonuinoRFID.setupRFID();
}

void transmitRFIDToolTrigger(bool startTrigger)
{
  // this information is required for Tonuino RFID Tool
  if (startTrigger)
  {
	Serial.println("Tonuino_RFID_Tool_BEGIN");
  }
  else
  {
	Serial.println("Tonuino_RFID_Tool_END");
  }
}

void transmitCardData(nfcTagObject nfcTag)
{
  // this information is required for Tonuino RFID Tool
  // the formatting and order of the transmitted data is defined and must be in sync with the tool
  transmitRFIDToolTrigger(true);
  Serial.println("CardData");
  Serial.print("RFID:");
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  Serial.print("Cookie:");
  Serial.println(nfcTag.cookie);
  Serial.print("Folder:");
  Serial.println(nfcTag.nfcFolderSettings.folder);
  Serial.print("Mode:");
  Serial.println(nfcTag.nfcFolderSettings.mode);
  Serial.print("Special:");
  Serial.println(nfcTag.nfcFolderSettings.special);
  Serial.print("Special2:");
  Serial.println(nfcTag.nfcFolderSettings.special2);
  transmitRFIDToolTrigger(false);
}

void handleRFIDToolCommand()
{
  Serial.println("RFID_Tool_Command_Received");
  Serial.println(readSerialString);

  folderSettings receivedFS;
  int index = 0;
  char* command = strtok(readSerialString, ";");
  while(command != NULL) 
  {
	int charToInt = atoi(command);
	byte parsedByte = (byte)charToInt;
	switch (index)
	{
	  case 0: receivedFS.folder = parsedByte; break;
	  case 1: receivedFS.mode = parsedByte; break;
	  case 2: receivedFS.special = parsedByte; break;
	  case 3: receivedFS.special2 = parsedByte; break;
	}
	index++;
	// create next part
	command = strtok(NULL, ";");
  }

  Serial.println(receivedFS.folder);
  Serial.println(receivedFS.mode);
  Serial.println(receivedFS.special);
  Serial.println(receivedFS.special2);

  nfcTagObject tempCard;
  tempCard.cookie = cardCookie;
  tempCard.version = 1;
  tempCard.nfcFolderSettings.folder = receivedFS.folder;
  tempCard.nfcFolderSettings.special = receivedFS.special;
  tempCard.nfcFolderSettings.special2 = receivedFS.special2;
  tempCard.nfcFolderSettings.mode = receivedFS.mode;

  tonuinoRFID.writeCard(tempCard);
  delay(100);
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  // force new card detection
  transmitCardData(tempCard);
  tonuinoRFID.hasMusicCard = false;
  tonuinoRFID.hasModifierCard = false;
}

void handleCardReader()
{
  byte pollCardResult = tonuinoRFID.tryPollCard();

  if (pollCardResult == MODIFIERCARD_NEW || pollCardResult == MUSICCARD_NEW)
  {
  	// transmit data over serial for Tonuino RFID Tool
  	transmitCardData(tonuinoRFID.readCardData);
  }
  switch (pollCardResult)
  {
	case MUSICCARD_NEW:
		// placeholder: do something on new card detection
		break;

	case ALLCARDS_GONE:
		// placeholder: do something if all cards are gone
		break;

	case MUSICCARD_IS_BACK:
		// placeholder: do somethind if music card is back
		break;
  }    
}

void listenToRFIDTool()
{
	byte index = 0;
	while (Serial.available()) 
	{
		if (index > sizeof(readSerialString))
		{
			break;
		}
		delay(3);  
		char c = Serial.read();
		readSerialString[index] = c; 
		index++;
	}
	if (index > 0)
	{
		handleRFIDToolCommand();
		for(int i = 0; i < sizeof(readSerialString); ++i)
		{
		  readSerialString[i] = (char)0;
		}
	}
}

void loopTool() 
{
	listenToRFIDTool();
	
	handleCardReader();
}

#endif
