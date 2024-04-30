const int passiveBuzzer = 16;
const int chan = 0;

void setup() {
  ledcAttachPin(passiveBuzzer,chan);
}

void loop() {
  ledcWriteNote(chan, NOTE_C, 4);
  delay(500);
  ledcWrite(chan,0);
  delay(500);
}