# TonUINO Mira
RFID-Musikbox mit Arduino Nano und DFPlayer

# Content

## Support for large folder
- Folder 1-15 can have upto 3000 tracks
- Track names must have 4 digits at the start for tracks > 255 (0256.mp3 to 3000.mp3)
- Tracks <= 255 keep the 3 digit number (001.mp3 to 255.mp3), in all folders
	- Therefore track 1-255 are interchangable among the folders without renaming
	- Extended track variable sizes to 2 bytes (backward compatible on RFID cards)

## Support for Advertisement folder for music cards 
-> Set Folder to 100
- Therefore, advertisement music cards with single mode can be used for memory
	-> Listen to your favourite Tonuino songs while playing memory

## New "Pair" music modes
- play defined titles in 2 folders (A and B)
- Uni-directional pair (e.g. for question-answer pairs)
	- Play track in folder A on card detection
	- Play track in folder B on card removal
- Bi-directional pair (e.g. for vocabularies)
	- Play track on card detection, either in folder A or B
	- Play track on card removal in opposite folder (A, if B was played first and viceversa)
-> both pair modes:
	- Tracks must have same number, but in different folders
	- Recommendation: 
		- folder A for first tracks (e.g. questions)
		- folder B for second tracks (e.g. answers)

## New "Random[]Pair" music modes
- Random uni-directional and bi-directional pair
	- Play 1 RANDOM track from complete folder on card detection
	- Play same track from opposite folder on card removal
- Order of the folders is determined by uni- or bi-directional type (same as normal "pair" modes)
- The "section" variants define start and end track
	-> defines track range within folder instead of complete folder
			
## Memory mode
- Turn on/off with modifier
- Requires 2 (or more) identical cards 
	- identical = with same track number and start resp. end folder
- Supports cards with music modes: SingleTrack, UniDirectionalPair, BiDirectionalPair
- Automatic evaluation of second card with different RFID/UID 
	- Play sound for "right" or "wrong" match
- Repeats first track on return of the same card
- Pair-mode cards play no track on card removal

## Quiz mode
- Turn on/off with modifier
- Requires 1 Random-Uni/Bi-Directional-Pair or AudiDrama card for definition of the folder and track range (step 1)
- Requires multiple non-random Uni/Bi-Directional-Pair or SingleTrack cards (step 2)
	- number of cards >= amount of files defined by RandomPair/Audiodrama card on step 1
- Play new "question" on next button press or return of the RandomPair/Audiodrama card from step 1
- Play evaluation when card from step 2 is put on the RFID reader
	- Play sound for "right" or "wrong" match
	- Multiple retries with other cards are possible until the "right" match
	- Solution on next button press: Play the track in compare folder, if there was no "right" match
	
## New "RandomFolder" music modes
- Random folder - album
	-> Plays all tracks in a random folder in order
- Random folder - party
	-> Plays all tracks in a random folder in random order
- Random folder selection:
	- On every card detection (incl. return of same card)
	- Range is defined by start and end folder number
		
## End-Folder
- Extends range for music selection in combination with start folder
- Supports cards with music modes: 
	- Album, Audiobook	
		-> jumps to first track in next folder on next track action
		-> jumps to last track in previous folder on previous track action
		-> jumps to first track in first folder on first track action
		-> jumps to last track in last folder for last track action
	- Party, AudioDrama -> jumps to random folder on next track action

## Music Modes - Definitions

	AudioDrama = 1
	Album = 2
	Party = 3
	Single = 4
	AudioBook = 5

	Section_AudioDrama = 7
	Section_Album = 8
	Section_Party = 9
	Section_Audiobook = 10
	
	RandomFolder_Album = 20
	RandomFolder_Party = 21
	
	UniDirectionalPair = 30
	BiDirectionalPair = 31
	
	RandomUniDirectionalPair = 35
	RandomBiDirectionalPair = 36
	Section_RandomUniDirectionalPair = 37
	Section_RandomBiDirectionalPair = 38
		
## Modifiers
	- Can be used on cards or triggered by buttons (or something else)
	- So-called BoolValue-Modifiers can trigger on card removal, these are:
		- MODI_TrackContinue
		- MODI_Player_Random, MODI_Player_RepeatSingle, MODI_Player_RepeatAll, MODI_Player_ListenToEnd, MODI_Player_StopOnCardRemoval
		- MODI_Player_FreezeDance, MODI_Player_Memory, MODI_Player_Quiz
		- MODI_LockAll, MODI_LockButtons

