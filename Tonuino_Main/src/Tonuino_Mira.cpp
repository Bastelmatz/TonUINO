
#include "Tonuino_Defines_Tools.h"

#ifdef TONUINO_MIRA

#include "Tonuino_Mira.h"

#include <JC_Button.h>
#include <MFRC522.h>
#include <avr/sleep.h>

/*
   _____         _____ _____ _____ _____
  |_   _|___ ___|  |  |     |   | |     |
    | | | . |   |  |  |-   -| | | |  |  |
    |_| |___|_|_|_____|_____|_|___|_____|
    TonUINO Version 2.1

    created by Thorsten Voß and licensed under GNU/GPL.
    Information and contribution at https://tonuino.de.
*/

// ****************************************
// Options
static bool StopPlayOnCardRemoval = false;
// *******************************************

// RFID reader
Tonuino_RFID_Reader tonuinoRFID;

// DFPlayer Mini
TonuinoDFPlayer dfPlayer;

TonuinoEEPROM tonuinoEEPROM;

uint8_t voiceMenu(int numberOfOptions, int startMessage, int messageOffset,
                  bool preview = false, int previewFromFolder = 0, int defaultValue = 0, bool exitWithLongPress = false);
void writeCard(nfcTagStruct nfcTag);

#define buttonPause A1
#define buttonNext A3
#define buttonPrevious A4
#define stopLED 6
#define shutdownPin 7
#define openAnalogPin A6

#define PotiPin A2                            // 10kOhm Poti at Pin A2
int PotiHysterese = 0;                        // Volumenpoti Hysterese (Standarteinstellung = 2)
int PotiValue;                                // Poti Value now, Volumen
int oldPotiValue;                             // old Poti Value, Volumen

#define LONG_PRESS 1000

bool usePotentiometer = false;

Button pauseButton(buttonPause);
Button nextButton(buttonNext);
Button previousButton(buttonPrevious);

bool ignorePauseButton = false;
bool ignoreNextButton = false;
bool ignorePreviousButton = false;

uint8_t trackInEEPROM = 0;
nfcTagStruct nextMC;
musicDataset lastMusicDS;

bool usePowerOff = false;

bool allLocked = false;
bool buttonsLocked = false;

TonuinoPlayer tonuinoPlayer()
{
	return dfPlayer.tonuinoPlayer;
}

void loadDataFromFlash()
{
	tonuinoEEPROM.loadSettingsFromFlash();
	lastMusicDS = tonuinoEEPROM.loadLastDatasetFromFlash();
}

void setStandbyTimerValue(uint8_t timeInMin)
{
	tonuinoPlayer().standbyTimer.timeInMin = timeInMin;
}

void setSleepTimerValue(uint8_t timeInMin)
{
	tonuinoPlayer().sleepTimer.timeInMin = timeInMin;
}

uint8_t getLastTrack(musicDataset musicDS)
{
	if (musicDS.mode == AudioBook) 
	{
		trackInEEPROM = tonuinoEEPROM.loadLastTrackFromFlash(musicDS.folder);
		return trackInEEPROM;
	}
	return 0;
}

void loadFolder(musicDataset musicDS)
{
    uint8_t lastTrack = getLastTrack(musicDS);
	dfPlayer.loadFolder(musicDS, lastTrack);
}

void loadAndPlayFolder(musicDataset musicDS)
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
	if (!usePowerOff)
	{
		return;
	}
	Serial.println(F("=== power off!"));
    // enter sleep state
    digitalWrite(shutdownPin, HIGH);
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

void playShortCut(uint8_t shortCut) 
{
	Serial.println(F("=== playShortCut()"));
	Serial.println(shortCut);
	musicDataset shortCutData = tonuinoEEPROM.settings.shortCuts[shortCut];
	if (shortCutData.folder != 0) 
	{
		loadAndPlayFolder(shortCutData);
	}
	else
	{
		Serial.println(F("Shortcut not configured!"));
	}
}

