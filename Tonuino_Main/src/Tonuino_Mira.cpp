
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

uint8_t trackInEEPROM = 0;
nfcTagObject myCard;
folderSettings lastFolder;

bool usePowerOff = false;

uint8_t voiceMenu(int numberOfOptions, int startMessage, int messageOffset,
                  bool preview = false, int previewFromFolder = 0, int defaultValue = 0, bool exitWithLongPress = false);
bool checkTwo ( uint8_t a[], uint8_t b[] );
void writeCard(nfcTagObject nfcTag);
void adminMenu(bool fromCard = false);

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

TonuinoPlayer tonuinoPlayer()
{
	return dfPlayer.tonuinoPlayer;
}

void loadDataFromFlash()
{
	tonuinoEEPROM.loadSettingsFromFlash();
	lastFolder = tonuinoEEPROM.loadLastFolderFromFlash();
	
	dfPlayer.volumeMin = tonuinoEEPROM.mySettings.minVolume;
	dfPlayer.volumeMax = tonuinoEEPROM.mySettings.maxVolume;
}

class Modifier {
  public:
    virtual void loop() {}
    virtual bool handlePause() {
      return false;
    }
    virtual bool handleNext() {
      return false;
    }
    virtual bool handlePrevious() {
      return false;
    }
    virtual bool handleNextButton() {
      return false;
    }
    virtual bool handlePreviousButton() {
      return false;
    }
    virtual bool handleVolumeUp() {
      return false;
    }
    virtual bool handleVolumeDown() {
      return false;
    }
    virtual bool handleRFID(nfcTagObject *newCard) {
      return false;
    }
    virtual uint8_t getActive() {
      return 0;
    }
    Modifier() {

    }
};

Modifier *activeModifier = NULL;

class FreezeDance: public Modifier {
  private:
    unsigned long nextStopAtMillis = 0;
    const uint8_t minSecondsBetweenStops = 5;
    const uint8_t maxSecondsBetweenStops = 30;

    void setNextStopAtMillis() {
      uint16_t seconds = random(this->minSecondsBetweenStops, this->maxSecondsBetweenStops + 1);
      Serial.println(F("=== FreezeDance::setNextStopAtMillis()"));
      Serial.println(seconds);
      this->nextStopAtMillis = millis() + seconds * 1000;
    }

  public:
    void loop() {
      if (this->nextStopAtMillis != 0 && millis() > this->nextStopAtMillis) {
        Serial.println(F("== FreezeDance::loop() -> FREEZE!"));
        if (dfPlayer.isPlaying()) {
          dfPlayer.playAdvertisement(301);
          delay(500);
        }
        setNextStopAtMillis();
      }
    }
    FreezeDance(void) {
      Serial.println(F("=== FreezeDance()"));
      if (dfPlayer.isPlaying()) {
        delay(1000);
        dfPlayer.playAdvertisement(300);
        delay(500);
      }
      setNextStopAtMillis();
    }
    uint8_t getActive() {
      Serial.println(F("== FreezeDance::getActive()"));
      return 2;
    }
};

class Locked: public Modifier {
  public:
    virtual bool handlePause()     {
      Serial.println(F("== Locked::handlePause() -> LOCKED!"));
      return true;
    }
    virtual bool handleNextButton()       {
      Serial.println(F("== Locked::handleNextButton() -> LOCKED!"));
      return true;
    }
    virtual bool handlePreviousButton() {
      Serial.println(F("== Locked::handlePreviousButton() -> LOCKED!"));
      return true;
    }
    virtual bool handleVolumeUp()   {
      Serial.println(F("== Locked::handleVolumeUp() -> LOCKED!"));
      return true;
    }
    virtual bool handleVolumeDown() {
      Serial.println(F("== Locked::handleVolumeDown() -> LOCKED!"));
      return true;
    }
    virtual bool handleRFID(nfcTagObject *newCard) {
      Serial.println(F("== Locked::handleRFID() -> LOCKED!"));
      return true;
    }
    Locked(void) {
      Serial.println(F("=== Locked()"));
      //      if (isPlaying())
      //        mp3.playAdvertisement(303);
    }
    uint8_t getActive() {
      return 3;
    }
};

