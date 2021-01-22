
#include <avr/sleep.h> // for byte type
#include "shared/Tonuino_RFID.h"
#include "shared/Tonuino_EEPROM.h"
#include "shared/Tonuino_Player.h"
#include "shared/Tonuino_DFPlayer.h"
#include <SPI.h>

void loopTonuino();
void setupTonuino();

uint8_t getLastTrack(folderSettings folder);
void loadAndPlayFolder(folderSettings theFolder);
void loadFolder(folderSettings theFolder);
bool setupFolder(folderSettings * theFolder);

void onNewCard();
void setupCard();
void resetCard();

bool evaluateCardData(nfcTagObject tempCard, nfcTagObject nfcTag);

bool askCode(uint8_t *code);
