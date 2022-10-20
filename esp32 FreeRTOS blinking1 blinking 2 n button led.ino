const int pushButton = 23;
int buttonState = 0;
const int redLED = 18;
const int blueLED = 19;
const int greenLED = 17;

TaskHandle_t Task1;
TaskHandle_t Task2;

void loop2(void* parameter) {
  for (;;) {
    digitalWrite(blueLED, HIGH);
    Serial.println("                      LED BLUE ON");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    digitalWrite(blueLED, LOW);
    Serial.println("                      LED BLUE OFF");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}
void loop3(void* parameter) {
  for (;;) {
    digitalWrite(greenLED, HIGH);
    Serial.println("LED GREEN ON");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(greenLED, LOW);
    Serial.println("LED GREEN OFF");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pushButton, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  xTaskCreatePinnedToCore(loop2, "Blinking 1", 1000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(loop3, "Blinking 2", 1000, NULL, 1, &Task2, 1);
}

void loop() {
  buttonState = digitalRead(pushButton);
  if (buttonState == HIGH) {
    digitalWrite(redLED, HIGH);
    Serial.print("                                               Core#");
    Serial.print(xPortGetCoreID());
    Serial.println("  Button Pressed");
    delay(50);
  } else {
    digitalWrite(redLED, LOW);
  }
}