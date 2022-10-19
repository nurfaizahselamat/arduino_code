const int pushButton = 23;
int buttonState = 0;
const int blueLED = 19;
int redLED = 18;

TaskHandle_t Task1;

void loop2(void* parameter) {
  for (;;) {
    // write you code for 2nd loop here to run endlessly
    buttonState = digitalRead(pushButton);
    if (buttonState == 1) {
      digitalWrite(redLED, HIGH);
      Serial.print("                     Core#");
      Serial.print(xPortGetCoreID());
      Serial.println("  ButtonPressed");
      delay(50);
    } else {
      digitalWrite(redLED, LOW);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pushButton, INPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Initialize your task (2nd loop)
  xTaskCreatePinnedToCore(
    loop2,          // name of the task function
    "buttonCheck",  // name of the task
    1000,           // memory assigned for the task
    NULL,           // parameter to pass if any
    1,              // priority of task, starting from 0(Highestpriority) *IMPORTANT*( if set to 1 and there is no activity in your 2nd loop, it will reset the esp32)
    &Task1,         // Reference name of taskHandle variable
    0);             // choose core (0 or 1)
}

void loop() {
  digitalWrite(blueLED, HIGH);
  Serial.println("             LED ON");
  delay(1000);
  digitalWrite(blueLED, LOW);
  Serial.println("  LED OFF");
  delay(1000);
}