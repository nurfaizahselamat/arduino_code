const int waterSensor = 32;
int dataWater = 0;
const int ledBlue = 19;
const int ledRed = 18;

void setup() {
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  dataWater = analogRead(waterSensor);
  Serial.println(dataWater);
  delay(1000);

  if (dataWater >= 1000 && dataWater < 2000) {
    digitalWrite(ledBlue, HIGH);
  } else {
    digitalWrite(ledBlue, LOW);
  }
  if (dataWater > 2000) {
    digitalWrite(ledRed, HIGH);
  } else {
    digitalWrite(ledRed, LOW);
  }
}
