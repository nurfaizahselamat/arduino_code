const int diffuseSensor1 = 4;
const int diffuseSensor2 = 13;
int dataSensor1 = 0;
int dataSensor2 = 0;
const int relayIN1 = 15; 

void setup() {
  pinMode(diffuseSensor1, INPUT);  
  pinMode(diffuseSensor2, INPUT);
  pinMode(relayIN1, OUTPUT);           // Set the relay pin as an output
  digitalWrite(relayIN1, HIGH);        // Set the relay to HIGH (OFF) initially
  Serial.begin(115200);
}

void loop() {
  dataSensor1 = digitalRead(diffuseSensor1);
  dataSensor2 = digitalRead(diffuseSensor2);
  Serial.println(dataSensor1);

  if (dataSensor1 == LOW) {         //Object detected data 0
    digitalWrite(relayIN1, LOW);    //Relay turn ON
  } else if (dataSensor2 == LOW) {
    digitalWrite(relayIN1, HIGH);
  } else {
    Serial.println("Check your sensors");
  }
}
