#include <MFRC522.h>
#include <SPI.h>
#include <avr/sleep.h>

#include "Tonuino_Structs.h"

// prevent multiple definitions
#ifndef TONUINO_RFID_INCLUDED
#define TONUINO_RFID_INCLUDED

// MFRC522
#define RST_PIN 9
#define SS_PIN 10
static MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522
const byte sector = 1;
const byte blockAddr = 4;
const byte trailerBlock = 7;

const byte MUSICCARD_NO_CHANGE = 0; // no change detected since last pollCard() call
const byte MUSICCARD_NEW       = 1; // music card with new UID detected (had no card or other card before)
const byte MODIFIERCARD_NEW    = 2; // modifier card is detected
const byte ALLCARDS_GONE       = 3; // no card is reachable anymore
const byte MUSICCARD_IS_BACK   = 4; // music card was gone, and is now back again
	
void dump_byte_array(byte * buffer, byte bufferSize); 
	
	
class Tonuino_RFID_Reader
{
public:
	static bool hasMusicCard;
	static bool hasModifierCard;

	nfcTagStruct readCardData;

	// Card detection
	bool hasAnyCard();
	static byte lastMusicCardUid[4];
	static byte currentCardUid[4];
	static byte retries;
	static const byte maxRetries = 2;
	static bool lastMusicCardWasUL;
	static bool lastModifierCardWasUL;

	void setupRFID();

	bool cardSerialFound();
	bool cardDetected();
	void haltAndStop();
	
	byte tryPollCard();

	bool writeCard(MusicDataset musicDS);

private:
	MFRC522::MIFARE_Key key;
	MFRC522::StatusCode status;
	bool isMifareUL;
	
	byte pollCard();
	bool isCardGone();
	bool isSameMusicCardAsLastOne();
	bool readCard();
	bool tryAuthenticate();
};

#endif