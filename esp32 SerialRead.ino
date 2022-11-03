const int ledRed = 18;
const int ledBlue = 19;

void setup() {
  Serial.begin(115200);
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int incomingByte = Serial.parseInt();
    if (incomingByte == 4) {
      digitalWrite(ledRed, HIGH);
    }
    if (incomingByte == 1) {
      digitalWrite(ledRed, LOW);
    }
    if (incomingByte == 2) {
      digitalWrite(ledBlue, HIGH);
    }
    if (incomingByte == 3) {
      digitalWrite(ledBlue, LOW);
    }
  }
}