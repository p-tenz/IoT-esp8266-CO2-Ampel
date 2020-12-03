# IoT-esp8266-CO2-Ampel
IoT Projekt mit WEMOS D1 Mini

Misst CO2 Wert der Raumluft und zeigt je nach Höhe des Wertes eine Ampelfarbe an. Diese signalisiert, ob gelüftet werden muss.

![Ampel in §d-gedruckten Gehäuse](co2ampel-3.jpg?raw=true)

## Was wird benötigt?
### Hardware
1. Mikrocontroller: WEMOS D1 Mini (ESP8266 Board)
2. CO2 Sensor: MHZ-19
3. mehrfarbige LED: D1Z-RGB-LED (Shield)
4. USB Mini Kabel mit Netzstecker
5. Verbindungskäbelchen
6. evtl. Gehäuse

### Software
* Treiber für WEMOS D1 Mini: https://docs.wemos.cc/en/latest/ch340_driver.html
* Arduino IDE
* Bibliotheken
  * für Kommunikation mit dem Sensor: SoftwareSerial Library
  * für RGB LED: Adafruit_NeoPixel_Library
  * optional (in co2-ampel-2.ino verwendet) zum Ansteuern des CO2 Sensors MHZ-19: MHZ19_uart Library, siehe https://github.com/nara256/mhz19_uart

## Wie baut man das alles zusammen?
1. Wemos D1 Mini und RGB-LED SHield mit Steckerleisten versehen (dabei auf Ausrichtung achten) und zusammenstecken.
2. D1 Mini mit MHZ-19 verkabeln:
  * [D1] 5V - [MHZ-19] VIN - rot
  * [D1] G  - [MHZ-19] GND - schwarz
  * [D1] D6 - [MHZ-19] RX  - grün
  * [D1] D7 - [MHZ-19] TX  - lila
  
![Verkabelung](Verkabelung.jpg?raw=true)

## Sketches
Ich verwende den zuletzt genannten.

### co2-ampl.ino
* erster Versuch mit Breadboard, LED an D5, Sensor an D1 und D2
* sendet selbst den Byte-Code für Messung an den MHZ-19
* lässt D1 Mini zwischen den Messungen in den Tiefschlaf fallen (leere Loop-Methode, alles in Setup-Methode)
### co2-ampel-2.ino
* zweiter Versuch mit Verwendung der MHZ-19_uart Library (siehe Software)
* misst auch die Temperatur (not supported)
* zur Wahl mit Verwendung von Tiefschlaf zwischen Messungen
### d1mini-mhz19-co2-ampel-loop.ino
* einfache Variante für RGB-LED Shield (LED an D2), Sensor verkabelt (D6 und D7)
* ohne Tiefschlaf
* Grenzwerte 1000, 1400 (und 2000)

## Zu beachten
* RGB-LED Shield verwendet Datenpin D2. Dieser ist im Programm beim Initialisiern der Library festgelegt. Ebenso die Anzahl der LEDs, also 1.
* Das RGB-LED Shield kann in seiner Helligkeit an die Umgebung angepasst werden.
* CO2-Sensor MHZ-19 wird an die Datenpins D6 und D7 angeschlossen. Dies ist auch im Programm festgelegt.
* Um zu prüfen, ob der CO2-Sensor korrekt kalibriert ist, schließt man ihn an den PC an und stellt ihn an ein geöffnetes Fenster. Im seriellen Monitor werden die Werte ausgegeben. Diese sollten um die 400ppm liegen. Bitte Zugluft und direkte Sonne vermeiden! 
* Die verwendten Grenzwerte sind: 
  * grün bei Werten unter 1000ppm
  * gelb bei Werten zwischen 1000ppm un 1400 ppm
  * rot bei Werten über 1400ppm
  * (violett bei Werten über 2000ppm)

## Weitere Links
* Hintergrund zum Thema: https://www.umwelt-campus.de/forschung/projekte/iot-werkstatt/ideen-zur-corona-krise
* Datenblatt MHZ19: https://www.winsen-sensor.com/d/files/PDF/Infrared%20Gas%20Sensor/NDIR%20CO2%20SENSOR/MH-Z19%20CO2%20Ver1.0.pdf
* Gespickelt auf: http://esp8266-server.de/CO2Ampel.html

## Gehäuse
Habe ein 3D Modell für den Wemos D1 gefunden und etwas angepasst. Bin noch am Optimieren. Sobald ich fertig bin, gibt es die STL Datei.