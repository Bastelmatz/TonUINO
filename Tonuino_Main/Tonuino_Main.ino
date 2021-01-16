
// HOW TO: including files
// - from the libraries folder, and subfolders, uses <> around the path/file name.
// - from the sketch folder, and subfolders, uses "" around the path/file name.
// + local includes from included files must be stated here already

#include "src/Tonuino_Defines_Tools.h"

// ******************************************
//  Tonuino Tool
// ******************************************

#ifdef TONUINO_RFID_TOOL

#include "src/Tonuino_RFID_Tool.h";

// local includes from included files must be stated here already
#include "src/shared/Tonuino_RFID.h"

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

#include "src/Tonuino_Mira.h";

void setup()
{
  setupTonuino();
}

void loop()
{
  loopTonuino();
}

#endif
