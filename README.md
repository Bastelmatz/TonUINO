# TonUINO
Die DIY Musikbox (nicht nur) für Kinder


# Change Log

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
