#include <WiFi.h>
#include <PubSubClient.h>

#define ssid "iotclass@unifi"
#define password "classiot123"
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

const int diffuseSensor = 13;
int dataSensor = 0;

void connectToWiFi() {
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to WiFi");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32nfs2022")) {
      Serial.println("connected");
    } else {
      Serial.println(" trying again");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  client.setServer(mqtt_server, 1883);
  pinMode(diffuseSensor, INPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(50);
  dataSensor = digitalRead(diffuseSensor);

  if (dataSensor == LOW) {
    Serial.println("Object Detected");
    //publish sensor data to MQTT broker
    client.publish("nur/faizah/sensor", "Object Detected");
  } else {
    Serial.println("Object Not Detected");
    //publish sensor data to MQTT broker
    client.publish("nur/faizah/sensor", "Object Not Detected");
  }
}