#include <MFRC522.h>
#include <SPI.h>
#include <avr/sleep.h>

// prevent multiple definitions
#ifndef TONUINO_RFID_INCLUDED
#define TONUINO_RFID_INCLUDED

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

// MFRC522
#define RST_PIN 9
#define SS_PIN 10
static MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522
static MFRC522::MIFARE_Key key;
const byte sector = 1;
const byte blockAddr = 4;
const byte trailerBlock = 7;
static MFRC522::StatusCode status;


const byte MUSICCARD_NO_CHANGE = 0; // no change detected since last pollCard() call
const byte MUSICCARD_NEW       = 1; // music card with new UID detected (had no card or other card before)
const byte MODIFIERCARD_NEW    = 2; // modifier card is detected
const byte ALLCARDS_GONE       = 3; // no card is reachable anymore
const byte MUSICCARD_IS_BACK   = 4; // music card was gone, and is now back again
	
void dump_byte_array(byte * buffer, byte bufferSize); 
	
	
class Tonuino_RFID_Reader
{
public:
	bool hasMusicCard = false;
	bool hasModifierCard = false;

	nfcTagObject readCardData;

	// Card detection
	bool hasAnyCard();
	byte lastMusicCardUid[4];
	byte currentCardUid[4];
	byte retries;
	const byte maxRetries = 2;
	bool lastMusicCardWasUL;
	bool lastModifierCardWasUL;

	void setupRFID();

	bool cardSerialFound();
	bool cardDetected();
	void haltAndStop();
	
	byte tryPollCard();

	bool writeCard(nfcTagObject nfcTag);

private:
	byte pollCard();
	bool isCardGone();
	bool isSameMusicCardAsLastOne();
	bool readCard();
};

#endif