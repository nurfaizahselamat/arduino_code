#include <WiFi.h>

#define ssid "iotclass@unifi"
#define password "classiot123"

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to WiFi");
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();

  void loop() {}