
#include "Tonuino_RFID.h"

bool Tonuino_RFID_Reader::hasMusicCard = false;
bool Tonuino_RFID_Reader::hasModifierCard = false;
bool Tonuino_RFID_Reader::lastCardWasModifierCard = false;

byte Tonuino_RFID_Reader::lastMusicCardUid[4];
byte Tonuino_RFID_Reader::currentCardUid[4];
byte Tonuino_RFID_Reader::retries = maxRetries;
bool Tonuino_RFID_Reader::lastMusicCardWasUL = false;
bool Tonuino_RFID_Reader::lastModifierCardWasUL = false;
	
// Card detection
bool Tonuino_RFID_Reader::hasAnyCard() { return hasMusicCard || hasModifierCard; }

void Tonuino_RFID_Reader::setupRFID() 
{
  Serial.begin(115200); // Es gibt ein paar Debug Ausgaben über die serielle Schnittstelle

  // NFC Leser initialisieren
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader
  for (byte i = 0; i < 6; i++) 
  {
	key.keyByte[i] = 0xFF;
  }
}

bool Tonuino_RFID_Reader::cardSerialFound()
{
  bool found = mfrc522.PICC_ReadCardSerial();
  return found;
}

bool Tonuino_RFID_Reader::cardDetected()
{
  bool detected = mfrc522.PICC_IsNewCardPresent();
  return detected;
}

