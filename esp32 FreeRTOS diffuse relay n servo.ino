#include <ESP32Servo.h>
Servo armRobot;

const int diffuseSensor1 = 13;
int dataSensor1 = 0;
const int blueLED = 19;

const int diffuseSensor2 = 16;
int dataSensor2 = 0;
const int relayIN1 = 15;

TaskHandle_t pets;
TaskHandle_t people;

void task1(void* parameters) {
  for (;;) {
    dataSensor1 = digitalRead(diffuseSensor1);

    if (dataSensor1 == LOW) {
      digitalWrite(blueLED, HIGH);
      Serial.println("  LED ON");
    } else {
      digitalWrite(blueLED, LOW);
      Serial.println("  LED OFF");
    }
    vTaskDelay(100);
  }
}

void task2(void* parameters) {
  for (;;) {
    dataSensor2 = digitalRead(diffuseSensor2);

    if (dataSensor2 == LOW) {
      digitalWrite(relayIN1, LOW);
      Serial.println("                RELAY ON");
    } else {
      digitalWrite(relayIN1, HIGH);
      Serial.println("                RELAY OFF");
    }
    vTaskDelay(100);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(diffuseSensor1, INPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(diffuseSensor2, INPUT);
  pinMode(relayIN1, OUTPUT);

  armRobot.attach(5, 500, 2500);

  xTaskCreatePinnedToCore(task1, "Cats Detected", 5000, NULL, 1, &pets, 0);
  xTaskCreatePinnedToCore(task2, "Peoples Detected", 5000, NULL, 2, &people, 1);
}

void loop() {
  armRobot.write(90);
  Serial.println("                                  Gate Open");
  delay(1000);
  armRobot.write(0);
  Serial.println("                                  Gate Close");
  delay(1000);
}