const int waterSensor = 32;
int dataWater = 0;

void setup() { //analog tak perlu setup pinMODE
Serial.begin(115200);
}

void loop() {
dataWater = analogRead(waterSensor);
Serial.println(dataWater);
delay(1000);
}