## BoolValue - Definitions

	MODI_BOOLVAL_Set = 1
	MODI_BOOLVAL_Undo = 2
	MODI_BOOLVAL_Toggle = 3
	
	MODI_BOOLVAL_OnRemoval_Set = 10
	MODI_BOOLVAL_OnRemoval_Undo = 11
	MODI_BOOLVAL_OnRemoval_Toggle = 12
	
	MODI_BOOLVAL_Set_OnRemoval_Undo = 20
	MODI_BOOLVAL_Undo_OnRemoval_Set = 21
	MODI_BOOLVAL_Toggle_OnRemoval_Toggle = 22

## Modifiers - Definitions

	MODI_TrackContinue = 1
	MODI_TrackNext = 2
	MODI_TrackPrevious = 3
	MODI_TrackFirst = 4
	MODI_TrackLast = 5
	MODI_TrackNumber = 6
	
	MODI_ShortCut = 10
	MODI_Advertisement = 11
	
	MODI_Player_StandbyTime = 20
	MODI_Player_SleepTime = 21
	MODI_Player_Volume = 22
	MODI_Player_VolumeUp = 23
	MODI_Player_VolumeDown = 24
	
	MODI_Player_Random = 30
	MODI_Player_RepeatSingle = 31
	MODI_Player_RepeatAll = 32
	MODI_Player_ListenToEnd = 33
	MODI_Player_StopOnCardRemoval = 34
	
	MODI_Player_FreezeDance = 40
	MODI_Player_Memory = 41
	MODI_Player_Quiz = 42
	
	MODI_LockAll = 50
	MODI_LockButtons = 51
	
	MODI_SetupCard = 60
	MODI_ResetCard = 61
	MODI_ResetEEPROM = 62
	
	MODI_MENU_ChangeSmall = 70
	MODI_MENU_ChangeLarge = 71
	MODI_MENU_Choose = 72
	MODI_MENU_Cancel = 73
	
############################################################

# Use Cases

## Memory
- Single player, cooperative or competitive multiplayer (e.g. who collects more pairs)
- Using new Memory mode/modifier
- Multiple, visual identically cards, the more the better!?
	- Single tracks with SingleTrack cards
	- Question-Answer with uni-directional pairs
	- Title A - Title B with bi-directional pairs
	
## "Think & Say" Quiz with Pair Cards
- Single player, cooperative or competitive multiplayer (e.g. who says the correct(?) answer first?)
- "Answer" should be announced verbal ("Think & Say") or written down ("Think & Write") before card is removed and corret answer is played
- With Uni/Bi-Directional-Pair Cards
	- multiple cards -> 1 defined "question" can/must be selected
- With Random-Uni/Bi-Directional-Pair Cards -> RECOMMENDED
	- random question(s) with only 1 card in total
	- E.g. use Uni-Directional-Pairs for "How sounds the cat?" - "Meeow"
	- E.g. use Bi-Directional-Pairs to train vocabularies
	
## "Think & Search" Quiz
- Single player, cooperative or competitive multiplayer (e.g. who finds the correct(?) answer first?)
- Using new Quiz mode/modifier
- Multiple, visual identifiable cards
	- Single tracks with SingleTrack cards
	- Question-Answer with uni-directional pairs
	- Title A - Title B with bi-directional pairs

## Uni/Bi-Directional-Pair Cards with 3 in 1 functionality
1) Think & Say Quiz
2) Memory (requires 2 or more cards with same data, visually identically)
3) Think & Search Quiz (cards must be visually identifiable)
-> therefore, "identical cards" (for memory) and "unique topping" (for quiz) must be combinable (e.g. plugable or adhering)

############################################################
	
# Change Log

## Version Mira 1.1 (19.04.2021)
- Add support for large folders (1-15) with upto 3000 songs (requires 4 digit track number pattern: 0256.mp3 to 3000.mp3)
	- Extended track variable sizes to 2 bytes (backward compatible on RFID cards)
