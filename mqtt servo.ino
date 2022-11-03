#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
Servo weeekly;

// WiFi, MQTT parameters
const char* ssid = "iotclass@unifi";                // WiFi SSID
const char* password = "classiot123";        // WiFi Password
const char* mqtt_server = "broker.hivemq.com";  // IP Broker MQTT
const char* topic_weeekly = "servo/weeekly/nurfaizah";  // Topic MQTT for weeekly servo
 
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
 String string;
 // display incoming Topic
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 // decode payload message
 for (int i = 0; i < length; i++) {
 string+=((char)payload[i]); 
 }
 // display incoming message
 Serial.print(string);
 Serial.print(" toInt ");
 // convert position as an Integer
 int pos = string.toInt(); 
 Serial.println(pos);

 // Determines which servo should be moved
 if ( strcmp(topic, topic_weeekly) == 0 ) {
 Serial.print("Move weeekly to ");
 Serial.println(pos);
 weeekly.write(pos); 
 }
 delay(15); 
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32nurfaizah")) {
      Serial.println("connected");
      client.subscribe(topic_weeekly); 
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  weeekly.attach(5,500,2500);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {   
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(100);
}