void setupTonuino() {

  Serial.begin(115200); // Es gibt ein paar Debug Ausgaben über die serielle Schnittstelle

  // Wert für randomSeed() erzeugen durch das mehrfache Sammeln von rauschenden LSBs eines offenen Analogeingangs
  uint32_t ADC_LSB;
  uint32_t ADCSeed;
  for (uint8_t i = 0; i < 128; i++) {
    ADC_LSB = analogRead(openAnalogPin) & 0x1;
    ADCSeed ^= ADC_LSB << (i % 32);
  }
  randomSeed(ADCSeed); // Zufallsgenerator initialisieren

  // Dieser Hinweis darf nicht entfernt werden
  Serial.println(F("\n _____         _____ _____ _____ _____"));
  Serial.println(F("|_   _|___ ___|  |  |     |   | |     |"));
  Serial.println(F("  | | | . |   |  |  |-   -| | | |  |  |"));
  Serial.println(F("  |_| |___|_|_|_____|_____|_|___|_____|\n"));
  Serial.println(F("TonUINO Version 2.1"));
  Serial.println(F("created by Thorsten Voß and licensed under GNU/GPL."));
  Serial.println(F("Information and contribution at https://tonuino.de.\n"));

  // load data from EEPROM
  loadDataFromFlash();
  
  // DFPlayer Mini initialisieren
  dfPlayer.setup();
  
  // set settings
  dfPlayer.volumeMin = 1;
  dfPlayer.volumeMax = 30;
  dfPlayer.setVolume(10);
  oldPotiValue = dfPlayer.volume;
  dfPlayer.setEqualizer(DfMp3_Eq_Normal);
  setStandbyTimerValue(0);
  setSleepTimerValue(0);

  // NFC Leser initialisieren
  tonuinoRFID.setupRFID();

  pinMode(buttonPause, INPUT_PULLUP);
  pinMode(buttonNext, INPUT_PULLUP);
  pinMode(buttonPrevious, INPUT_PULLUP);
  pinMode(PotiPin, INPUT_PULLUP);

  pinMode(stopLED, OUTPUT);
  
  pinMode(shutdownPin, OUTPUT);
  digitalWrite(shutdownPin, LOW);

  // RESET --- ALLE DREI KNÖPFE BEIM STARTEN GEDRÜCKT HALTEN -> alle EINSTELLUNGEN werden gelöscht
  if (digitalRead(buttonPause) == LOW && digitalRead(buttonNext) == LOW && digitalRead(buttonPrevious) == LOW) 
  {
    tonuinoEEPROM.resetEEPROM();
    loadDataFromFlash();
  }

  // play startup sound
  //dfPlayer.start();
  dfPlayer.playAdvertisement(261);
  //dfPlayer.pause();
  delay(1000);
  
  // load last folder 
  loadFolder(lastMusicDS);
}

void readButtons() {
  pauseButton.read();
  nextButton.read();
  previousButton.read();
}

void readPotentiometer() 
{     
	if (!usePotentiometer)
	{
		return;
	}
    PotiValue = analogRead(PotiPin);
    PotiValue = map(PotiValue, 0, 1024, dfPlayer.volumeMin, dfPlayer.volumeMax);
    // Vergleiche aktueller Lautstärke-Potistellung mit der alten Stellung inkl. Hysterese 
    // pressing A0 pause button causes low level for poti voltage = max volume
    if ((PotiValue > oldPotiValue + PotiHysterese && PotiValue <= dfPlayer.volumeMax)
     || (PotiValue < oldPotiValue - PotiHysterese && PotiValue >= dfPlayer.volumeMin))  
    {
        Serial.print("Potentiometer Volumen: ");
        Serial.println(PotiValue);       
        oldPotiValue = PotiValue;
        dfPlayer.setVolume(PotiValue);
    }
}

