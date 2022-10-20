const int diffuseSensor = 13;
int dataSensor = 0;
const int ledBlue = 19;
const int ledRed = 18;

void setup() {
  pinMode(diffuseSensor, INPUT);
  Serial.begin(115200);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

void loop() {
  dataSensor = digitalRead(diffuseSensor);

  if (dataSensor == LOW) {
    digitalWrite(ledBlue, HIGH);
    Serial.println("                LED Blue Menyala");
  } 
  else {
    digitalWrite(ledBlue, LOW);
    Serial.println("LED Padam");
  }
  if (dataSensor == LOW) {
    digitalWrite(ledRed, HIGH);
    Serial.println("                LED Red Menyala");
  } 
  else {
    digitalWrite(ledRed, LOW);
    Serial.println("LED Padam");
  }
}
