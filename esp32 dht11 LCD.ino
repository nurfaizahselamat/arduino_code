#include <DHT.h>
#define DHT11PIN 25
DHT dht(DHT11PIN, DHT11);

#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {
  dht.begin();

  lcd.init();
  lcd.backlight();
}


void loop() {
  float temp = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(temp);
  lcd.print("°");

  float humi = dht.readHumidity();
  lcd.setCursor(1, 1);
  lcd.print("Humi : ");
  lcd.print(humi);
  lcd.print("%");
  delay (1000);
}