const int blueLED = 19;
const int pushButton = 23;
int buttonState = 0;
const int redLED = 18;

TaskHandle_t Task1;

void loop2(void* parameters) {
  for (;;) {
    digitalWrite(blueLED, HIGH);
    Serial.println("            LED ON");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    digitalWrite(blueLED, LOW);
    Serial.println("LED OFF");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(blueLED, OUTPUT);
  pinMode(pushButton, INPUT);
  pinMode(redLED, OUTPUT);

  xTaskCreatePinnedToCore(loop2, "Blinking LED", 1000, NULL, 1, &Task1, 0);
}

void loop() {
  buttonState = digitalRead(pushButton);
  if (buttonState == HIGH) {
    digitalWrite(redLED, HIGH);
    Serial.print("                      Core#");
    Serial.print(xPortGetCoreID());
    Serial.println("  Button Pressed");
    delay(50);
  } else {
    digitalWrite(redLED, LOW);
  }
}