void handleButtons()
{
	// Buttons werden nun über JS_Button gehandelt, dadurch kann jede Taste doppelt belegt werden
    readButtons();
	
	readPotentiometer();
		
	bool isCurrentlyPlaying = dfPlayer.isPlaying();
	
	if (pauseButton.wasReleased()) 
	{
		if (ignorePauseButton == false)
		{
			dfPlayer.togglePlay();
		}
		ignorePauseButton = false;
	} 
	else if (pauseButton.pressedFor(LONG_PRESS) && ignorePauseButton == false) 
	{
		if (isCurrentlyPlaying) 
		{
			uint8_t advertTrack = tonuinoPlayer().currentTrackInRange();
			dfPlayer.playAdvertisement(advertTrack);
		}
		else 
		{
			playShortCut(0);
		}
		ignorePauseButton = true;
	}
	if (!dfPlayer.listenUntilTrackEnds)
	{
		if (nextButton.wasReleased()) 
		{
			if (isCurrentlyPlaying) 
			{
				dfPlayer.nextTrack();
			}
			else 
			{
				playShortCut(1);
			}
		}
		if (previousButton.wasReleased()) 
		{
			if (isCurrentlyPlaying) 
			{
				dfPlayer.previousTrack();
			}
			else 
			{
				playShortCut(2);
			}
		}
	}
}