- Add support for Advertisement folder for music cards -> Set Folder to 100
- Add new music modes for random uni- and bi-directional pairs
- Add new music modes for uni- and bi-directional pairs
- Add memory mode
- Add quiz mode
- Add support for end-folder
- Save recent track and folder for cards with any audiobook mode on RFID card instead of EEPROM
- Save recent music dataset to EEPROM (to start on next power-up without card)
- Add option to really reset card (write 0s)
- Play next track on card return, if currently playing
- Extend bool modifiers to apply on card removal
- Replace JCButton library with own implementation
- Add dozens of modifiers
- Now nearly all original Tonuino code refactored
- Add support for LED animation (12 neopixel)


## Version Mira 1.0 (19.02.2021)
- Complete code refactoring to use multiple .cpp/.h files
- Remove admin menu and settings
- Add "Stop on card removal" feature, disabled by default
- Add Tonuino RFID Tool (to read and write RFID tags)
- Add central modifier handling (for player modification)
- Replace modifier classes with respective settings
- Add loop for voice menu options
- Play first/last track on long pressed previous/next button while playing
- Add support for rotary encoder (used for volume control)
- Add support for ultrasonic sensor (used for track start in coinbox)
- Add start/fix music dataset (used for coinbox without RFID reader)


## Version 2.1 Mira (15.11.2020)
- Stop LED an digital Pin 6 hinzugefügt (leuchtet wenn DFPlayer nicht busy ist, d.h. gestoppt ist)
- Letzte Karte (d.h. Ordner und Modus) wird im EEPROM gespeichert und bei (Neu)Start geladen (sodass beim Neustart die letzte Karte nicht noch einmal aufgelegt werden muss) 
- Bei Start den Sound 261 abspielen (anstelle Shortcut 3)
- Lautstärke Default-Werte und Limits verringert (für Verstärker PAM8403)
- Lautstärke-Drehregler (Poti an A2) ersetzt die Lautstärke-Tasten
- Programmcode aufgeräumt


## Version 2.1 (xx.xx.xxxx) noch WIP
- Partymodus hat nun eine Queue -> jedes Lied kommt nur genau 1x vorkommt
- Neue Wiedergabe-Modi "Spezialmodus Von-Bis" - Hörspiel, Album und Party -> erlaubt z.B. verschiedene Alben in einem Ordner zu haben und je mit einer Karte zu verknüpfen
- Admin-Menü
- Maximale, Minimale und Initiale Lautstärke
- Karten werden nun über das Admin-Menü neu konfiguriert
- die Funktion der Lautstärketasten (lauter/leiser oder vor/zurück) kann im Adminmenü vertauscht werden
- Shortcuts können konfiguriert werden!
- Support für 5 Knöpfe hinzugefügt
- Reset der Einstellungen ins Adminmenü verschoben
- Modikationskarten (Sleeptimer, Tastensperre, Stopptanz, KiTa-Modus)
- Admin-Menü kann abgesichert werden

## Version 2.01 (01.11.2018)
- kleiner Fix um die Probleme beim Anlernen von Karten zu reduzieren

## Version 2.0 (26.08.2018)

- Lautstärke wird nun über einen langen Tastendruck geändert
- bei kurzem Tastendruck wird der nächste / vorherige Track abgespielt (je nach Wiedergabemodus nicht verfügbar)
- Während der Wiedergabe wird bei langem Tastendruck auf Play/Pause die Nummer des aktuellen Tracks angesagt
- Neuer Wiedergabemodus: **Einzelmodus**
  Eine Karte kann mit einer einzelnen Datei aus einem Ordner verknüpft werden. Dadurch sind theoretisch 25000 verschiedene Karten für je eine Datei möglich
- Neuer Wiedergabemodus: **Hörbuch-Modus**
  Funktioniert genau wie der Album-Modus. Zusätzlich wir der Fortschritt im EEPROM des Arduinos gespeichert und beim nächsten mal wird bei der jeweils letzten Datei neu gestartet. Leider kann nur der Track, nicht die Stelle im Track gespeichert werden
- Um mehr als 100 Karten zu unterstützen wird die Konfiguration der Karten nicht mehr im EEPROM gespeichert sondern direkt auf den Karten - die Karte muss daher beim Anlernen aufgelegt bleiben!
- Durch einen langen Druck auf Play/Pause kann **eine Karte neu konfiguriert** werden
- In den Auswahldialogen kann durch langen Druck auf die Lautstärketasten jeweils um 10 Ordner oder Dateien vor und zurück gesprungen werden
- Reset des MP3 Moduls beim Start entfernt - war nicht nötig und hat "Krach" gemacht
