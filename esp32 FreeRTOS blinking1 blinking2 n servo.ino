#include <DHT.h>
DHT dht(25, DHT11);

const int diffuseSensor = 13;
int sensorState = 0;
#include <ESP32Servo.h>
Servo armRobot;

TaskHandle_t Task1;

void loop2(void* parameter) {
  for (;;) {
    delay(1000);
    float humi = dht.readHumidity();
    float temp = dht.readTemperature();
    if (isnan(humi) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    Serial.printf(("                                   Temperature: %.2f°C \t Humidity: %.2f%% \n"), temp, humi);
  }
}

void setup() {
  armRobot.attach(25, 500, 2500);
  pinMode(diffuseSensor, INPUT);
  Serial.begin(115200);
  dht.begin();

  xTaskCreatePinnedToCore(loop2, "dht11", 5000, NULL, 1, &Task1, 0);
}

void loop() {
  sensorState = digitalRead(diffuseSensor);
  if (sensorState == LOW) {
    armRobot.write(0);
    Serial.println("Gate Open");
    delay(1000);
  } else {
    armRobot.write(180);
    Serial.println("Gate Close");
  }
  delay(50);
}