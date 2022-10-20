#include <ESP32Servo.h>
Servo armRobot;

const int blueLED = 19;
const int redLED = 18;

TaskHandle_t Task1;
TaskHandle_t Task2;

void loop2(void* parameters) {
  for (;;) {
    digitalWrite(blueLED, HIGH);
    Serial.println("                      LED BLUE ON");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    digitalWrite(blueLED, LOW);
    Serial.println("                      LED BLUE OFF");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
void loop3(void* parameters) {
  for (;;) {
    digitalWrite(redLED, HIGH);
    Serial.println("LED GREEN ON");
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(redLED, LOW);
    Serial.println("LED GREEN OFF");
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  armRobot.attach(5, 500, 2500);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  xTaskCreatePinnedToCore(loop2, "Blinking 1", 1000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(loop3, "Blinking 2", 1000, NULL, 1, &Task2, 1);
}

void loop() {
    armRobot.write(90);
    Serial.println("                                          Gate Open");
    delay(1000);
    armRobot.write(0);
    Serial.println("                                          Gate Close");
    delay(1000);
}