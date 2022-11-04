#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

const char* ssid = "iotclass@unifi";
const char* password = "classiot123";
const char* mqtt_server = "broker.hivemq.com";
const char* topicServo = "servo/nurfaizah";

int servoPosition = 0;
Servo weeekly;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void reconnect() {

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32nurfaizah")) {
      Serial.println("connected");
      client.subscribe(topicServo);
    } else {
      Serial.println(" trying again");
      delay(1000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String messageTemp;
  // decode payload message
  for (int i = 0; i < length; i++) {
    messageTemp += ((char)payload[i]);
  }
  if (strcmp(topic, topicServo) == 0) {
    servoPosition = messageTemp.toInt();
  }
  delay(15);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  reconnect();
  client.setCallback(callback);
  weeekly.attach(5, 500, 2500);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(50);

  weeekly.write(servoPosition);
  Serial.println(servoPosition);
  delay(1000);
}