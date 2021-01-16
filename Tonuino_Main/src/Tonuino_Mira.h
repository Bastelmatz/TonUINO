
void loopTonuino();
void setupTonuino();

#include <avr/sleep.h>

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
  //  uint8_t folder;
  //  uint8_t mode;
  //  uint8_t special;
  //  uint8_t special2;
};

void setstandbyTimer();
void disablestandbyTimer();
void loadAndPlayFolder();
void loadFolder();
bool setupFolder(folderSettings * theFolder);

bool isCardGone();
void onNewCard();
bool readCard();
void setupCard();
void resetCard();

bool evaluateCardData(nfcTagObject tempCard, nfcTagObject * nfcTag);
bool isSameMusicCardAsLastOne();

bool askCode(uint8_t *code);
