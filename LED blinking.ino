const int ledBlue = 4;
const int ledBuild = 2;

void setup() {
pinMode (ledBlue, OUTPUT);
pinMode (ledBuild, OUTPUT);
}

void loop() { 
digitalWrite (ledBlue, HIGH);
delay (500);
digitalWrite (ledBlue, LOW);
delay (500);

digitalWrite (ledBuild, HIGH);
delay (500);
digitalWrite (ledBuild, LOW);
delay (500);
}
