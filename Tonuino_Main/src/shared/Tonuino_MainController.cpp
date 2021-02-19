
#include "Tonuino_MainController.h"

#include <MFRC522.h>
#include <avr/sleep.h>

/*
   _____         _____ _____ _____ _____
  |_   _|___ ___|  |  |     |   | |     |
    | | | . |   |  |  |-   -| | | |  |  |
    |_| |___|_|_|_____|_____|_|___|_____|
    TonUINO MIRA Version 1.0.0

    created by Bastelmatz.
*/

TonuinoPinConfig pinConfig;
TonuinoSWConfig swConfig;
TonuinoHWConfig hwConfig;

// RFID reader
Tonuino_RFID_Reader tonuinoRFID;

// DFPlayer Mini
TonuinoDFPlayer dfPlayer;

TonuinoEEPROM tonuinoEEPROM;

TonuinoPotentiometer tonuinoPoti;

TonuinoUltraSonic ultraSonicSensor;
bool handle_sonic = false;

TonuinoButtons tonuinoButtons;

TonuinoRotaryEncoder rotaryEncoder;

uint8_t trackInEEPROM = 0;
nfcTagStruct nextMC;
MusicDataset lastMusicDS;

bool allLocked = false;
bool buttonsLocked = false;

TonuinoPlayer tonuinoPlayer()
{
	return dfPlayer.tonuinoPlayer;
}

void loadStartFolder()
{
	if (swConfig.StartMusicDS.folder == 0)
	{
		lastMusicDS = tonuinoEEPROM.loadLastDatasetFromFlash();
	}
	else
	{
		lastMusicDS = swConfig.StartMusicDS;
	}
}

void setStandbyTimerValue(uint8_t timeInMin)
{
	tonuinoPlayer().standbyTimer.timeInMin = timeInMin;
}

void setSleepTimerValue(uint8_t timeInMin)
{
	tonuinoPlayer().sleepTimer.timeInMin = timeInMin;
}

uint8_t getLastTrack(MusicDataset musicDS)
{
	if (musicDS.mode == AudioBook) 
	{
		trackInEEPROM = tonuinoEEPROM.loadLastTrackFromFlash(musicDS.folder);
		return trackInEEPROM;
	}
	return 0;
}

void loadFolder(MusicDataset musicDS)
{
    uint8_t lastTrack = getLastTrack(musicDS);
	dfPlayer.loadFolder(musicDS, lastTrack);
}

void loadAndPlayFolder(MusicDataset musicDS)
{
	uint8_t lastTrack = getLastTrack(musicDS);
	dfPlayer.loadAndPlayFolder(musicDS, lastTrack);
}

void activateFreezeDance(bool active)
{
	if (dfPlayer.isPlaying()) 
	{
		delay(1000);
		dfPlayer.playAdvertisement(300);
		delay(500);
	}
	dfPlayer.setFreezeDance(active);
}

void turnOff()
{
	if (!hwConfig.PowerOff)
	{
		return;
	}
	Serial.println(F("=== power off!"));
    // enter sleep state
    digitalWrite(pinConfig.Shutdown, HIGH);
    delay(500);

    // http://discourse.voss.earth/t/intenso-s10000-powerbank-automatische-abschaltung-software-only/805
    // powerdown to 27mA (powerbank switches off after 30-60s)
    mfrc522.PCD_AntennaOff();
    mfrc522.PCD_SoftPowerDown();
    dfPlayer.sleep();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    cli();  // Disable interrupts
    sleep_mode();
}

void checkSleepAtMillis()
{
	unsigned long sleepTime = tonuinoPlayer().sleepTimer.activeTime;
	if (sleepTime > 0 && millis() > sleepTime) 
	{
		tonuinoPlayer().pauseAndStandBy();
		turnOff();
	}
}

// Funktion für den Standby Timer (z.B. über Pololu-Switch oder Mosfet)
void checkStandbyAtMillis() 
{
	unsigned long standbyTime = tonuinoPlayer().standbyTimer.activeTime;
	if (standbyTime > 0 && millis() > standbyTime) 
	{
		turnOff();
	}
}

void checkCurrentTrack()
{
	if (dfPlayer.musicDS.mode == AudioBook)
	{
		uint8_t currentTrack = tonuinoPlayer().currentTrack();
		if (currentTrack > 0 && trackInEEPROM != currentTrack)
		{
			Serial.print("Save current track to EEPROM: ");
			Serial.print(currentTrack);
			tonuinoEEPROM.writeLastTrackToFlash(currentTrack, dfPlayer.musicDS.folder);
		}
	}
}

