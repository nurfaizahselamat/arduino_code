const int blueLED = 19;
const int greenLED = 17;

#include <ESP32Servo.h>
Servo armRobot;

TaskHandle_t Task1;
TaskHandle_t Task2;

void loop2(void* parameter) {
  for (;;) {
    digitalWrite(blueLED, HIGH);
    Serial.println("                      LED BLUE ON");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    digitalWrite(blueLED, LOW);
    Serial.println("                      LED BLUE OFF");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
void loop3(void* parameter) {
  for (;;) {
    digitalWrite(greenLED, HIGH);
    Serial.println("LED GREEN ON");
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(greenLED, LOW);
    Serial.println("LED GREEN OFF");
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  armRobot.attach(5, 500, 2500);

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