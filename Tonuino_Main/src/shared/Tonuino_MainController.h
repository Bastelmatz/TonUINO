
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
void writeCard(MusicDataset musicDS);
void resetCard();

void evaluateModifierCardData(MusicDataset musicDS, bool isCardRemoval);
void handleModifier(EModifier modifier, uint16_t special);
void handleModifier(EModifier modifier, uint16_t special, bool isCardRemoval);