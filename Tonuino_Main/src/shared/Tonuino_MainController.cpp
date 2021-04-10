
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
uint8_t sonicCounter = 0;
bool countdownNextTrack = false;

TonuinoButtons tonuinoButtons;

TonuinoRotaryEncoder rotaryEncoder;

TonuinoNeopixel neopixelRing;

uint32_t lastTimeTrackAndFolderSaved = 0;
MusicDataset recentMusicDSinEEPROM = { 0 };
MusicDataset recentCardMusicDS;

bool allLocked = false;
bool buttonsLocked = false;

TonuinoPlayer tonuinoPlayer()
{
	return dfPlayer.tonuinoPlayer;
}

void setStandbyTimerValue(uint8_t timeInMin)
{
	tonuinoPlayer().standbyTimer.timeInMin = timeInMin;
}

void setSleepTimerValue(uint8_t timeInMin)
{
	tonuinoPlayer().sleepTimer.timeInMin = timeInMin;
}

MusicDataset loadStartMusicDS()
{
	if (swConfig.StartMusicDS.startFolder == 0)
	{
		recentMusicDSinEEPROM = tonuinoEEPROM.loadFromFlash_RecentMusicDS();
		return recentMusicDSinEEPROM;
	}
	else
	{
		return swConfig.StartMusicDS;
	}
}

void loadFolder(MusicDataset musicDS)
{
	dfPlayer.loadFolder(musicDS);
}

void loadAndPlayFolder(MusicDataset musicDS)
{
	dfPlayer.loadAndPlayFolder(musicDS);
}

