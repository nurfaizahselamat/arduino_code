const int diffuseSensor = 13;
int dataSensor = 0;
#define ledBlue 19
#include <ESP32Servo.h>
Servo faizah;

void setup() {
  pinMode(diffuseSensor, INPUT);
  Serial.begin(115200);
  
  pinMode(ledBlue, OUTPUT);
  faizah.attach(5, 500, 2500);
}

void loop() {
  dataSensor = digitalRead(diffuseSensor);

  if (dataSensor == LOW) {
    digitalWrite(ledBlue, HIGH);
    Serial.println("LED ON");

    faizah.write(90);
    Serial.println("GATE OPEN");
    Serial.println(" ");
    delay(1000);
  } else {
    digitalWrite(ledBlue, LOW);
    Serial.println("LED OFF");

    faizah.write(0);
    Serial.println("GATE CLOSE");
    Serial.println(" ");
    delay(1000);
  }
}