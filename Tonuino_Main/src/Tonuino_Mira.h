
#include <avr/sleep.h> // for byte type
#include "shared/Tonuino_RFID.h"
#include "shared/Tonuino_EEPROM.h"
#include "shared/Tonuino_Player.h"
#include "shared/Tonuino_DFPlayer.h"
#include <SPI.h>

void loopTonuino();
void setupTonuino();

uint8_t getLastTrack(musicDataset folder);
void loadAndPlayFolder(musicDataset theFolder);
void loadFolder(musicDataset theFolder);
bool setupFolder(musicDataset * theFolder);

void onNewCard();
void setupCard();
void resetCard();

bool evaluateCardData(nfcTagStruct tempCard, nfcTagStruct nfcTag);

bool askCode(uint8_t *code);
