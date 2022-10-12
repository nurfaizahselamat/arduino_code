const int ledRed = 18;
const int ledBlue = 19;

TaskHandle_t ledMerah;   
TaskHandle_t ledBiru;

void task1(void* parameters) {
  for (;;) {  
    Serial.print("Core Number:");
    Serial.println(xPortGetCoreID());
    
    digitalWrite(ledRed, HIGH);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    digitalWrite(ledRed, LOW);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
void task2(void* parameters) {
  for (;;) {
        Serial.print("            Core Number:");
    Serial.println(xPortGetCoreID());

    digitalWrite(ledBlue, HIGH);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    digitalWrite(ledBlue, LOW);
    vTaskDelay(200 / portTICK_PERIOD_MS);  //200milisec
  }
}

void setup() {
  pinMode(ledRed, OUTPUT); 
  pinMode(ledBlue, OUTPUT);  

  xTaskCreatePinnedToCore(task1, "LED MERAH", 1000, NULL, 1, &ledMerah, 0);  
  xTaskCreatePinnedToCore(task2, "LED BIRU", 1000, NULL, 1, &ledBiru, 1);

  Serial.begin (115200);
}

void loop() {
  // put your main code here, to run repeatedly:
}