void turnOff()
{
	if (!hwConfig.PowerOff)
	{
		return;
	}
	dfPlayer.playAdvertisementAndWait(302);
	
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

void saveCurrentTrackAndFolder()
{
	uint8_t mode = tonuinoPlayer().mode;
	if (mode == AudioBook || mode == Section_Audiobook)
	{
		// Don't save every track/folder change when manually moving through playlist 
		// Apply change only every 10th second
		if (millis() - lastTimeTrackAndFolderSaved < 10000)
		{
			return;
		}
		uint8_t currentTrack = tonuinoPlayer().currentTrack();
		uint8_t currentFolder = dfPlayer.currentMusicFolder;
		
		// Save to EEPROM		
		if (currentTrack > 0 && recentMusicDSinEEPROM.recentTrack != currentTrack)
		{
			tonuinoEEPROM.writeToFlash_RecentTrack(currentTrack);
			recentMusicDSinEEPROM.recentTrack = currentTrack;
		}
		if (currentFolder > 0 && recentMusicDSinEEPROM.recentFolder != currentFolder)
		{
			tonuinoEEPROM.writeToFlash_RecentFolder(currentFolder);
			recentMusicDSinEEPROM.recentFolder = currentFolder;
		}
		
		// Save to RFID card
		if (tonuinoRFID.hasMusicCard)
		{		
			if ((recentCardMusicDS.recentFolder != currentFolder && currentFolder > 0) ||
				(recentCardMusicDS.recentTrack != currentTrack && currentTrack > 0))
			{
				Serial.print(F("Write recent folder and track to card"));
				recentCardMusicDS.recentFolder = currentFolder;
				recentCardMusicDS.recentTrack = currentTrack;
				tonuinoRFID.writeCard(recentCardMusicDS);
			}
		}
		lastTimeTrackAndFolderSaved = millis();
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

void setupTonuino(TonuinoConfig config) 
{
	pinConfig = config.PINS;
	swConfig = config.SW;
	hwConfig = config.HW;
	
	Serial.begin(115200); // Es gibt ein paar Debug Ausgaben über die serielle Schnittstelle

	// Wert für randomSeed() erzeugen durch das mehrfache Sammeln von rauschenden LSBs eines offenen Analogeingangs
	uint32_t ADC_LSB = 0;
	uint32_t ADCSeed = 0;
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
	dfPlayer.volumeIncrement = swConfig.VolumeIncrement;
	dfPlayer.setVolume(swConfig.VolumeInit);
	dfPlayer.setEqualizer(swConfig.Equalizer);
	setStandbyTimerValue(swConfig.StandbyTimeInMin);
	setSleepTimerValue(swConfig.SleepTimeInMin);

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

	if (hwConfig.NeopixelRing)
	{
		neopixelRing.setup(hwConfig.NeopixelLeds, pinConfig.NeopixelData);
	}

	if (hwConfig.PowerOff)
	{
		pinMode(pinConfig.Shutdown, OUTPUT);
		digitalWrite(pinConfig.Shutdown, LOW);
	}

	// RESET --- ALLE DREI KNÖPFE BEIM STARTEN GEDRÜCKT HALTEN -> alle EINSTELLUNGEN werden gelöscht
	if (tonuinoButtons.read() == BUTTONPRESSED_All) 
	{
		tonuinoEEPROM.resetEEPROM();
	}

	// set volume according to poti
	handlePotentiometer();
	// play startup sound
	dfPlayer.playAdvertisementAndWait(261);
	dfPlayer.pause();
	// give DFPlayer some time
	delay(1000);
	
	// load defined or recent folder 
	MusicDataset startMusicDS = loadStartMusicDS();
	loadFolder(startMusicDS);
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

void handlePotentiometer()
{
	if (!hwConfig.Potentiometer)
	{
		return;
	}
	
	if (tonuinoPoti.read())
	{
		dfPlayer.setVolume(tonuinoPoti.appliedValue);
	}
}

void handleButtons()
{
	if (allLocked || buttonsLocked)
	{
		return;
	}
	
	bool isCurrentlyPlaying = dfPlayer.isPlaying();
	
	if (!isCurrentlyPlaying && tonuinoButtons.read() == BUTTONPRESSED_LONG_All) 
	{
		handleModifier(MODI_ResetCard, 0);
		return;
	}
	
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
		evaluateModifierCardData(tonuinoRFID.readCardData.musicDS, false);
	}
	if (allLocked)
	{
		return;
	}
	switch (pollCardResult)
	{
		case MUSICCARD_NEW: onNewMusicCard(); break;
		case ALLCARDS_GONE: onCardGone(); break;
		case MUSICCARD_IS_BACK:	onMusicCardReturn(); break;
	}
}

void handleUltraSonic()
{
	if (!hwConfig.UltraSonic)
	{
		return;
	}

	uint16_t distance = ultraSonicSensor.read();
	if (distance > 20 && distance < 60)
	{
		sonicCounter++; 
	}
	if (distance > 60)
	{
		if (sonicCounter > 1 && !countdownNextTrack) // avoid outliers and prevent new call while countdown
		{
			dfPlayer.pause();
			delay(100);
			dfPlayer.playAdvertisement(262);
			countdownNextTrack = true;
		}
		sonicCounter = 0;
	}
	if (countdownNextTrack && neopixelRing.limitedAnimationFinished)
	{
		dfPlayer.nextTrack();
		countdownNextTrack = false;
	}
}
	
void handleNeopixels()
{
	neopixelRing.animConfig.volume = dfPlayer.volume;
	neopixelRing.animConfig.volumeMin = dfPlayer.volumeMin;
	neopixelRing.animConfig.volumeMax = dfPlayer.volumeMax;
	neopixelRing.animConfig.musicLoaded = dfPlayer.musicDSLoaded;
	neopixelRing.animConfig.musicLoading = countdownNextTrack;
	neopixelRing.animConfig.musicPlaying = dfPlayer.isPlaying();
	neopixelRing.animate();
}

void loopTonuino() 
{
	checkSleepAtMillis();
    checkStandbyAtMillis();
	saveCurrentTrackAndFolder();
    dfPlayer.loop();
	checkPlayState();
	
	handleUltraSonic();
	handleRotaryEncoder();
	handlePotentiometer();
	handleButtons();
	handleCardReader();
	handleNeopixels();
}

void onNewMusicCard()
{
	if (tonuinoRFID.readCardData.cookie != cardCookie)
	{
		// Neue Karte konfigurieren
		setupCard();
		return;
	}

	MusicDataset nextMusicDS = tonuinoRFID.readCardData.musicDS;
	uint8_t mode = nextMusicDS.mode;
	if (nextMusicDS.startFolder > 0 && mode > 0) 
	{
		memcpy(&recentCardMusicDS, &nextMusicDS, sizeof(MusicDataset));
		
		ECOMPARERESULT compareResult = dfPlayer.playOrCompareTrack(recentCardMusicDS, true, false, swConfig.StopPlayOnCardRemoval);
		if (compareResult != COMPARE_NOTSUPPORTED)
		{
			// optional to do: visualize result, e.g. turn LED on/off or change color
		}
		
		// Save recent music for next power up
		if (mode == Album || mode == Section_Album ||
			mode == Party || mode == Section_Party ||
			mode == AudioBook || mode == Section_Audiobook ||
			mode == RandomFolder_Album || 
			mode == RandomFolder_Party)
		{
			tonuinoEEPROM.writeToFlash_RecentMusicDS(recentCardMusicDS);
			recentMusicDSinEEPROM = recentCardMusicDS;
		}
	}
}

void onCardGone()
{
	MusicDataset lastCardMusicDS = tonuinoRFID.readCardData.musicDS;
	if (tonuinoRFID.lastCardWasModifierCard)
	{
		evaluateModifierCardData(lastCardMusicDS, true);
		return;
	}
	// on music card gone
	dfPlayer.playOrCompareTrack(recentCardMusicDS, false, true, swConfig.StopPlayOnCardRemoval);
}

void onMusicCardReturn()
{
	dfPlayer.playOrCompareTrack(recentCardMusicDS, false, false, swConfig.StopPlayOnCardRemoval);
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
	bool doPreview = false;
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
		if (modiDS.modi == MODI_None && hwConfig.RotaryEncoder)
		{
			modiDS = rotaryEncoder.getMenuModification(returnValue, defaultValue, numberOfOptions);
		}
		if (modiDS.modi == MODI_MENU_Cancel ||
			modiDS.modi == MODI_MENU_Choose) 
		{
			if (modiDS.modi == MODI_MENU_Cancel) 
			{
				dfPlayer.playMp3Track(802);
			}
			Serial.print(F("Use option "));
			Serial.println(modiDS.value);
			return modiDS.value;
		}
		if (modiDS.modi == MODI_MENU_ChangeSmall ||
			modiDS.modi == MODI_MENU_ChangeLarge) 
		{
			doPreview = false;
			returnValue = modiDS.value;
			Serial.println(returnValue);
			dfPlayer.playMp3Track(messageOffset + returnValue);
			if (preview && modiDS.modi == MODI_MENU_ChangeSmall) 
			{
				doPreview = true;
			}
		}
		if (doPreview && !dfPlayer.isPlaying())
		{
			if (previewFromFolder == 0) 
			{
				dfPlayer.playTrack(returnValue, 1);
			}
			else 
			{
				dfPlayer.playTrack(previewFromFolder, returnValue);
			}
			doPreview = false;
		}
	} while (true);
}

bool setupFolder(MusicDataset * musicDS) 
{
	// Ordner abfragen
	musicDS->startFolder = voiceMenu(99, 301, 0, true, 0, 0);
	uint8_t folder = musicDS->startFolder;
	if (folder == 0) return false;

	// Wiedergabemodus abfragen
	musicDS->mode = voiceMenu(9, 310, 310, false, 0, 0);
	uint8_t mode = musicDS->mode;
	if (mode == 0) return false;

	uint8_t numberOptions = dfPlayer.getFolderTrackCount(folder);
	// Einzelmodus -> Datei abfragen
	if (mode == Single)
	{
		musicDS->startTrack = voiceMenu(numberOptions, 320, 0, true, folder, 0);
	}
	// Spezialmodus Von-Bis
	if (mode == Section_AudioDrama || 
	    mode == Section_Album || 
		mode == Section_Party ||
		mode == Section_Audiobook) 
	{
		musicDS->startTrack = voiceMenu(numberOptions, 321, 0, true, folder, 0);
		musicDS->endTrack = voiceMenu(numberOptions, 322, 0, true, folder, musicDS->startTrack);
	}
	
	if (mode == RandomFolder_Album || mode == RandomFolder_Party)
	{
		musicDS->endFolder = voiceMenu(99, 301, 0, true, 0, folder);
	}
	return true;
}

void waitForNewCard()
{
	// wait = Some time for the user to leave the next/previous button, if they are pressed before (e.g. as a trigger)
	dfPlayer.playMP3AndWait(800);
	do {
		uint8_t buttonState = tonuinoButtons.read();
		if (buttonState == BUTTONCLICK_Next || buttonState == BUTTONCLICK_Previous) 
		{
			Serial.println(F("Waiting for new card aborted!"));
			dfPlayer.playMp3Track(802);
			break;
		}
	} while (!tonuinoRFID.cardDetected());
}

void setupCard() 
{
	dfPlayer.musicDSLoaded = false;
	dfPlayer.playMP3AndWait(300);
	dfPlayer.pause();
	Serial.println(F("=== setupCard()"));
	MusicDataset newMusicDS;
	if (setupFolder(&newMusicDS) == true)
	{
		// Karte ist konfiguriert -> speichern
		dfPlayer.pause();
		do { } while (dfPlayer.isPlaying());
		writeCard(newMusicDS);
	}
	tonuinoRFID.haltAndStop();
	delay(1000);
}

void writeCard(MusicDataset musicDS) 
{
	bool statusOK = tonuinoRFID.writeCard(musicDS);
	dfPlayer.playMp3Track(statusOK ? 400 : 401);
}

void resetCard() 
{
	waitForNewCard();
	
	if (!tonuinoRFID.cardSerialFound())
	{
		Serial.println(F("No card serial found."));
		return;
	}

	Serial.println(F("Reset card!"));
	bool statusOK = tonuinoRFID.resetCard();
	dfPlayer.playMp3Track(statusOK ? 400 : 401);
	tonuinoRFID.haltAndStop();
	delay(1000);
}

void playShortCut(uint8_t shortCut) 
{
	Serial.println(F("=== playShortCut()"));
	Serial.println(shortCut);
	MusicDataset shortCutData = swConfig.ShortCuts[shortCut];
	if (shortCutData.startFolder > 0) 
	{
		loadAndPlayFolder(shortCutData);
	}
	else
	{
		Serial.println(F("Shortcut not configured!"));
	}
}

void handleModifier(EModifier modifier, uint16_t special)
{
	handleModifier(modifier, special, false);
}

void handleModifier(EModifier modifier, uint16_t special, bool isCardRemoval)
{
	if (modifier == MODI_None)
	{
		return;
	}
	
	bool toggle = false;
	bool bValue = false;
	// Evaluate toggle and bValue for BoolModifier
	if (TONUINOMODIFIER::isBoolModifer(modifier))
	{
		EModifierBoolValue modifierBoolValue = static_cast<EModifierBoolValue>(special);
		bool applyOnRemoval = false;
		bool applyAlways = false;
		switch (modifierBoolValue)
		{
			case MODI_BOOLVAL_OnRemoval_Set:
			case MODI_BOOLVAL_OnRemoval_Undo:
			case MODI_BOOLVAL_OnRemoval_Toggle: applyOnRemoval = true; break;
			case MODI_BOOLVAL_Set_OnRemoval_Undo:
			case MODI_BOOLVAL_Undo_OnRemoval_Set:
			case MODI_BOOLVAL_Toggle_OnRemoval_Toggle: applyAlways = true; break;
		}
		if (!applyAlways && isCardRemoval != applyOnRemoval)
		{
			return;
		}
		switch (modifierBoolValue)
		{
			case MODI_BOOLVAL_Toggle:
			case MODI_BOOLVAL_OnRemoval_Toggle:
			case MODI_BOOLVAL_Toggle_OnRemoval_Toggle: toggle = true; break;
		}
		if (isCardRemoval)
		{
			bValue = modifierBoolValue == MODI_BOOLVAL_OnRemoval_Set || 
					 modifierBoolValue == MODI_BOOLVAL_Undo_OnRemoval_Set;
		}
		else
		{
			bValue = modifierBoolValue == MODI_BOOLVAL_Set || 
					 modifierBoolValue == MODI_BOOLVAL_Set_OnRemoval_Undo;
		}
	}
	
	Serial.print(F("Handle modifier: "));
	Serial.print(modifier);
	Serial.print(F(" - value: "));
	Serial.println(special);
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
		case MODI_SetupCard:
		{
			setupCard(); break;
		}
		case MODI_ResetCard:
		{
			resetCard(); break;
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
			dfPlayer.setFreezeDance(toggle ? !dfPlayer.freezeDance_active : bValue); break;
		}
		case MODI_Player_Memory:
		{
			dfPlayer.setMemoryMode(toggle ? !dfPlayer.memoryMode_active : bValue); break;
		}
		case MODI_Player_RandomQuiz:
		{
			dfPlayer.randomQuiz_active = toggle ? !dfPlayer.randomQuiz_active : bValue; break;
		}
		case MODI_TrackContinue:
		{
			if (toggle)
			{
				dfPlayer.togglePlay();
			}
			else
			{
				bValue ? dfPlayer.continueTitle() : dfPlayer.pauseAndStandBy();
			}
			break;
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
			dfPlayer.playAdvertisementAndWait(advertTrack);
			break;
		}
		case MODI_ShortCut:
		{
			playShortCut(special); break;
		}
		case MODI_Advertisement:
		{
			dfPlayer.playAdvertisementAndWait(special);
		}
	}
}

void evaluateModifierCardData(MusicDataset musicDS, bool isCardRemoval)
{
	EModifier modifier = static_cast<EModifier>(musicDS.mode);
	uint8_t special = musicDS.startTrack;
	uint8_t special2 = musicDS.endTrack;
	
	uint16_t value = special2 << 8 | special;
	handleModifier(modifier, value, isCardRemoval);
}
