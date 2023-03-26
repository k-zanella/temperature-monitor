#include <LiquidCrystal.h>
#include "DHT.h"

// lcd display
#define RS 12
#define E  11
#define D4 9
#define D5 8
#define D6 7
#define D7 6

// dht sensor
#define DHT_PIN  13
#define DHT_TYPE DHT22

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
DHT           dht(DHT_PIN, DHT_TYPE);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
}

float temp, hum, hic = 0;

void loop() {
  temp = dht.readTemperature();
  hum  = dht.readHumidity();
  hic  = dht.computeHeatIndex(temp, hum, false);

  // checks if reads failed
  if (isnan(hum) || isnan(temp)) {
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print(String(temp) + "C" + " -- ");

  lcd.setCursor(10, 0);
  lcd.print(String(hic) + "C");

  lcd.setCursor(0, 1);
  lcd.print(String(hum) + "%");

  delay(1000);
}