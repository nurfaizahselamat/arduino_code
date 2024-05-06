#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const int ledPin = 23; //1

//Handle received and sent message
String message = ""; //2
char incomingChar;

void setup() {
  pinMode(ledPin, OUTPUT); //3
  Serial.begin(115200);
  SerialBT.begin("ESP32_nfs");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
if (Serial.available()){
  SerialBT.write(Serial.read());
}
if (SerialBT.available()){
  Serial.write(SerialBT.read());
}
delay(20);
}
