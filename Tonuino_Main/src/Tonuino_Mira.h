
#include <avr/sleep.h> // for byte type
#include "shared/Tonuino_RFID.h"
#include "shared/Tonuino_EEPROM.h"
#include "shared/Tonuino_Player.h"
#include <SPI.h>

void loopTonuino();
void setupTonuino();

void setstandbyTimer();
void disablestandbyTimer();
void loadAndPlayFolder();
void loadFolder();
bool setupFolder(folderSettings * theFolder);

void onNewCard();
void setupCard();
void resetCard();

bool evaluateCardData(nfcTagObject tempCard, nfcTagObject * nfcTag);

bool askCode(uint8_t *code);
