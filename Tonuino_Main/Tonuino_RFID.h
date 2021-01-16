#include <MFRC522.h>
#include <SPI.h>
#include <avr/sleep.h>

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
 
static nfcTagObject readCardData;

// MFRC522
#define RST_PIN 9                 // Configurable, see typical pin layout above
#define SS_PIN 10                 // Configurable, see typical pin layout above
static MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522
static MFRC522::MIFARE_Key key;
const byte sector = 1;
const byte blockAddr = 4;
const byte trailerBlock = 7;
static MFRC522::StatusCode status;

// Card detection
static bool hasMusicCard = false;
static bool hasModifierCard = false;
static bool hasAnyCard();
static byte lastMusicCardUid[4];
static byte retries;
const byte maxRetries = 2;
static bool lastMusicCardWasUL;
static bool lastModifierCardWasUL;

const byte MUSICCARD_NO_CHANGE = 0; // no change detected since last pollCard() call
const byte MUSICCARD_NEW       = 1; // music card with new UID detected (had no card or other card before)
const byte MODIFIERCARD_NEW    = 2; // modifier card is detected
const byte ALLCARDS_GONE       = 2; // no card is reachable anymore
const byte MUSICCARD_IS_BACK   = 3; // music card was gone, and is now back again

void setupRFID();

bool cardSerialFound();
bool cardDetected();

byte pollCard();
bool isCardGone();
bool isSameMusicCardAsLastOne();
byte tryPollCard();

bool readCard();
void writeCard(nfcTagObject nfcTag);
void dump_byte_array(byte * buffer, byte bufferSize); 
