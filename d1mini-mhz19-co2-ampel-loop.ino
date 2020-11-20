#include <SoftwareSerial.h>     // brauchen wir für serielle Kommunikation mit dem Sensor
#include <Adafruit_NeoPixel.h>  // brauchen wir für die RGB LED

#define PIXEL_PIN D2  // wir haben die RGB LED an PIN D2

// Konfigurieren der NeoPixel Bibliothek
// wieviele Pixels (1), welcher Pin
 Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int CO2Wert;  // CO2 Wert in ppm
int Messinterval = 1; // alle x Minuten messen

// TX, RX Pins festlegen
SoftwareSerial co2Serial(D7, D6);


void setup() {
  Serial.begin(115200);               // serielle Kommunikation mit dem PC beginnen
  delay(10);
//  Serial.println("***");
//  Serial.println("Setup gestartet ...");
  
  // initialisieren
  co2Serial.begin(9600);              // serielle Kommunikation mit dem Sensor beginnen

  // NeoPixels Biliothek initialisieren
  pixels.begin();

  // einmal blinken bitte
  delay(10);
  blinkInAllColors();
}
 
void loop()
{
  // am besten abschalten im Klassenzimmer ;-)
  //blinkInAllColors();
  
  // MH-Z19 CO2 Sensor lesen
  CO2Wert = leseCO2();      
            
  // Ampelfarbe einstellen
  if (CO2Wert < 0){
    pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // blau=Fehler (oder Neustart)
    
  } else if (CO2Wert < 1000) {
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // grün 
    
  } else if (CO2Wert < 1400) {
    pixels.setPixelColor(0, pixels.Color(255, 153, 0)); // gelb
    
  } else {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // rot
  }
  if (CO2Wert > 2000) {
    pixels.setPixelColor(0, pixels.Color(153, 0, 255)); // violett
  }
  // eingestellte Pixelfarbe an die Lampe senden 
  pixels.show(); 

  // Ausgabe
  //Serial.printf("CO2 = %d ppm\n\n", CO2Wert);
  Serial.print("CO2[ppm]:"); Serial.println(CO2Wert);
  //Serial.print("Pause für "); Serial.print(Messinterval); Serial.println(" min");
  delay(Messinterval * 1000 * 60);  // in Millisekunden umrechnen
}

// misst CO2 Wert und liefert ihn zurück in ppm 
// Kommunikation mit MH-Z19B CO2 Sensor
int leseCO2() 
{
  byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
                
  char antwort[9];
  co2Serial.write(cmd, 9);
  co2Serial.readBytes(antwort, 9);
  if (antwort[0] != 0xFF) return -1;
  if (antwort[1] != 0x86) return -1;
  int antwortHigh = (int) antwort[2]; // CO2 High Byte
  int antwortLow = (int) antwort[3];  // CO2 Low Byte
  int ppm = (256 * antwortHigh) + antwortLow;
  return ppm;   // Antwort des MH-Z19 CO2 Sensors in ppm
}

// LED blinkt in allen Farben, endet mit Blau; zeigt dass gemessen wurde
void blinkInAllColors() {
  for (int i=0; i<5; i++)
  {
    switch (i) {
      case 0:
        pixels.setPixelColor(0, pixels.Color(255, 0, 0)); //red
        break;
      case 1:
        pixels.setPixelColor(0, pixels.Color(255, 153, 0)); //yellow
        break;
      case 2:
        pixels.setPixelColor(0, pixels.Color(0, 255, 0)); //green
        break;
      case 3:
        pixels.setPixelColor(0, pixels.Color(153, 0, 255)); //violet
        break;
      case 4:
        pixels.setPixelColor(0, pixels.Color(0, 0, 255)); //blue
        break;
    }
    pixels.show();
    delay(200); // warte kurz (in Millisekunden)   
    pixels.setPixelColor(0,0,0,0);  // Licht aus
    pixels.show();
    delay(200);
  }
}
