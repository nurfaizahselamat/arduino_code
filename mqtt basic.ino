#include <WiFi.h>
#include <PubSubClient.h>

#define ssid "iotclass@unifi"         
#define password "classiot123"
#define mqtt_server "broker.hivemq.com"

WiFiClient espClient;                     //kt bagi laluan supaya mqtt lalu wifi
PubSubClient client(espClient);

void connectToWiFi(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to WiFi");
}

void reconnect() {                                 //untuk connect ngan mqtt
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32nurfaizah")) {
      Serial.println("connected");
    } else {
      Serial.println(" trying again");
      delay(1000);
    }
  }
}

void setup() {       
  Serial.begin(115200);            
  connectToWiFi();                       //untuk connect ngan wifi
  client.setServer(mqtt_server, 1883);  //untuk sambung ke mqtt
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 
}