void handleCardReader()
{
	// poll card only every 100ms
	static uint8_t lastCardPoll = 0;
	uint8_t now = millis();

	if (static_cast<uint8_t>(now - lastCardPoll) > 100)
	{
		lastCardPoll = now;

		byte pollCardResult = tonuinoRFID.tryPollCard();

		if (pollCardResult == MODIFIERCARD_NEW)
		{
			evaluateModifierData(tonuinoRFID.readCardData);
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
}

bool m_lastPlayState = true;
void checkPlayState()
{
	bool isCurrentlyPlaying = dfPlayer.isPlaying();
    if (m_lastPlayState != isCurrentlyPlaying)
    {
      digitalWrite(stopLED, isCurrentlyPlaying ? LOW : HIGH);
      m_lastPlayState = isCurrentlyPlaying;
    }
}

void loopTonuino() 
{
	checkSleepAtMillis();
    checkStandbyAtMillis();
	checkCurrentTrack();
    dfPlayer.loop();
	checkPlayState();

	if (!allLocked && !buttonsLocked)
	{
		handleButtons();
	}

    // Ende der Buttons

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
	if (StopPlayOnCardRemoval)
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
		readButtons();
		if (nextButton.wasReleased() || previousButton.wasReleased()) 
		{
			Serial.println(F("Abgebrochen!"));
			dfPlayer.playMp3Track(802);
			break;
		}
	} while (!tonuinoRFID.cardDetected());
}

void waitForCardAndWrite(nfcTagStruct card)
{
	Serial.println(F(" Karte auflegen"));
	waitForNewCard();

	// RFID Karte wurde aufgelegt
	if (tonuinoRFID.cardSerialFound()) 
	{
		Serial.println(F("schreibe Karte..."));
		writeCard(card);
		delay(100);
		tonuinoRFID.haltAndStop();
		dfPlayer.waitForTrackToFinish();
	}
}

uint8_t voiceMenu(int numberOfOptions, int startMessage, int messageOffset,
                  bool preview = false, int previewFromFolder = 0, int defaultValue = 0, bool exitWithLongPress = false) {
  uint8_t returnValue = defaultValue;
  if (startMessage != 0)
  {
    dfPlayer.playMp3Track(startMessage);
  }
  Serial.print(F("=== voiceMenu() ("));
  Serial.print(numberOfOptions);
  Serial.println(F(" Options)"));
  do {
    if (Serial.available() > 0) {
      int optionSerial = Serial.parseInt();
      if (optionSerial != 0 && optionSerial <= numberOfOptions)
        return optionSerial;
    }
    readButtons();
    dfPlayer.loop();
    if (pauseButton.pressedFor(LONG_PRESS)) 
    {
      dfPlayer.playMp3Track(802);
      ignorePauseButton = true;
      checkStandbyAtMillis();
      return defaultValue;
    }
    if (pauseButton.wasReleased()) 
    {
      if (returnValue != 0) {
        Serial.print(F("=== "));
        Serial.print(returnValue);
        Serial.println(F(" ==="));
        return returnValue;
      }
      delay(1000);
    }

    if (nextButton.pressedFor(LONG_PRESS)) 
    {
      returnValue = min(returnValue + 10, numberOfOptions);
      Serial.println(returnValue);
      dfPlayer.playMP3AndWait(messageOffset + returnValue);
      ignoreNextButton = true;
    } else if (nextButton.wasReleased()) 
    {
      if (ignoreNextButton) 
      {
        ignoreNextButton = false;
      } 
      else 
      {
        returnValue = min(returnValue + 1, numberOfOptions);
        Serial.println(returnValue);
        dfPlayer.playMP3AndWait(messageOffset + returnValue);
        if (preview) 
        {
          if (previewFromFolder == 0) 
		  {
            dfPlayer.playTrack(returnValue, 1);
          } 
		  else 
		  {
            dfPlayer.playTrack(previewFromFolder, returnValue);
          }
          delay(1000);
        }
      }
    }

    if (previousButton.pressedFor(LONG_PRESS)) 
    {
      returnValue = max(returnValue - 10, 1);
      Serial.println(returnValue);
      dfPlayer.playMP3AndWait(messageOffset + returnValue);
      ignorePreviousButton = true;
    } 
	else if (previousButton.wasReleased()) 
    {
      if (ignorePreviousButton) 
      {
        ignorePreviousButton = false; 
      } 
      else 
      {
        returnValue = max(returnValue - 1, 1);
        Serial.println(returnValue);
        dfPlayer.playMP3AndWait(messageOffset + returnValue);
        if (preview) 
		{
          if (previewFromFolder == 0) 
		  {
            dfPlayer.playTrack(returnValue, 1);
          }
          else 
		  {
            dfPlayer.playTrack(previewFromFolder, returnValue);
          }
          delay(1000);
        }
      }
    }
  } while (true);
}

void resetCard() {
  dfPlayer.playMp3Track(800);
  waitForNewCard();

  if (!tonuinoRFID.cardSerialFound())
    return;

  Serial.print(F("Karte wird neu konfiguriert!"));
  setupCard();
}

bool setupFolder(musicDataset * musicDS) 
{
  // Ordner abfragen
  musicDS->folder = voiceMenu(99, 301, 0, true, 0, 0, true);
  if (musicDS->folder == 0) return false;

  int numberOptions = dfPlayer.getFolderTrackCount(musicDS->folder);
  
  // Wiedergabemodus abfragen
  musicDS->mode = voiceMenu(9, 310, 310, false, 0, 0, true);
  
  uint8_t mode = musicDS->mode;
  if (mode == 0) return false;

  // Einzelmodus -> Datei abfragen
  if (mode == 4)
  {
    musicDS->special = voiceMenu(numberOptions, 320, 0, true, musicDS->folder);
  }
  // Admin Funktionen
  if (mode == 6) 
  {
    //musicDS->special = voiceMenu(3, 320, 320);
    musicDS->folder = 0;
    mode = 255;
  }
  // Spezialmodus Von-Bis
  if (mode == 7 || mode == 8 || mode == 9) 
  {
    musicDS->special = voiceMenu(numberOptions, 321, 0, true, musicDS->folder);
    musicDS->special2 = voiceMenu(numberOptions, 322, 0, true, musicDS->folder, musicDS->special);
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
    do {
    } while (dfPlayer.isPlaying());
    writeCard(newCard);
  }
  delay(1000);
}

void evaluateModifierData(nfcTagStruct tempCard)
{
	EModifier modifier = static_cast<EModifier>(tempCard.musicDS.mode);
	uint8_t special = tempCard.musicDS.special;
	
	bool settingChanged = false;
	switch (modifier)
	{
		case LockAll:
		{
			allLocked = !allLocked;
		}
		case LockButtons:
		{
			buttonsLocked = !buttonsLocked;
		}
		case ResetCard:
		{
			resetCard();
			tonuinoRFID.haltAndStop();
		}
		case ResetEEPROM:
		{
			tonuinoEEPROM.resetEEPROM();
			tonuinoEEPROM.resetSettings();
			dfPlayer.playMp3Track(999);
		}
		case Player_SleepTime:
		{
			setSleepTimerValue(special);
		}
	}
	if (settingChanged)
	{
		tonuinoEEPROM.writeSettingsToFlash();
	}
}

void writeCard(nfcTagStruct nfcTag) 
{
	bool statusOK = tonuinoRFID.writeCard(nfcTag);
	dfPlayer.playMp3Track(statusOK ? 400 : 401);
}

#endif
