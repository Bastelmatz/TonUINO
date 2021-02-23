
#include "Tonuino_RFID.h"
#include "Tonuino_EEPROM.h"
#include "Tonuino_Player.h"
#include "Tonuino_DFPlayer.h"
#include "Tonuino_Modifiers.h"
#include "Tonuino_Config.h"
#include "Tonuino_Buttons.h"
#include "Tonuino_Potentiometer.h"
#include "Tonuino_RotaryEncoder.h"
#include "Tonuino_UltraSonic.h"
#include "Tonuino_Neopixel.h"

#include <SPI.h>

void loopTonuino();
void setupTonuino(TonuinoConfig config);

uint8_t getLastTrack(MusicDataset folder);
void loadAndPlayFolder(MusicDataset theFolder);
void loadFolder(MusicDataset theFolder);
bool setupFolder(MusicDataset * theFolder);

void onNewCard();
void onCardGone();
void onCardReturn();
void setupCard();
void writeCard(nfcTagStruct nfcTag);
void resetCard();

void evaluateModifierData(MusicDataset musicDS);
void handleModifier(EModifier modifier, uint8_t special);