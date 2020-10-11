/*----------------------------------------------------------
    MH-Z19 CO2 Ampel
  ----------------------------------------------------------*/
#include <Adafruit_NeoPixel.h>  // brauchen wir für die RGB LED
#include <MHZ19_uart.h>         // library für MH-Z19 CO2 Sensor

const int tx_pin = D1;  //Serial tx pin no
const int rx_pin = D2;  //Serial rx pin no

// CO2 Sensor
MHZ19_uart mhz19;
int Messinterval = 1; // alle x Minuten messen

// Ampel
#define PIXEL_PIN D5  // wir haben die RGB LED an PIN D5
// LED kann auch mit 3.3V betrieben werden

// Konfigurieren der NeoPixel Bibliothek
// wieviele Pixels (1), welcher Pin
 Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

/* -------------------------------------------------------------
 *  Liefert Farbkürzel für jeweiligen CO2 Wert.
 */
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

/*---------------------------------------------------
 * Lässt LED blinken in allen Ampelfarben. Die Variable pixels muss vorher initialisiert sein.
 */
void Blink(){
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
        pixels.setPixelColor(0, pixels.Color(0, 0, 255)); //blue
        break;
      case 4:
        pixels.setPixelColor(0, pixels.Color(153, 0, 255)); //violet
        break;
    }
    pixels.show();
//    delay(200); // delay for a period of time (in milliseconds)   
//    pixels.setPixelColor(0,0,0,0);
//    pixels.show();
    delay(200);
  }
}
 
/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup() {
  Serial.begin(9600);
  Serial.println("Setup gestartet ...");
  Serial.println("Initialisiere CO2 Sensor Library ...");
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);
// das funktioniert leider nicht: Dauerschleife
//  while( mhz19.isWarming() ) {
//    Serial.print("MH-Z19 now warming up...  status:");Serial.println(mhz19.getStatus());
//    delay(1000);
//  }

  // NeoPixels Biliothek initialisieren
  Serial.println("Initialisiere NeoPixels Library");
  pixels.begin();

  Serial.println("Setup beendet.");
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop() {
  Serial.println("Messe CO2 und Temperatur");
  int co2ppm = mhz19.getPPM();
  int temp = mhz19.getTemperature();

  Serial.print("co2: "); Serial.println(co2ppm);
  Serial.print("temp: "); Serial.println(temp);

  // Ampel
  // optional: blinkende Ampel
  Serial.println("Blink");
  Blink();
  // jetzt Farbe setzen
  if (co2ppm < 0){
    pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // blue
  } else { 
    // Berechnen der Farbe
    char farbe = GetColor(co2ppm);
    Serial.print("Farbe:");Serial.println(farbe);
  
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
  
  Serial.println("Pause");
  delay(Messinterval * 1000 * 60);
}
