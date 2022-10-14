#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);  
  Serial.println(F("BMP280 test"));



  if (!bmp.begin(0x76)) { 
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1)
      ;
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, /* Operating Mode. */  
                  Adafruit_BMP280::SAMPLING_X2,                        /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,                       /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,                         /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500);                    /* Standby time. */
}

void loop() {
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature()); 
  Serial.println(" °C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.println(" m");

  Serial.println();
  delay(2000);
}