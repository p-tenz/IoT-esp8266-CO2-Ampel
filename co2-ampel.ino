#include <SoftwareSerial.h>     // brauchen wir für serielle Kommunikation mit dem Sensor
#include <Adafruit_NeoPixel.h>  // brauchen wir für die RGB LED
// brauchen wir das? Geht auch ohne ...
//extern "C" {
//#include "user_interface.h"
//}

#define PIXEL_PIN D5  // wir haben die RGB LED an PIN D5
// LED kann auch mit 3.3V betrieben werden

// Konfigurieren der NeoPixel Bibliothek
// wieviele Pixels (1), welcher Pin
 Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

//EspClass esp; // brauchen wir, um den ESP schlafen zu schicken
int CO2Wert;  // CO2 Wert in ppm
int Messinterval = 1; // alle x Minuten messen

// RX, TX Pins festlegen
SoftwareSerial co2Serial(D2, D1);

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

char GetColor(int co2) 
{
//  int temp = 150 - (150 * co2 / 1800);  // co2 in Farbe Umrechnen
//  if (temp < 0)temp += 256;             // wir wollen einen Wert zw. 0 und 255

  if (co2 < 1000) {
    // grün 
    return 'G';
  } else if (co2 < 2000) {
    // gelb
    return 'Y';
  } else {
    // rot
    return 'R';
  }
  if (co2 > 2500) {
    // violett
    return 'V';
  }
}

void setup() {
  // verbinde D0 mit RST für WakeUp (Kabel stecken nicht vergessen)
  pinMode(D0, WAKEUP_PULLUP);

  // messen
  co2Serial.begin(9600);              // serielle Kommunikation mit dem Sensor beginnen
  CO2Wert = leseCO2();                // MH-Z19 CO2 Sensor lesen

  // NeoPixels Biliothek initialisieren
  pixels.begin();

  // blink in all colors ending blue to show that thing is working
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
    delay(200); // delay for a period of time (in milliseconds)   
    pixels.setPixelColor(0,0,0,0);
    pixels.show();
    delay(200);
  }

  if (CO2Wert < 0){
    pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // blue
  } else { 
    // Berechnen der Farbe
    char farbe = GetColor(CO2Wert);
  
    switch (farbe) 
    {
      case 'G': 
        pixels.setPixelColor(0, pixels.Color(0, 255, 0));
        break;
      case 'R': 
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        break;
      case 'Y': 
        pixels.setPixelColor(0, pixels.Color(255, 153, 0));
        break;
      case 'V': 
        pixels.setPixelColor(0, pixels.Color(153, 0, 255));
        break;      
      default:
        pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // blue
        break;
    }
  }
  
  pixels.show(); // This sends the updated pixel color to the hardware.
  

  // Ausgabe
  Serial.begin(115200);               // serielle Kommunikation mit dem PC beginnen
  Serial.println("");
  Serial.println("Wach auf und geh messen ...");
  Serial.printf("CO2 Wert = %d ppm\n\n", CO2Wert);
  Serial.println("Geh wieder schlafen ...");
  
  //esp.deepSleep(Messinterval * 60e6, WAKE_RF_DISABLED); // ESP8266 geht für x Minuten schlafen
    // convert to microseconds
  ESP.deepSleep(Messinterval * 60e6);
}
 
void loop()
{
  // empty because of deepsleep
}
