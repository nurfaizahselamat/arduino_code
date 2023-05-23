#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <DHT.h>

const char* ssid = "iotclass@unifi";
const char* password = "classiot123";
const char* mqtt_server = "broker.hivemq.com";
const char* topicTemp = "temperature/nurfaizah";
const char* topicHumi = "humidity/nurfaizah";
const char* topicServo = "servo/nurfaizah";

int servoPosition = 0;
Servo weeekly;

DHT dht(25, DHT11);
char temp[10];
char humi[10];

WiFiClient espClient;
PubSubClient client(espClient);

TaskHandle_t Task1_handle;
TaskHandle_t Task2_handle;

void task1(void* parameters) {
  for (;;) {
    float t = dht.readTemperature();
    dtostrf(t, 4, 2, temp);
    float h = dht.readHumidity();
    dtostrf(h, 4, 2, humi);

    Serial.printf(("Suhu: %.2fC \t Kelembapan: %.2f%% \n"), t, h);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    client.publish(topicTemp, temp);
    client.publish(topicHumi, humi);
  }
}

void task2(void* parameters) {
  for (;;) {
    weeekly.write(servoPosition);
    Serial.println(servoPosition);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

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
  dht.begin();

  xTaskCreatePinnedToCore(task1, "DHT11", 5000, NULL, 1, &Task1_handle, 0);
  xTaskCreatePinnedToCore(task2, "Servo", 5000, NULL, 2, &Task2_handle, 1);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(50);
}