#include <SoftwareSerial.h>
extern "C" {
#include "user_interface.h"
}

//EspClass esp; // brauchen wir, um den ESP schlafen zu schicken
int CO2Wert;  // CO2 Wert in ppm
int Messinterval = 1; // alle x Minuten messen

// RX, TX Pins festlegen
SoftwareSerial co2Serial(D2, D1);

int leseCO2()                         // Kommunikation mit MH-Z19 CO2 Sensor
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
  return ppm;                         // Antwort des MH-Z19 CO2 Sensors in ppm
}

void setup() {
  // verbinde D0 mit RST für WakeUp (Kabel stecken nicht vergessen)
  pinMode(D0, WAKEUP_PULLUP);

  // messen
  co2Serial.begin(9600);
  CO2Wert = leseCO2();                // MH-Z19 CO2 Sensor lesen

  // Ausgabe
  Serial.begin(115200);
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
}
