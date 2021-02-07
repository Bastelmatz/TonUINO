
#include <SPI.h>
#include <DFMiniMp3.h>

#include "Tonuino_Structs.h"

// prevent multiple definitions
#ifndef TONUINO_CONFIG_INCLUDED
#define TONUINO_CONFIG_INCLUDED

static uint8_t CONFIG_StandbyTime = 0;
static uint8_t CONFIG_SleepTime = 0;
static uint8_t CONFIG_VolumeInit = 10;
static uint8_t CONFIG_VolumeMin = 1;
static uint8_t CONFIG_VolumeMax = 25;
static DfMp3_Eq CONFIG_Equalizer = DfMp3_Eq_Normal;

static bool CONFIG_UseCardReader = false;
static bool CONFIG_UsePowerOff = false;
static bool CONFIG_HasPotentiometer = true;
static bool CONFIG_HasUltraSonic = true;

static bool CONFIG_StopPlayOnCardRemoval = false;

static MusicDataset CONFIG_ShortCuts[4];
  
#define LONG_PRESS 1000

#define PIN_ButtonPause A1
#define PIN_ButtonNext A3
#define PIN_ButtonPrevious A4
#define PIN_StopLED 6
#define PIN_Shutdown 7
#define PIN_SonicTrigger 5 
#define PIN_SonicEcho 8 
#define PIN_OpenAnalog A6

#define PIN_Poti A2  // 10kOhm Poti

#endif