bool m_lastPlayState = true;
void checkPlayState()
{
	bool isCurrentlyPlaying = dfPlayer.isPlaying();
    if (m_lastPlayState != isCurrentlyPlaying)
    {
		digitalWrite(pinConfig.StopLED, isCurrentlyPlaying ? LOW : HIGH);
		m_lastPlayState = isCurrentlyPlaying;
    }
}

void playShortCut(uint8_t shortCut) 
{
	Serial.println(F("=== playShortCut()"));
	Serial.println(shortCut);
	MusicDataset shortCutData = swConfig.ShortCuts[shortCut];
	if (shortCutData.folder > 0) 
	{
		loadAndPlayFolder(shortCutData);
	}
	else
	{
		Serial.println(F("Shortcut not configured!"));
	}
}

void setupTonuino(TonuinoConfig config) 
{
	pinConfig = config.PINS;
	swConfig = config.SW;
	hwConfig = config.HW;
	
	Serial.begin(115200); // Es gibt ein paar Debug Ausgaben über die serielle Schnittstelle

	// Wert für randomSeed() erzeugen durch das mehrfache Sammeln von rauschenden LSBs eines offenen Analogeingangs
	uint32_t ADC_LSB;
	uint32_t ADCSeed;
	for (uint8_t i = 0; i < 128; i++) 
	{
		ADC_LSB = analogRead(pinConfig.OpenAnalog) & 0x1;
		ADCSeed ^= ADC_LSB << (i % 32);
	}
	randomSeed(ADCSeed); // Zufallsgenerator initialisieren

	// Dieser Hinweis darf nicht entfernt werden
	Serial.println(F("\n _____         _____ _____ _____ _____"));
	Serial.println(F("|_   _|___ ___|  |  |     |   | |     |"));
	Serial.println(F("  | | | . |   |  |  |-   -| | | |  |  |"));
	Serial.println(F("  |_| |___|_|_|_____|_____|_|___|_____|\n"));
	Serial.println(F("TonUINO MIRA Version 1.0.0"));
	Serial.println(F("created by Bastelmatz."));

	// DFPlayer Mini initialisieren
	dfPlayer.setup(pinConfig.DFPlayer_Busy);

	// set settings
	dfPlayer.volumeMin = swConfig.VolumeMin;
	dfPlayer.volumeMax = swConfig.VolumeMax;
	dfPlayer.setVolume(swConfig.VolumeInit);
	dfPlayer.setEqualizer(swConfig.Equalizer);
	setStandbyTimerValue(0);
	setSleepTimerValue(0);

	// NFC Leser initialisieren
	if (hwConfig.CardReader)
	{
		tonuinoRFID.setupRFID();
	}

	if (hwConfig.Potentiometer)
	{
		tonuinoPoti.setup(pinConfig.Poti, swConfig.VolumeMin, swConfig.VolumeMax); 
	}
	
	if (hwConfig.RotaryEncoder)
	{
		rotaryEncoder.setup(pinConfig.Encoder_CLK, pinConfig.Encoder_DT); 
	}
	
	if (hwConfig.UltraSonic)
	{
		ultraSonicSensor.setup(pinConfig.SonicTrigger, pinConfig.SonicEcho);
	}

	tonuinoButtons.setup(pinConfig.ButtonPause, pinConfig.ButtonNext, pinConfig.ButtonPrevious);

	pinMode(pinConfig.StopLED, OUTPUT);

	if (hwConfig.PowerOff)
	{
		pinMode(pinConfig.Shutdown, OUTPUT);
		digitalWrite(pinConfig.Shutdown, LOW);
	}

	// RESET --- ALLE DREI KNÖPFE BEIM STARTEN GEDRÜCKT HALTEN -> alle EINSTELLUNGEN werden gelöscht
	if (tonuinoButtons.readRaw() == BUTTONDOWN_All) 
	{
		tonuinoEEPROM.resetEEPROM();
	}

	// play startup sound
	dfPlayer.playAdvertisement(261);

	// load last folder 
	loadStartFolder();
	loadFolder(lastMusicDS);
}

void handleRotaryEncoder()
{
	if (!hwConfig.RotaryEncoder)
	{
		return;
	}
	
	ModifierDataset modiDS = rotaryEncoder.getPlayerModification();	
	handleModifier(modiDS.modi, modiDS.value);
}

void handleButtons()
{
	if (allLocked || buttonsLocked)
	{
		return;
	}
	if (hwConfig.Potentiometer)
	{
		if (tonuinoPoti.read())
		{
			dfPlayer.setVolume(tonuinoPoti.appliedValue);
		}
	}
	
	bool isCurrentlyPlaying = dfPlayer.isPlaying();
	ModifierDataset modiDS = tonuinoButtons.getPlayerModification(isCurrentlyPlaying);	
	handleModifier(modiDS.modi, modiDS.value);
}

