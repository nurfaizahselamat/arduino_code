#include <ESP32Servo.h>
Servo faizah; 

void setup() {
  faizah.attach(5,500,2500);  
}

void loop() {
  faizah.write(0);    
  delay(1000);           
  faizah.write(180);
  delay(1000);
}