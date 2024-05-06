#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const int ledPin = 16; 

//Handle received and sent message
String message = ""; 
char incomingChar;

void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(115200);
  SerialBT.begin("ESP32_x");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop(){
  //Read received message
  if(SerialBT.available()){
    char incomingChar = SerialBT.read();
    if(incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);
  }
  //Check received message and control output accordingly
  //kalau  nak control kipas/pam/relay sila ubah coding di bawah
  if(message =="led_on"){
    digitalWrite(ledPin, HIGH);
  }else if(message =="led_off"){
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}



