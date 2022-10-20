#include <ESP32Servo.h>
#include <DHT.h>
DHT dht(25, DHT11);
Servo weeekly;

const int diffuseSensor = 13;
int sensorState = 0;

TaskHandle_t inspectDHT;

void task1(void* parameters) {
  for (;;) {
    delay(1000);
    float humi = dht.readHumidity();
    float temp = dht.readTemperature();
    if (isnan(humi) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    Serial.printf(("                     Temperature: %.2f°C \t Humidity: %.2f%% \n"), temp, humi);
  }
}

void setup() {
  weeekly.attach(5, 500, 2500);
  pinMode(diffuseSensor, INPUT);
  Serial.begin(115200);
  dht.begin();

  xTaskCreatePinnedToCore(task1, "dht11", 5000, NULL, 1, &inspectDHT, 0);
}

void loop() {
  sensorState = digitalRead(diffuseSensor);
  if (sensorState == LOW) {
    weeekly.write(0);
    Serial.println("Gate Open");
    delay(1000);
  } else {
    weeekly.write(180);
    Serial.println("Gate Close");
  }
  delay(100);
}