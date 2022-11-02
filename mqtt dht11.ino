#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define ssid "yourSSID"   
#define password "yourPASSWORD"
#define mqtt_server "broker.hivemq.com"

DHT dht(25, DHT11);
char temp[10];
char humi[10];

WiFiClient espClient;
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

void reconnect() {
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
  connectToWiFi();
  client.setServer(mqtt_server, 1883);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(1000);
  float h = dht.readHumidity();
  dtostrf(h, 4, 2, humi);
  float t = dht.readTemperature();
  dtostrf(t, 4, 2, temp);
    Serial.print("Suhu = ");
    Serial.print(temp);
    Serial.print("°C");
    client.publish("nurfaizah/temp", temp);
    Serial.print(" || ");
    Serial.print("Kelembapan = ");
    Serial.print(humi);
    Serial.println("%");
    client.publish("nurfaizah/humi", humi);
}
