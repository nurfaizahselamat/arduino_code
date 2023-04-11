const int diffuseSensor = 13;
int dataSensor1 = 0;
const int ledBlue = 19;

#include <ESP32Servo.h>
Servo faizah;

TaskHandle_t lampuDapur;

void loop2(void* parameters){
  for (;;){
    dataSensor1 = digitalRead (diffuseSensor);
    if (dataSensor1 == LOW){
      digitalWrite(ledBlue, HIGH);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      digitalWrite(ledBlue, LOW);
      vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    {
      Serial.print("Core Number: ");
      Serial.println(xPortGetCoreID());
    }
  }
}

void setup() {
pinMode(diffuseSensor, INPUT);
pinMode(ledBlue, OUTPUT);
faizah.attach(5, 500, 2500);
Serial.begin(115200);

xTaskCreatePinnedToCore(loop2, "LAMPU DI DAPUR", 1000, NULL, 1, &lampuDapur, 0);
}

void loop() {
faizah.write(90);
delay(1000);
faizah.write(0);
delay(1000);

Serial.print("Core Number: ");
Serial.println(xPortGetCoreID());

}