void handleCardReader()
{
	if (!hwConfig.CardReader)
	{
		return;
	}
	
	byte pollCardResult = tonuinoRFID.tryPollCard();
	if (pollCardResult == MODIFIERCARD_NEW)
	{
		evaluateModifierData(tonuinoRFID.readCardData.musicDS);
	}
	if (allLocked)
	{
		return;
	}
	switch (pollCardResult)
	{
		case MUSICCARD_NEW: onNewCard(); break;
		case ALLCARDS_GONE: onCardGone(); break;
		case MUSICCARD_IS_BACK:	onCardReturn(); break;
	}    
}

void handleUltraSonic()
{
	if (!hwConfig.UltraSonic)
	{
		return;
	}

	long distance = ultraSonicSensor.read();
	if (distance > 10 && distance < 70)
	{
		handle_sonic = true;
	}
	if (distance > 70)
	{
		if (handle_sonic)
		{
			dfPlayer.playAdvertisement(262);
			dfPlayer.nextTrack();
		}
		handle_sonic = false;
	}
}

void loopTonuino() 
{
	checkSleepAtMillis();
    checkStandbyAtMillis();
	checkCurrentTrack();
    dfPlayer.loop();
	checkPlayState();
	
	handleUltraSonic();
	handleRotaryEncoder();
	handleButtons();
	handleCardReader();
}

void onNewCard()
{
	memcpy(&nextMC, &tonuinoRFID.readCardData, sizeof(nfcTagStruct));
	
	if (nextMC.cookie == cardCookie && nextMC.musicDS.folder > 0 && nextMC.musicDS.mode > 0) 
	{
		loadAndPlayFolder(nextMC.musicDS);
		// Save last folder for next power up
		tonuinoEEPROM.writeLastDatasetToFlash(nextMC.musicDS);
	}
	// Neue Karte konfigurieren
	else if (nextMC.cookie != cardCookie) 
	{
		dfPlayer.musicDSLoaded = false;
		dfPlayer.playMP3AndWait(300);
		setupCard();
	}
}

void onCardGone()
{
	if (swConfig.StopPlayOnCardRemoval)
	{
		dfPlayer.pauseAndStandBy();
	}
}

void onCardReturn()
{
	dfPlayer.continueTitle();
}

void waitForNewCard()
{
	do {
		int buttonState = tonuinoButtons.read();
		if (buttonState == BUTTONCLICK_Next || buttonState == BUTTONCLICK_Previous) 
		{
			Serial.println(F("Abgebrochen!"));
			dfPlayer.playMp3Track(802);
			break;
		}
	} while (!tonuinoRFID.cardDetected());
}

uint8_t voiceMenu(uint8_t numberOfOptions, int startMessage, int messageOffset,
                  bool preview, int previewFromFolder, int defaultValue) 
{
	uint8_t returnValue = defaultValue;
	if (startMessage != 0)
	{
		dfPlayer.playMp3Track(startMessage);
	}
	Serial.print(F("=== voiceMenu() ("));
	Serial.print(numberOfOptions);
	Serial.println(F(" Options)"));
	do 
	{
		// Support for input via console
		if (Serial.available() > 0) 
		{
			int optionSerial = Serial.parseInt();
			if (optionSerial != 0 && optionSerial <= numberOfOptions)
			{
				return optionSerial;
			}
		}

		dfPlayer.loop();
		checkStandbyAtMillis();
		ModifierDataset modiDS = tonuinoButtons.getMenuModification(returnValue, defaultValue, numberOfOptions);
		if (modiDS.modi == MODI_MENU_Cancel ||
			modiDS.modi == MODI_MENU_Choose) 
		{
			if (modiDS.modi == MODI_MENU_Cancel) 
			{
				dfPlayer.playMp3Track(802);
			}
			Serial.print("Use option ");
			Serial.println(modiDS.value);
			return modiDS.value;
		}
		if (modiDS.modi == MODI_MENU_ChangeSmall ||
			modiDS.modi == MODI_MENU_ChangeLarge) 
		{
			returnValue = modiDS.value;
			Serial.println(returnValue);
			dfPlayer.playMP3AndWait(messageOffset + returnValue);
			if (preview && modiDS.modi == MODI_MENU_ChangeSmall) 
			{
				if (previewFromFolder == 0) 
				{
					dfPlayer.playTrack(returnValue, 1);
				}
				else 
				{
					dfPlayer.playTrack(previewFromFolder, returnValue);
				}
			}
		}
	} while (true);
}