void Tonuino_RFID_Reader::haltAndStop()
{
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

byte Tonuino_RFID_Reader::pollCard()
{
  if (hasAnyCard())
  {
	if (isCardGone())
	{
		lastCardWasModifierCard = hasModifierCard;
		hasMusicCard = false;
		hasModifierCard = false;
		 
		return ALLCARDS_GONE;
	}
  }
  else
  {
	if (cardDetected() && cardSerialFound() && readCard())
	{
	  retries = maxRetries;
	  bool currentCardIsUL = mfrc522.PICC_GetType(mfrc522.uid.sak) == MFRC522::PICC_TYPE_MIFARE_UL;
	  bool isModifierCard = readCardData.cookie == cardCookie && readCardData.musicDS.startFolder == 0;
	  if (isModifierCard)
	  {
		hasModifierCard = true;
		lastModifierCardWasUL = currentCardIsUL;
		return MODIFIERCARD_NEW;
	  }
	  else
	  {
		hasMusicCard = true;
		lastMusicCardWasUL = currentCardIsUL;
		return isSameMusicCardAsLastOne() ? MUSICCARD_IS_BACK : MUSICCARD_NEW;
	  }
	}
	return MUSICCARD_NO_CHANGE;
  }
  return MUSICCARD_NO_CHANGE;
}

bool Tonuino_RFID_Reader::isCardGone()
{
  // perform a dummy read command just to see whether the card is in range
  byte buffer[18];
  byte size = sizeof(buffer);

  bool lastCardWasUL = hasMusicCard ? lastMusicCardWasUL : lastModifierCardWasUL;
  if (mfrc522.MIFARE_Read(lastCardWasUL ? 8 : blockAddr, buffer, &size) == MFRC522::STATUS_OK)
  {
	retries = maxRetries;
  }
  else
  {
	if (retries > 0)
	{
		retries--;
	}
	else
	{
		Serial.println(F("card gone"));
		haltAndStop();
		return true;
	}
  }
  return false;
}

bool Tonuino_RFID_Reader::isSameMusicCardAsLastOne()
{ 
  bool bSameUID = !memcmp(lastMusicCardUid, mfrc522.uid.uidByte, 4);
  Serial.print(F("IsSameAsLastMusicCardUID="));
  Serial.println(bSameUID);
  // store info about current card
  memcpy(lastMusicCardUid, mfrc522.uid.uidByte, 4);
  return bSameUID;
}

byte Tonuino_RFID_Reader::tryPollCard()
{
  // poll card only every 100ms
  static uint8_t lastCardPoll = 0;
  uint8_t now = millis();

  if (static_cast<uint8_t>(now - lastCardPoll) > 100)
  {
	lastCardPoll = now;
	return pollCard();
  }
  return MUSICCARD_NO_CHANGE;
}

bool Tonuino_RFID_Reader::tryAuthenticate()
{
  // Show some details of the PICC (that is: the tag/card)
  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
  
  isMifareUL = piccType == MFRC522::PICC_TYPE_MIFARE_UL;
	
  // authentificate with the card and set card specific parameters
  if (isMifareUL)
  {
	byte pACK[] = {0, 0}; //16 bit PassWord ACK returned by the NFCtag
	Serial.println(F("Authenticating UL..."));
	status = mfrc522.PCD_NTAG216_AUTH(key.keyByte, pACK);
  }
  else // Mifare Mini, 1K, 4K
  {
	Serial.println(F("Authenticating again using key A..."));
	status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  }

  if (status != MFRC522::STATUS_OK) 
  {
	Serial.print(F("PCD_Authenticate() failed: "));
	Serial.println(mfrc522.GetStatusCodeName(status));
	return false;
  }
  return true;
}

bool Tonuino_RFID_Reader::readCard() 
{
	byte buffer[18+12];   // add more room at the end so that UL read with offset of up to 12 bytes fits
	byte size = 18;

	if (!tryAuthenticate()) 
	{
		return false;
	}

	//for (int i = 0; i < 32; i++)
	//{
	//  // Show the whole sector as it currently is
	//Serial.print(F("Current data in sector "));
	//Serial.println(i);
	//mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, i);
	//Serial.println();
	//}

	// Read data from the block
	if (isMifareUL)
	{
		// UL cards read 4 bytes at once -> 4 parts for 16 bytes
		for (byte part = 0; part < 4; part++)
		{
			status = mfrc522.MIFARE_Read(8 + part, buffer + 4 * part, &size);
		}
	}
	else // Mifare Mini, 1K, 4K
	{
		Serial.print(F("Reading data from block "));
		Serial.print(blockAddr);
		Serial.println(F(" ..."));
		// classic cards read 16 bytes at once
		status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
	}
	if (status != MFRC522::STATUS_OK) 
	{
		Serial.print(F("MIFARE_Read() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		return false;
	}
	
	Serial.print(F("Data on Card "));
	Serial.println(F(":"));
	dump_byte_array(buffer, 16);
	Serial.println();
	Serial.println();

	uint32_t tempCookie;
	tempCookie = (uint32_t)buffer[0] << 24;
	tempCookie += (uint32_t)buffer[1] << 16;
	tempCookie += (uint32_t)buffer[2] << 8;
	tempCookie += (uint32_t)buffer[3];

	readCardData.cookie = tempCookie;
	readCardData.version = buffer[4];
	readCardData.musicDS.startFolder = buffer[5];
	readCardData.musicDS.mode = buffer[6];
	readCardData.musicDS.startTrack = (buffer[12] << 8) | buffer[7];
	readCardData.musicDS.endTrack = (buffer[13] << 8) | buffer[8];
	readCardData.musicDS.endFolder = buffer[9];
	readCardData.musicDS.recentTrack = (buffer[14] << 8) | buffer[10];
	readCardData.musicDS.recentFolder = buffer[11];
	
	// store info about current card
	memcpy(currentCardUid, mfrc522.uid.uidByte, 4);

	return true;
}

bool Tonuino_RFID_Reader::resetCard()
{
	byte buffer[16] = { 0 };
	return writeCard(buffer);
} 

bool Tonuino_RFID_Reader::writeCard(MusicDataset musicDS) 
{
	byte buffer[16] = {(cardCookie >> 24) & 0xff,
					 (cardCookie >> 16) & 0xff,
					 (cardCookie >> 8) & 0xff,
					 (cardCookie) & 0xff,
					 2,   
					 musicDS.startFolder,  
					 musicDS.mode,         
					 static_cast<byte>(musicDS.startTrack & 0xff),   
					 static_cast<byte>(musicDS.endTrack & 0xff),
					 musicDS.endFolder,
					 static_cast<byte>(musicDS.recentTrack & 0xff),
					 musicDS.recentFolder,
					 static_cast<byte>((musicDS.startTrack >> 8) & 0xff),
					 static_cast<byte>((musicDS.endTrack >> 8) & 0xff),
					 static_cast<byte>((musicDS.recentTrack >> 8) & 0xff),
					 0x00
					};
	return writeCard(buffer);
}

bool Tonuino_RFID_Reader::writeCard(byte buffer[16]) 
{
	if (!tryAuthenticate()) 
	{
		return false;
	}

	// Write data to the block
	Serial.print(F("Writing data into block "));
	Serial.print(blockAddr);
	Serial.println(F(" ..."));
	dump_byte_array(buffer, 16);
	Serial.println();

	if (isMifareUL)
	{
		byte buffer2[16];
		byte size2 = sizeof(buffer2);

		for (byte part = 0; part < 4; part++)
		{
			memset(buffer2, 0, size2);
			memcpy(buffer2, buffer + (4 * part), 4);
			status = mfrc522.MIFARE_Write(8 + part, buffer2, 16);
		}
	}
	else // Mifare Mini, 1K, 4K
	{
		status = mfrc522.MIFARE_Write(blockAddr, buffer, 16);
	}

	if (status != MFRC522::STATUS_OK) 
	{
		Serial.print(F("MIFARE_Write() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
	}
	Serial.println();
	delay(2000);

	return status == MFRC522::STATUS_OK;
}

/**
  Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) 
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