class ToddlerMode: public Modifier {
  public:
    virtual bool handlePause()     {
      Serial.println(F("== ToddlerMode::handlePause() -> LOCKED!"));
      return true;
    }
    virtual bool handleNextButton()       {
      Serial.println(F("== ToddlerMode::handleNextButton() -> LOCKED!"));
      return true;
    }
    virtual bool handlePreviousButton() {
      Serial.println(F("== ToddlerMode::handlePreviousButton() -> LOCKED!"));
      return true;
    }
    virtual bool handleVolumeUp()   {
      Serial.println(F("== ToddlerMode::handleVolumeUp() -> LOCKED!"));
      return true;
    }
    virtual bool handleVolumeDown() {
      Serial.println(F("== ToddlerMode::handleVolumeDown() -> LOCKED!"));
      return true;
    }
    ToddlerMode(void) {
      Serial.println(F("=== ToddlerMode()"));
      //      if (isPlaying())
      //        mp3.playAdvertisement(304);
    }
    uint8_t getActive() {
      Serial.println(F("== ToddlerMode::getActive()"));
      return 4;
    }
};

class KindergardenMode: public Modifier {
  private:
    nfcTagObject nextCard;
    bool cardQueued = false;

  public:
    virtual bool handleNext() {
      Serial.println(F("== KindergardenMode::handleNext() -> NEXT"));
      //if (this->nextCard.cookie == cardCookie && this->nextCard.nfcFolderSettings.folder != 0 && this->nextCard.nfcFolderSettings.mode != 0) {
      //myFolder = &this->nextCard.nfcFolderSettings;
      if (this->cardQueued == true) {
        this->cardQueued = false;

        myCard = nextCard;
        loadAndPlayFolder(myCard.nfcFolderSettings);
        return true;
      }
      return false;
    }
    //    virtual bool handlePause()     {
    //      Serial.println(F("== KindergardenMode::handlePause() -> LOCKED!"));
    //      return true;
    //    }
    virtual bool handleNextButton()       {
      Serial.println(F("== KindergardenMode::handleNextButton() -> LOCKED!"));
      return true;
    }
    virtual bool handlePreviousButton() {
      Serial.println(F("== KindergardenMode::handlePreviousButton() -> LOCKED!"));
      return true;
    }
    virtual bool handleRFID(nfcTagObject * newCard) { // lot of work to do!
      Serial.println(F("== KindergardenMode::handleRFID() -> queued!"));
      this->nextCard = *newCard;
      this->cardQueued = true;
      if (!dfPlayer.isPlaying()) {
        handleNext();
      }
      return true;
    }
    KindergardenMode() {
      Serial.println(F("=== KindergardenMode()"));
      //      if (isPlaying())
      //        mp3.playAdvertisement(305);
      //      delay(500);
    }
    uint8_t getActive() {
      Serial.println(F("== KindergardenMode::getActive()"));
      return 5;
    }
};

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
	if (dfPlayer.folderDataset.mode == AudioBook)
	{
		uint8_t currentTrack = tonuinoPlayer().currentTrack();
		if (currentTrack > 0 && trackInEEPROM != currentTrack)
		{
			Serial.print("Save current track to EEPROM: ");
			Serial.print(currentTrack);
			tonuinoEEPROM.writeLastTrackToFlash(currentTrack, dfPlayer.folderDataset.folder);
		}
	}
}

void playShortCut(uint8_t shortCut) 
{
	Serial.println(F("=== playShortCut()"));
	Serial.println(shortCut);
	folderSettings shortCutData = tonuinoEEPROM.mySettings.shortCuts[shortCut];
	if (shortCutData.folder != 0) 
	{
		loadAndPlayFolder(shortCutData);
	}
	else
	{
		Serial.println(F("Shortcut not configured!"));
	}
}

void setStandbyTimerValue()
{
	tonuinoPlayer().standbyTimer.timeInMin = tonuinoEEPROM.mySettings.standbyTimer;
}

void setSleepTimerValue()
{
	tonuinoPlayer().sleepTimer.timeInMin = 0;
}

uint8_t getLastTrack(folderSettings folderDataset)
{
	if (folderDataset.mode == AudioBook) 
	{
		trackInEEPROM = tonuinoEEPROM.loadLastTrackFromFlash(folderDataset.folder);
		return trackInEEPROM;
	}
	return 0;
}

