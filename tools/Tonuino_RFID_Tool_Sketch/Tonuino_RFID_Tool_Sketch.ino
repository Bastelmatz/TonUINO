#include <MFRC522.h>
#include <SPI.h>
#include <avr/sleep.h>

/*
   _____         _____ _____ _____ _____
  |_   _|___ ___|  |  |     |   | |     |
    | | | . |   |  |  |-   -| | | |  |  |
    |_| |___|_|_|_____|_____|_|___|_____|
    TonUINO Version 2.1

    created by Thorsten Voß and licensed under GNU/GPL.
    Information and contribution at https://tonuino.de.
*/

static const uint32_t cardCookie = 322417479;

struct folderSettings {
  uint8_t folder;
  uint8_t mode;
  uint8_t special;
  uint8_t special2;
};

// this object stores nfc tag data
struct nfcTagObject {
  uint32_t cookie;
  uint8_t version;
  folderSettings nfcFolderSettings;
};
 
nfcTagObject tempCard;

void writeCard(nfcTagObject nfcTag);
void dump_byte_array(byte * buffer, byte bufferSize);

// MFRC522
#define RST_PIN 9                 // Configurable, see typical pin layout above
#define SS_PIN 10                 // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522
MFRC522::MIFARE_Key key;
const byte sector = 1;
const byte blockAddr = 4;
const byte trailerBlock = 7;
MFRC522::StatusCode status;

void setup() 
{
  Serial.begin(115200); // Es gibt ein paar Debug Ausgaben über die serielle Schnittstelle

  // Dieser Hinweis darf nicht entfernt werden
  Serial.println(F("\n _____         _____ _____ _____ _____"));
  Serial.println(F("|_   _|___ ___|  |  |     |   | |     |"));
  Serial.println(F("  | | | . |   |  |  |-   -| | | |  |  |"));
  Serial.println(F("  |_| |___|_|_|_____|_____|_|___|_____|\n"));
  Serial.println(F("TonUINO RFID Tool"));
  Serial.println(F("created by Bastelmatz."));

  // NFC Leser initialisieren
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

bool cardSerialFound()
{
  bool found = mfrc522.PICC_ReadCardSerial();
  return found;
}

bool cardDetected()
{
  bool detected = mfrc522.PICC_IsNewCardPresent();
  return detected;
}

static bool hasMusicCard = false;
static bool hasModifierCard = false;
static bool hasAnyCard() { return hasMusicCard || hasModifierCard; }

static byte lastMusicCardUid[4];
static byte retries;
const byte maxRetries = 2;
static bool lastMusicCardWasUL;
static bool lastModifierCardWasUL;

const byte MUSICCARD_NO_CHANGE = 0; // no change detected since last pollCard() call
const byte MUSICCARD_NEW       = 1; // card with new UID detected (had no card or other card before)
const byte ALLCARDS_GONE       = 2; // card is not reachable anymore
const byte MUSICCARD_IS_BACK   = 3; // card was gone, and is now back again


byte pollCard()
{
  if (hasAnyCard())
  {
    if (isCardGone())
    {
      hasMusicCard = false;
      hasModifierCard = false;
         
      // transmit card removal 
      // this information is required for Tonuino RFID Tool
      transmitRFIDToolTrigger(true);
      Serial.println("CardData"); // no further data is available/required here
      transmitRFIDToolTrigger(false);
      
      return ALLCARDS_GONE;
    }
  }
  else
  {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && readCard())
    {
      retries = maxRetries;
      bool currentCardIsUL = mfrc522.PICC_GetType(mfrc522.uid.sak) == MFRC522::PICC_TYPE_MIFARE_UL;
      bool isModifierCard = tempCard.cookie == cardCookie && tempCard.nfcFolderSettings.folder == 0;
      if (isModifierCard)
      {
        hasModifierCard = true;
        lastModifierCardWasUL = currentCardIsUL;
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

bool isCardGone()
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
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
        return true;
    }
  }
  return false;
}

bool isSameMusicCardAsLastOne()
{ 
  bool bSameUID = !memcmp(lastMusicCardUid, mfrc522.uid.uidByte, 4);
  Serial.print(F("IsSameAsLastMusicCardUID="));
  Serial.println(bSameUID);
  // store info about current card
  memcpy(lastMusicCardUid, mfrc522.uid.uidByte, 4);
  return bSameUID;
}

void handleCardReader()
{
  // poll card only every 100ms
  static uint8_t lastCardPoll = 0;
  uint8_t now = millis();

  if (static_cast<uint8_t>(now - lastCardPoll) > 100)
  {
    lastCardPoll = now;
    switch (pollCard())
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
}

char readSerialString[20];

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

  writeCard(tempCard);
  delay(100);
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  // force new card detection
  transmitCardData(tempCard);
  hasMusicCard = false;
  hasModifierCard = false;
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

void loop() 
{
    listenToRFIDTool();
    
    handleCardReader();
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

bool readCard() 
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
    byte pACK[] = {0, 0}; //16 bit PassWord ACK returned by the tempCard
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

  tempCard.cookie = tempCookie;
  tempCard.version = buffer[4];
  tempCard.nfcFolderSettings.folder = buffer[5];
  tempCard.nfcFolderSettings.mode = buffer[6];
  tempCard.nfcFolderSettings.special = buffer[7];
  tempCard.nfcFolderSettings.special2 = buffer[8];

  // transmit data over serial for Tonuino RFID Tool
  transmitCardData(tempCard);
  
  return true;
}

void writeCard(nfcTagObject nfcTag) 
{
  byte buffer[16] = {0x13, 0x37, 0xb3, 0x47, // 0x1337 0xb347 magic cookie to identify our nfc tags
                     0x02,                   // version 1
                     nfcTag.nfcFolderSettings.folder,  // the folder picked by the user
                     nfcTag.nfcFolderSettings.mode,    // the playback mode picked by the user
                     nfcTag.nfcFolderSettings.special, // track or function for admin cards
                     nfcTag.nfcFolderSettings.special2,
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
    return;
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
