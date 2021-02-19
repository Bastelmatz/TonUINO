
#include <SPI.h>

// prevent multiple definitions
#ifndef TONUINO_STRUCTS_INCLUDED
#define TONUINO_STRUCTS_INCLUDED

static const uint32_t cardCookie = 322417479; // 0x1337 0xb347 magic cookie to identify our nfc tags

struct MusicDataset 
{
	uint8_t folder;
	uint8_t mode;
	uint8_t special;
	uint8_t special2;
};

// this object stores nfc tag data
struct nfcTagStruct 
{
	uint32_t cookie;
	uint8_t version;
	MusicDataset musicDS;
};

#endif