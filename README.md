# IoT-esp8266-CO2-Ampel
IoT Projekt mit WEMOS D1 Mini

Misst CO2 Wert der Raumluft und zeigt je nach Höhe des Wertes eine Ampelfarbe an, die signalisiert, ob gelüftet werden muss.

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
  * optional (in co2-ampel-2.ino) zum Ansteuern des CO2 Sensors MHZ-19: MHZ19_uart Library, siehe https://github.com/nara256/mhz19_uart

### Sketches
#### co2-ampl.ino
* erster Versuch
* sendet selbst den Byte-Code für Messung an den MHZ-19
* lässt D1 Mini zwischen den Messungen in den Tiefschlaf fallen (leere Loop-Methode, alles in Setup-Methode)
#### co2-ampel-2.ino
* zweiter Versuch mit Verwendung der MHZ-19_uart Library (siehe Software)
* misst auch die Temperatur (not supported)
* zur Wahl mit Verwendung von Tiefschlaf zwischen Messungen
#### d1mini-mhz19-co2-ampel-loop.ino
* einfache Variante für RGB-LED Shield
* ohne Tiefschlaf
* Grenzwerte 1000, 1400 (und 2000)


### Weitere Links
* Hintergrund zum Thema: https://www.umwelt-campus.de/forschung/projekte/iot-werkstatt/ideen-zur-corona-krise
* Datenblatt MHZ19: https://www.winsen-sensor.com/d/files/PDF/Infrared%20Gas%20Sensor/NDIR%20CO2%20SENSOR/MH-Z19%20CO2%20Ver1.0.pdf
* Gespickelt auf: http://esp8266-server.de/CO2Ampel.html