bool setupFolder(MusicDataset * musicDS) 
{
	// Ordner abfragen
	musicDS->folder = voiceMenu(99, 301, 0, true, 0, 0);
	uint8_t folder = musicDS->folder;
	if (folder == 0) return false;

	// Wiedergabemodus abfragen
	musicDS->mode = voiceMenu(9, 310, 310, false, 0, 0);
	uint8_t mode = musicDS->mode;
	if (mode == 0) return false;

	uint8_t numberOptions = dfPlayer.getFolderTrackCount(folder);
	// Einzelmodus -> Datei abfragen
	if (mode == 4)
	{
		musicDS->special = voiceMenu(numberOptions, 320, 0, true, folder, 0);
	}
	// Spezialmodus Von-Bis
	if (mode == 7 || mode == 8 || mode == 9) 
	{
		musicDS->special = voiceMenu(numberOptions, 321, 0, true, folder, 0);
		musicDS->special2 = voiceMenu(numberOptions, 322, 0, true, folder, musicDS->special);
	}
	return true;
}

void setupCard() 
{
	dfPlayer.pause();
	Serial.println(F("=== setupCard()"));
	nfcTagStruct newCard;
	if (setupFolder(&newCard.musicDS) == true)
	{
		// Karte ist konfiguriert -> speichern
		dfPlayer.pause();
		do { } while (dfPlayer.isPlaying());
		writeCard(newCard);
	}
	delay(1000);
}

void writeCard(nfcTagStruct nfcTag) 
{
	bool statusOK = tonuinoRFID.writeCard(nfcTag);
	dfPlayer.playMp3Track(statusOK ? 400 : 401);
}

void resetCard() 
{
	dfPlayer.playMp3Track(800);
	waitForNewCard();

	if (!tonuinoRFID.cardSerialFound())
	{
		return;
	}

	Serial.print(F("Karte wird neu konfiguriert!"));
	setupCard();
}

void handleModifier(EModifier modifier, uint8_t special)
{
	bool toggle = special == 2;
	bool bValue = special == 1;
	switch (modifier)
	{
		case MODI_LockAll:
		{
			allLocked = toggle ? !allLocked : bValue; break;
		}
		case MODI_LockButtons:
		{
			buttonsLocked = toggle ? !buttonsLocked : bValue; break;
		}
		case MODI_ResetCard:
		{
			resetCard();
			tonuinoRFID.haltAndStop(); 
			break;
		}
		case MODI_ResetEEPROM:
		{
			tonuinoEEPROM.resetEEPROM();
			dfPlayer.playMp3Track(999); 
			break;
		}
		case MODI_Player_SleepTime:
		{
			setSleepTimerValue(special); break;
		}
		case MODI_Player_Volume:
		{
			dfPlayer.setVolume(special); break;
		}
		case MODI_Player_VolumeUp:
		{
			dfPlayer.volumeUp(); break;
		}
		case MODI_Player_VolumeDown:
		{
			dfPlayer.volumeDown(); break;
		}
		case MODI_Player_Random:
		{
			tonuinoPlayer().playRandom = toggle ? !tonuinoPlayer().playRandom : bValue; break;
		}
		case MODI_Player_RepeatSingle:
		{
			tonuinoPlayer().singleRepetition = toggle ? !tonuinoPlayer().singleRepetition : bValue; break;
		}
		case MODI_Player_ListenToEnd:
		{
			tonuinoPlayer().listenUntilTrackEnds = toggle ? !tonuinoPlayer().listenUntilTrackEnds : bValue; break;
		}
		case MODI_Player_FreezeDance:
		{
			dfPlayer.freezeDance_active = toggle ? !dfPlayer.freezeDance_active : bValue; break;
		}
		case MODI_TrackToggle:
		{
			dfPlayer.togglePlay(); break;
		}
		case MODI_TrackNext:
		{
			dfPlayer.nextTrack(); break;
		}
		case MODI_TrackPrevious:
		{
			dfPlayer.previousTrack(); break;
		}
		case MODI_TrackFirst:
		{
			dfPlayer.firstTrack(); break;
		}
		case MODI_TrackLast:
		{
			dfPlayer.lastTrack(); break;
		}
		case MODI_TrackNumber:
		{
			uint8_t advertTrack = tonuinoPlayer().currentTrackInRange();
			dfPlayer.playAdvertisement(advertTrack);
			break;
		}
		case MODI_ShortCut:
		{
			playShortCut(special); break;
		}
	}
}

void handleModifier(EModifier modifier)
{
	handleModifier(modifier, 0);
}

void evaluateModifierData(MusicDataset musicDS)
{
	EModifier modifier = static_cast<EModifier>(musicDS.mode);
	uint8_t special = musicDS.special;
	
	handleModifier(modifier, special);
}
