const int diffuseSensor = 13;   
int dataSensor = 0;             

void setup() {
  pinMode(diffuseSensor, INPUT);
  Serial.begin(115200);   
}

void loop() {
  dataSensor = digitalRead(diffuseSensor);  
  Serial.println(dataSensor);
  delay(1000);
}