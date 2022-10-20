//Diffuse sensor1 control LED
const int diffuseSensor1 = 13;
int dataSensor1 = 0;
const int blueLED = 19;

//Diffuse sensor 2 control relay1
const int diffuseSensor2 = 16;
int dataSensor2 = 0;
const int relayIN1 = 15;

#include <ESP32Servo.h>
Servo armRobot;

TaskHandle_t Task1;
TaskHandle_t Task2;

void loop2(void* parameter) {
  for (;;) {
    dataSensor1 = digitalRead(diffuseSensor1);
    if (dataSensor1 == LOW) {
      digitalWrite(blueLED, HIGH);
    } else {
      digitalWrite(blueLED, LOW);
    }
  }
}

void loop3(void* parameter) {
  for (;;) {
    dataSensor2 = digitalRead(diffuseSensor2);
    if (dataSensor2 == LOW) {
      digitalWrite(relayIN1, LOW);
    } else {
      digitalWrite(relayIN1, HIGH);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(blueLED, OUTPUT);
  pinMode(relayIN1, OUTPUT);
  armRobot.attach(5, 500, 2500);

  xTaskCreatePinnedToCore(loop2, "Escalator", 1000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(loop3, "Guest Room", 1000, NULL, 1, &Task2, 1);
}

void loop() {
  armRobot.write(180);
  Serial.println("                                          Gate Open");
  delay(1000);
  armRobot.write(0);
  Serial.println("                                          Gate Close");
  delay(1000);
}