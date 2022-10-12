#include <DHT.h>
#define DHT11PIN 25
DHT dht(DHT11PIN, DHT11);


void setup() {
dht.begin ();
Serial.begin (115200);
}


void loop() {
float temp = dht.readTemperature();
Serial.print ("Temperature : ");
Serial.print (temp);
Serial.print ("°");

float humi = dht.readHumidity();
Serial.print ("                 Humidity : ");
Serial.print(humi);
Serial.print ("%");
Serial.println ();
delay (1000);
}
