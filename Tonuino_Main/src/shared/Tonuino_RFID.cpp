
#include "Tonuino_RFID.h"

bool Tonuino_RFID_Reader::hasMusicCard = false;
bool Tonuino_RFID_Reader::hasModifierCard = false;

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
	  hasMusicCard = false;
	  hasModifierCard = false;
		 
	  return ALLCARDS_GONE;
	}
  }
  else
  {
	if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && readCard())
	{
	  retries = maxRetries;
	  bool currentCardIsUL = mfrc522.PICC_GetType(mfrc522.uid.sak) == MFRC522::PICC_TYPE_MIFARE_UL;
	  bool isModifierCard = readCardData.cookie == cardCookie && readCardData.musicDS.folder == 0;
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

bool Tonuino_RFID_Reader::readCard() 
{
  // Show some details of the PICC (that is: the tag/card)
  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
  const bool bIsMifareUL = piccType == MFRC522::PICC_TYPE_MIFARE_UL;
  
  byte buffer[18+12];   // add more room at the end so that UL read with offset of up to 12 bytes fits
  byte size = 18;

  // Authenticate using key A
  if (bIsMifareUL)
  {
	byte pACK[] = {0, 0}; //16 bit PassWord ACK returned by the readCardData
	Serial.println(F("Authenticating MIFARE UL..."));
	status = mfrc522.PCD_NTAG216_AUTH(key.keyByte, pACK);
  }
  else // Mifare Mini, 1K, 4K
  {
	Serial.println(F("Authenticating Classic using key A..."));
	status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  }

  if (status != MFRC522::STATUS_OK) 
  {
	Serial.print(F("PCD_Authenticate() failed: "));
	Serial.println(mfrc522.GetStatusCodeName(status));
	return false;
  }

  // Read data from the block
  if (bIsMifareUL)
  {
	// UL cards read 4 bytes at once -> 4 parts for 16 bytes
	for (byte part = 0; part < 4; part++)
	{
	  status = mfrc522.MIFARE_Read(8 + part, buffer + 4 * part, &size);
	  if (status != MFRC522::STATUS_OK) 
	  {
		Serial.print(F("MIFARE_Read() failed: "));
		Serial.println(mfrc522.GetStatusCodeName(status));
		return false;
	  }
	}
  }
  else // Mifare Mini, 1K, 4K
  {
	Serial.print(F("Reading data from block "));
	Serial.print(blockAddr);
	Serial.println(F(" ..."));
	// classic cards read 16 bytes at once
	status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
	if (status != MFRC522::STATUS_OK) 
	{
	  Serial.print(F("MIFARE_Read() failed: "));
	  Serial.println(mfrc522.GetStatusCodeName(status));
	  return false;
	}
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
  readCardData.musicDS.folder = buffer[5];
  readCardData.musicDS.mode = buffer[6];
  readCardData.musicDS.special = buffer[7];
  readCardData.musicDS.special2 = buffer[8];
 
  // store info about current card
  memcpy(currentCardUid, mfrc522.uid.uidByte, 4);

  return true;
}

bool Tonuino_RFID_Reader::writeCard(nfcTagStruct cardData) 
{
  byte buffer[16] = {0x13, 0x37, 0xb3, 0x47, // 0x1337 0xb347 magic cookie to identify our nfc tags
					 0x02,                   // version 1
					 cardData.musicDS.folder,  // the folder picked by the user
					 cardData.musicDS.mode,    // the playback mode picked by the user
					 cardData.musicDS.special, // track or function for admin cards
					 cardData.musicDS.special2,
					 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
					};

  byte size = sizeof(buffer);

  MFRC522::PICC_Type mifareType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  const bool bIsMifareUL = mifareType == MFRC522::PICC_TYPE_MIFARE_UL;
  
  // authentificate with the card and set card specific parameters
  if (bIsMifareUL)
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

  // Write data to the block
  Serial.print(F("Writing data into block "));
  Serial.print(blockAddr);
  Serial.println(F(" ..."));
  dump_byte_array(buffer, 16);
  Serial.println();

  if (bIsMifareUL)
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
