//sensor BMP280
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;

//LCD
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);



void setup() {
  Serial.begin(115200);

// initialize LCD
  lcd.init();                     
  lcd.backlight();

//Sensor BMP280
  Serial.println(F("BMP280 test"));

  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print(F("Temp = "));
  lcd.setCursor(7, 0);
  lcd.print(bmp.readTemperature());
  lcd.setCursor(12, 0);
  lcd.write(0xDF);
  lcd.print("C");
  delay(1000);
 // lcd.clear();

  lcd.setCursor(0,1);
  lcd.print(F("Press = "));
  lcd.setCursor(9,1);
  lcd.print(bmp.readPressure());
  delay(1000);
  lcd.clear(); 

  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature()); 

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.println(" m");

  Serial.println();
  delay(2000);
}