const int buttonStart = 23;
int buttonState = 0;
const int relayIN1 = 16;

void setup() {
  pinMode (buttonStart, INPUT);
  pinMode (relayIN1, OUTPUT);
  Serial.begin (115200);
}

void loop() {
  buttonState = digitalRead (buttonStart);
  //Serial.println (buttonState);

  if (buttonState == LOW) {
    digitalWrite (relayIN1, HIGH);
    Serial.println ("                           RELAY OFF");
    delay (250);
  } else {
    digitalWrite (relayIN1, LOW);
    Serial.println ("RELAY ON");
    delay (250);
  }
}
