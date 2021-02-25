
// HOW TO: including files
// - from the libraries folder, and subfolders, uses <> around the path/file name.
// - from the sketch folder, and subfolders, uses "" around the path/file name.

#include "src/Tonuino_Defines_Tools.h"

// ******************************************
//  Tonuino Tool
// ******************************************

#ifdef TONUINO_RFID_TOOL

#include "src/Tonuino_RFID_Tool.h"

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

#include "src/Tonuino_Mira.h"

void setup()
{
  setupMira();
}

void loop()
{
  loopMira();
}

#endif

// ******************************************
//  Tonuino Mira Coinbox
// ******************************************

#ifdef TONUINO_MIRA_COINBOX

#include "src/Tonuino_Mira_Coinbox.h"

void setup()
{
  setupMira();
}

void loop()
{
  loopMira();
}

#endif

// ******************************************
//  Tonuino Mira Troy
// ******************************************

#ifdef TONUINO_MIRA_TROY

#include "src/Tonuino_Mira_Troy.h"

void setup()
{
  setupMira();
}

void loop()
{
  loopMira();
}

#endif
