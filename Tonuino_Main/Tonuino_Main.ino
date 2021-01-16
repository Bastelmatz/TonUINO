
// HOW TO: including files
// - from the libraries folder, and subfolders, uses <> around the path/file name.
// - from the sketch folder, and subfolders, uses "" around the path/file name.

#include "Tonuino_Defines.h"

// ******************************************
//  Tonuino Tool
// ******************************************

#ifdef TONUINO_RFID_TOOL

#include "Tonuino_RFID_Tool.h";

void setup()
{
  setupTool();
}

void loop()
{
  loopTool();
}
#endif

// ******************************************
//  Tonuino Mira
// ******************************************

#ifdef TONUINO_MIRA

#include "Tonuino_Mira.h";

void setup()
{
  setupTonuino();
}

void loop()
{
  loopTonuino();
}

#endif
