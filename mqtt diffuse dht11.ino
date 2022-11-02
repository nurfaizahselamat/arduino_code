#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define DHT11PIN 25

const int sensorPin = 13;
int sensorState = 0;
DHT dht(DHT11PIN, DHT11);

char str_hum_data[10];
char str_temp_data[10];

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;

void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(5000);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  
} //end callback

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("nur/faizah");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} //end reconnect()

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(sensorPin,INPUT);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  // hantar data setiap 1 saat
  if (now - lastMsg > 1000) {
     lastMsg = now;
     sensorState=digitalRead(sensorPin);
     if(sensorState == LOW)
     {
       Serial.println("Object Detected");
       //publish sensor data to MQTT broker
      client.publish("nur/faizah/sensor", "Object Detected");
       }
     else
     {
       Serial.println("Object Not Detected");
       //publish sensor data to MQTT broker
      client.publish("nur/faizah/sensor", "Object Not Detected");
     }
      float hum_data = dht.readHumidity();
      dtostrf(hum_data, 4, 2, str_hum_data);
      float temp_data = dht.readTemperature();
      dtostrf(temp_data, 4, 2, str_temp_data);
      Serial.print("Suhu = ");
      Serial.print(str_temp_data);
      Serial.print("°C");
      client.publish("nur/faizah/temp", str_temp_data);
      Serial.print(" || ");
      Serial.print("Kelembapan = ");
      Serial.print(str_hum_data);
      Serial.println("%");
      client.publish("nur/faizah/humi", str_hum_data);
    }
     
}