void loadFolder(folderSettings folder)
{
    uint8_t lastTrack = getLastTrack(folder);
	dfPlayer.loadFolder(folder, lastTrack);
}

void loadAndPlayFolder(folderSettings folder)
{
	uint8_t lastTrack = getLastTrack(folder);
	dfPlayer.loadAndPlayFolder(folder, lastTrack);
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
  
  // activate standby timer
  setStandbyTimerValue();
  setSleepTimerValue();
  
  // DFPlayer Mini initialisieren
  dfPlayer.setup();
  dfPlayer.setVolume(tonuinoEEPROM.mySettings.initVolume);
  oldPotiValue = dfPlayer.volume;
  dfPlayer.setEqualizer(tonuinoEEPROM.mySettings.eq - 1);

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
  loadFolder(lastFolder);
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

void doNextButton() 
{
	if (activeModifier != NULL)
		if (activeModifier->handleNextButton() == true)
			return;

	dfPlayer.nextTrack();
}

void doPreviousButton() 
{
	if (activeModifier != NULL)
		if (activeModifier->handlePreviousButton() == true)
			return;

	dfPlayer.previousTrack();
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

		if (pollCardResult == MUSICCARD_NEW || 
			pollCardResult == MUSICCARD_IS_BACK ||
			pollCardResult == MODIFIERCARD_NEW)
		{
			evaluateCardData(tonuinoRFID.readCardData, myCard);
		}

		switch (pollCardResult)
		{
		case MUSICCARD_NEW:
			onNewCard();
			break;

		case ALLCARDS_GONE:
			if (StopPlayOnCardRemoval)
			{
				dfPlayer.pauseAndStandBy();
			}
			break;

		case MUSICCARD_IS_BACK:
			dfPlayer.continueTitle();
			break;
		}    
	}
}

void setStopLight()
{
  if (dfPlayer.isPlaying())
  {
    digitalWrite(stopLED, LOW);
  }
  else
  {
    digitalWrite(stopLED, HIGH);
  }
}

bool m_lastPlayState = true;

