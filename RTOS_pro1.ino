const int waterSensor = 32;
int dataWater = 0;
const int relayIN = 5;

#include <ESP32Servo.h>
Servo gerbang;

TaskHandle_t airEmpangan;

void loop2(void* parameters) {
  for (;;) {
    dataWater = analogRead(waterSensor);
    Serial.println(dataWater);
    delay(500);

    if (dataWater >= 700 && dataWater < 2000) {
      digitalWrite(relayIN, LOW);
      Serial.println("                       MOTOR PAM MENYALA");
    } else {
      digitalWrite(relayIN, HIGH);
      Serial.println("                       MOTOR PAM PADAM");
    }
  }
}

void setup() {
  pinMode(relayIN, OUTPUT);

  gerbang.attach(14, 250, 2500);
  Serial.begin(115200);

  xTaskCreatePinnedToCore(loop2, "EMPANGAN BAKUN", 1000, NULL, 1, &airEmpangan, 0);
}

void loop() {
  gerbang.write(90);
  delay(1000);
  gerbang.write(0);
  delay(1000);
}
