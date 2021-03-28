
#include "Tonuino_RFID_Tool_Core.h"
#include <SPI.h>
#include <avr/sleep.h>

char Tonuino_RFID_Tool_Core::readSerialString[READBYTESMAX];

void Tonuino_RFID_Tool_Core::transmitTrigger(bool startTrigger)
{
	// this information is required for Tonuino RFID Tool
	if (startTrigger)
	{
		Serial.println(F("Tonuino_RFID_Tool_BEGIN"));
	}
	else
	{
		Serial.println(F("Tonuino_RFID_Tool_END"));
	}
}

void Tonuino_RFID_Tool_Core::transmitCardData(nfcTagStruct nfcTag)
{
	// this information is required for Tonuino RFID Tool
	// the formatting and order of the transmitted data is defined and must be in sync with the tool
	transmitTrigger(true);
	Serial.println(F("CardData"));
	Serial.print(F("RFID:"));
	//dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size); // doesn't work anymore for some reason
	dump_byte_array(tonuinoRFID.currentCardUid, sizeof(tonuinoRFID.currentCardUid));
	Serial.println();
	Serial.print(F("Cookie:"));
	Serial.println(nfcTag.cookie);
	Serial.print(F("Folder:"));
	Serial.println(nfcTag.musicDS.folder);
	Serial.print(F("Mode:"));
	Serial.println(nfcTag.musicDS.mode);
	Serial.print(F("Special:"));
	Serial.println(nfcTag.musicDS.special);
	Serial.print(F("Special2:"));
	Serial.println(nfcTag.musicDS.special2);
	transmitTrigger(false);
}

void Tonuino_RFID_Tool_Core::transmitCardRemoval()
{
	transmitTrigger(true);
	Serial.println(F("CardData"));
	transmitTrigger(false);
}

void Tonuino_RFID_Tool_Core::writeCard(MusicDataset musicDS)
{
	tonuinoRFID.setupRFID();
	
	Serial.println(F("Wait 10s for card..."));
	long startTime = millis();
	do {
		if (millis() - startTime > 10000)
		{
			Serial.println(F("Wait for card aborted!"));
			break;
		}
		delay (10);
	} while (!tonuinoRFID.cardDetected());
	if (!tonuinoRFID.cardSerialFound())
	{
		Serial.println(F("No card serial found!"));
		return;
	}
	
	bool success = false;
	if (musicDS.mode == 0 && 
	    musicDS.folder == 0 && 
		musicDS.special == 0 &&
		musicDS.special2 == 0)
	{
		success = tonuinoRFID.resetCard();
	}
	else
	{
		success = tonuinoRFID.writeCard(musicDS);
	}
	
	if (success)
	{
		Serial.println(F("Card written!"));
	}
	tonuinoRFID.haltAndStop();

	// force new card detection
	tonuinoRFID.hasMusicCard = false;
	tonuinoRFID.hasModifierCard = false;
}

void Tonuino_RFID_Tool_Core::handleCommand()
{
	Serial.println(F("RFID_Tool_Command_Received"));
	Serial.println(readSerialString);

	MusicDataset receivedDS;
	int index = 0;
	char* command = strtok(readSerialString, ";");
	while(command != NULL) 
	{
		int charToInt = atoi(command);
		byte parsedByte = (byte)charToInt;
		switch (index)
		{
			case 0: receivedDS.folder = parsedByte; break;
			case 1: receivedDS.mode = parsedByte; break;
			case 2: receivedDS.special = parsedByte; break;
			case 3: receivedDS.special2 = parsedByte; break;
		}
		index++;
		// create next part
		command = strtok(NULL, ";");
	}

	Serial.println(receivedDS.folder);
	Serial.println(receivedDS.mode);
	Serial.println(receivedDS.special);
	Serial.println(receivedDS.special2);

	MusicDataset musicDS;
	musicDS.folder = receivedDS.folder;
	musicDS.special = receivedDS.special;
	musicDS.special2 = receivedDS.special2;
	musicDS.mode = receivedDS.mode;

	writeCard(musicDS);
}

void Tonuino_RFID_Tool_Core::listen()
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
		handleCommand();
		for (uint8_t i = 0; i < sizeof(readSerialString); ++i)
		{
		  readSerialString[i] = (char)0;
		}
	}
}