void loopTonuino() 
{
	checkSleepAtMillis();
    checkStandbyAtMillis();
	checkCurrentTrack();
    dfPlayer.loop();

    bool isCurrentlyPlaying = dfPlayer.isPlaying();
    if (m_lastPlayState != isCurrentlyPlaying)
    {
      setStopLight();
      m_lastPlayState = isCurrentlyPlaying;
    }

    // Modifier : WIP!
    if (activeModifier != NULL) {
      activeModifier->loop();
    }
      
    // Buttons werden nun über JS_Button gehandelt, dadurch kann jede Taste
    // doppelt belegt werden
    readButtons();

    readPotentiometer(); 
    
    // admin menu
    if ((pauseButton.pressedFor(LONG_PRESS) || nextButton.pressedFor(LONG_PRESS) || previousButton.pressedFor(LONG_PRESS)) 
        && pauseButton.isPressed() && nextButton.isPressed() && previousButton.isPressed()) 
    {
      dfPlayer.pause();
      do {
        readButtons();
      } while (pauseButton.isPressed() || nextButton.isPressed() || previousButton.isPressed());
      readButtons();
      adminMenu();
      return;
    }

    if (pauseButton.wasReleased()) 
    {
      if (activeModifier != NULL)
      {
        if (activeModifier->handlePause() == true)
          return;
      }
      if (ignorePauseButton == false)
      {
		dfPlayer.togglePlay();
      }
      ignorePauseButton = false;
    } else if (pauseButton.pressedFor(LONG_PRESS) && ignorePauseButton == false) 
    {
      if (activeModifier != NULL)
      {
        if (activeModifier->handlePause() == true)
          return;
      }
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

    if (nextButton.wasReleased()) 
    {
      if (isCurrentlyPlaying) 
      {
        doNextButton();
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
        doPreviousButton();
      }
      else 
      {
        playShortCut(2);
      }
    }

    // Ende der Buttons

    handleCardReader();
}

void onNewCard()
{
	if (myCard.cookie == cardCookie && myCard.nfcFolderSettings.folder != 0 && myCard.nfcFolderSettings.mode != 0) 
	{
		dfPlayer.folderDataset = myCard.nfcFolderSettings;
		loadAndPlayFolder(dfPlayer.folderDataset);
		// Save last folder for next power up
		tonuinoEEPROM.writeLastFolderToFlash(dfPlayer.folderDataset);
	}
	// Neue Karte konfigurieren
	else if (myCard.cookie != cardCookie) 
	{
		dfPlayer.folderLoaded = false;
		dfPlayer.playMP3AndWait(300);
		setupCard();
	}
}

void waitForNewCard()
{
  do {
    readButtons();
    if (nextButton.wasReleased() || previousButton.wasReleased()) 
    {
      Serial.println(F("Abgebrochen!"));
      dfPlayer.playMp3Track(802);
      return true;
    }
  } while (!tonuinoRFID.cardDetected());
}

void waitForCardAndWrite(nfcTagObject card)
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

void adminMenu(bool fromCard = false) 
{
  tonuinoPlayer().pauseNoStandBy();
  dfPlayer.pause();
  Serial.println(F("=== adminMenu()"));
  dfPlayer.folderLoaded = false;
  if (fromCard == false) {
    // Admin menu has been locked - it still can be trigged via admin card
    if (tonuinoEEPROM.mySettings.adminMenuLocked == 1) {
      return;
    }
    // Pin check
    else if (tonuinoEEPROM.mySettings.adminMenuLocked == 2) {
      uint8_t pin[4];
      dfPlayer.playMp3Track(991);
      if (askCode(pin) == true) {
        if (checkTwo(pin, tonuinoEEPROM.mySettings.adminMenuPin) == false) {
          return;
        }
      } else {
        return;
      }
    }
    // Match check
    else if (tonuinoEEPROM.mySettings.adminMenuLocked == 3) {
      uint8_t a = random(10, 20);
      uint8_t b = random(1, 10);
      uint8_t c;
      dfPlayer.playMP3AndWait(992);
      dfPlayer.playMP3AndWait(a);

      if (random(1, 3) == 2) {
        // a + b
        c = a + b;
        dfPlayer.playMP3AndWait(993);
      } else {
        // a - b
        b = random(1, a);
        c = a - b;
        dfPlayer.playMP3AndWait(994);
      }
      dfPlayer.playMp3Track(b);
      Serial.println(c);
      uint8_t temp = voiceMenu(255, 0, 0, false);
      if (temp != c) {
        return;
      }
    }
  }
  int subMenu = voiceMenu(12, 900, 900, false, false, 0, true);
  if (subMenu == 0)
    return;
  if (subMenu == 1) 
  {
    resetCard();
    tonuinoRFID.haltAndStop();
  }
  else if (subMenu == 2) {
    // Maximum Volume
    tonuinoEEPROM.mySettings.maxVolume = voiceMenu(30 - tonuinoEEPROM.mySettings.minVolume, 930, tonuinoEEPROM.mySettings.minVolume, false, false, tonuinoEEPROM.mySettings.maxVolume - tonuinoEEPROM.mySettings.minVolume) + tonuinoEEPROM.mySettings.minVolume;
  }
  else if (subMenu == 3) {
    // Minimum Volume
    tonuinoEEPROM.mySettings.minVolume = voiceMenu(tonuinoEEPROM.mySettings.maxVolume - 1, 931, 0, false, false, tonuinoEEPROM.mySettings.minVolume);
  }
  else if (subMenu == 4) {
    // Initial Volume
    tonuinoEEPROM.mySettings.initVolume = voiceMenu(tonuinoEEPROM.mySettings.maxVolume - tonuinoEEPROM.mySettings.minVolume + 1, 932, tonuinoEEPROM.mySettings.minVolume - 1, false, false, tonuinoEEPROM.mySettings.initVolume - tonuinoEEPROM.mySettings.minVolume + 1) + tonuinoEEPROM.mySettings.minVolume - 1;
  }
  else if (subMenu == 5) {
    // EQ
    tonuinoEEPROM.mySettings.eq = voiceMenu(6, 920, 920, false, false, tonuinoEEPROM.mySettings.eq);
    dfPlayer.setEqualizer(tonuinoEEPROM.mySettings.eq - 1);
  }
  else if (subMenu == 6) {
    // create modifier card
    nfcTagObject tempCard;
    tempCard.cookie = cardCookie;
    tempCard.version = 1;
    tempCard.nfcFolderSettings.folder = 0;
    tempCard.nfcFolderSettings.special = 0;
    tempCard.nfcFolderSettings.special2 = 0;
    tempCard.nfcFolderSettings.mode = voiceMenu(6, 970, 970, false, false, 0, true);

    if (tempCard.nfcFolderSettings.mode != 0) {
      if (tempCard.nfcFolderSettings.mode == 1) {
        switch (voiceMenu(4, 960, 960)) {
          case 1: tempCard.nfcFolderSettings.special = 5; break;
          case 2: tempCard.nfcFolderSettings.special = 15; break;
          case 3: tempCard.nfcFolderSettings.special = 30; break;
          case 4: tempCard.nfcFolderSettings.special = 60; break;
        }
      }
      dfPlayer.playMp3Track(800);
      
	  waitForCardAndWrite(tempCard);
    }
  }
  else if (subMenu == 7) {
    uint8_t shortcut = voiceMenu(4, 940, 940);
    setupFolder(&tonuinoEEPROM.mySettings.shortCuts[shortcut - 1]);
    dfPlayer.playMp3Track(400);
  }
  else if (subMenu == 8) {
    switch (voiceMenu(5, 960, 960)) {
      case 1: tonuinoEEPROM.mySettings.standbyTimer = 5; break;
      case 2: tonuinoEEPROM.mySettings.standbyTimer = 15; break;
      case 3: tonuinoEEPROM.mySettings.standbyTimer = 30; break;
      case 4: tonuinoEEPROM.mySettings.standbyTimer = 60; break;
      case 5: tonuinoEEPROM.mySettings.standbyTimer = 0; break;
    }
  }
  else if (subMenu == 9) {
    // Create Cards for Folder
    // Ordner abfragen
    nfcTagObject tempCard;
    tempCard.cookie = cardCookie;
    tempCard.version = 1;
    tempCard.nfcFolderSettings.mode = 4;
    tempCard.nfcFolderSettings.folder = voiceMenu(99, 301, 0, true);
    uint8_t special = voiceMenu(dfPlayer.getFolderTrackCount(tempCard.nfcFolderSettings.folder), 321, 0,
                                true, tempCard.nfcFolderSettings.folder);
    uint8_t special2 = voiceMenu(dfPlayer.getFolderTrackCount(tempCard.nfcFolderSettings.folder), 322, 0,
                                 true, tempCard.nfcFolderSettings.folder, special);

    dfPlayer.playMP3AndWait(936);
    for (uint8_t x = special; x <= special2; x++) {
      dfPlayer.playMp3Track(x);
      tempCard.nfcFolderSettings.special = x;
      Serial.print(x);
      
	  waitForCardAndWrite(tempCard);
    }
  }
  else if (subMenu == 11) 
  {
    tonuinoEEPROM.resetEEPROM();
    tonuinoEEPROM.resetSettings();
    dfPlayer.playMp3Track(999);
  }
  // lock admin menu
  else if (subMenu == 12) {
    int temp = voiceMenu(4, 980, 980, false);
    if (temp == 1) {
      tonuinoEEPROM.mySettings.adminMenuLocked = 0;
    }
    else if (temp == 2) {
      tonuinoEEPROM.mySettings.adminMenuLocked = 1;
    }
    else if (temp == 3) {
      int8_t pin[4];
      dfPlayer.playMp3Track(991);
      if (askCode(pin)) {
        memcpy(tonuinoEEPROM.mySettings.adminMenuPin, pin, 4);
        tonuinoEEPROM.mySettings.adminMenuLocked = 2;
      }
    }
    else if (temp == 4) {
      tonuinoEEPROM.mySettings.adminMenuLocked = 3;
    }

  }
  tonuinoEEPROM.writeSettingsToFlash();
  setStandbyTimerValue();
  dfPlayer.pauseAndStandBy();
}

bool askCode(uint8_t *code) {
  uint8_t x = 0;
  while (x < 4) {
    readButtons();
    if (pauseButton.pressedFor(LONG_PRESS))
      break;
    if (pauseButton.wasReleased())
      code[x++] = 1;
    if (nextButton.wasReleased())
      code[x++] = 2;
    if (previousButton.wasReleased())
      code[x++] = 3;
  }
  return true;
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

bool setupFolder(folderSettings * theFolder) {
  // Ordner abfragen
  theFolder->folder = voiceMenu(99, 301, 0, true, 0, 0, true);
  if (theFolder->folder == 0) return false;

  // Wiedergabemodus abfragen
  theFolder->mode = voiceMenu(9, 310, 310, false, 0, 0, true);
  if (theFolder->mode == 0) return false;

  // Einzelmodus -> Datei abfragen
  if (theFolder->mode == 4)
    theFolder->special = voiceMenu(dfPlayer.getFolderTrackCount(theFolder->folder), 320, 0,
                                   true, theFolder->folder);
  // Admin Funktionen
  if (theFolder->mode == 6) {
    //theFolder->special = voiceMenu(3, 320, 320);
    theFolder->folder = 0;
    theFolder->mode = 255;
  }
  // Spezialmodus Von-Bis
  if (theFolder->mode == 7 || theFolder->mode == 8 || theFolder->mode == 9) {
    theFolder->special = voiceMenu(dfPlayer.getFolderTrackCount(theFolder->folder), 321, 0,
                                   true, theFolder->folder);
    theFolder->special2 = voiceMenu(dfPlayer.getFolderTrackCount(theFolder->folder), 322, 0,
                                    true, theFolder->folder, theFolder->special);
  }
  return true;
}

void setupCard() {
  dfPlayer.pause();
  Serial.println(F("=== setupCard()"));
  nfcTagObject newCard;
  if (setupFolder(&newCard.nfcFolderSettings) == true)
  {
    // Karte ist konfiguriert -> speichern
    dfPlayer.pause();
    do {
    } while (dfPlayer.isPlaying());
    writeCard(newCard);
  }
  delay(1000);
}

bool evaluateCardData(nfcTagObject tempCard, nfcTagObject nfcTag)
{
  if (tempCard.cookie == cardCookie) 
  {
    if (activeModifier != NULL && tempCard.nfcFolderSettings.folder != 0) {
      if (activeModifier->handleRFID(&tempCard) == true) {
        return false;
      }
    }

    if (tempCard.nfcFolderSettings.folder == 0) 
    {
      if (activeModifier != NULL) 
      {
        if (activeModifier->getActive() == tempCard.nfcFolderSettings.mode) 
        {
          delete activeModifier;
          activeModifier = NULL;
          Serial.println(F("modifier removed"));
          dfPlayer.playAdvertisement(261);
          delay(2000);
          return false;
        }
      }
      if (tempCard.nfcFolderSettings.mode != 0 && tempCard.nfcFolderSettings.mode != 255) 
      {
        dfPlayer.playAdvertisement(260);
      }
      switch (tempCard.nfcFolderSettings.mode ) 
	  {
        case 0:
        case 255:
          tonuinoRFID.haltAndStop(); adminMenu(true);  break;
        case 2: activeModifier = new FreezeDance(); break;
        case 3: activeModifier = new Locked(); break;
        case 4: activeModifier = new ToddlerMode(); break;
        case 5: activeModifier = new KindergardenMode(); break;
      }
      delay(2000);
      return false;
    }
    else {
      memcpy(&nfcTag, &tempCard, sizeof(nfcTagObject));
      loadFolder(nfcTag.nfcFolderSettings);
    }
    return true;
  }
  else {
    memcpy(&nfcTag, &tempCard, sizeof(nfcTagObject));
    return true;
  }
}

void writeCard(nfcTagObject nfcTag) 
{
	bool statusOK = tonuinoRFID.writeCard(nfcTag);
	dfPlayer.playMp3Track(statusOK ? 400 : 401);
}


///////////////////////////////////////// Check Bytes   ///////////////////////////////////
bool checkTwo ( uint8_t a[], uint8_t b[] ) {
  for ( uint8_t k = 0; k < 4; k++ ) {   // Loop 4 times
    if ( a[k] != b[k] ) {     // IF a != b then false, because: one fails, all fail
      return false;
    }
  }
  return true;
}

#endif
