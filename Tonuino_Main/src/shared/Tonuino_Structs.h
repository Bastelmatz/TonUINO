
#include <SPI.h>

// prevent multiple definitions
#ifndef TONUINO_STRUCTS_INCLUDED
#define TONUINO_STRUCTS_INCLUDED

static const uint32_t cardCookie = 322417479; // 0x1337 0xb347 magic cookie to identify our nfc tags

struct MusicDataset 
{
	uint8_t mode;
	uint8_t startFolder;
	uint8_t startTrack;
	uint8_t endFolder;
	uint8_t endTrack;
};

// this object stores nfc tag data
struct nfcTagStruct 
{
	uint32_t cookie;
	uint8_t version;
	MusicDataset musicDS;
};

struct TONUINO_STRUCTS
{
	static void print(MusicDataset musicDS)
	{
		Serial.print(F("Mode: "));
		Serial.println(musicDS.mode);
		Serial.print(F("Start folder: "));
		Serial.println(musicDS.startFolder);
		Serial.print(F("Start track: "));
		Serial.println(musicDS.startTrack);
		Serial.print(F("End folder: "));
		Serial.println(musicDS.endFolder);
		Serial.print(F("End track: "));
		Serial.println(musicDS.endTrack);
	}
};

#endif