const int sensorPin = 13 ;   
const int ledPin = 19;
int sensorState = 0;    
int lastSensorState = 0;  

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  sensorState = digitalRead(sensorPin);

  if (sensorState == LOW && lastSensorState == 0) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Object detected!!!");
    lastSensorState = 1;  
  }
  if (sensorState == HIGH && lastSensorState == 1) {
    digitalWrite(ledPin, LOW);
    Serial.println("                    no Object...going to sleep");
    lastSensorState = 0;  
  }
  delay(50);
}