int count1 = 0;
int count2 = 0;

void task1(void* parameters) {
  for (;;) {
    Serial.print("Task 1 Count: ");
    Serial.println(count1++);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void task2(void* parameters) {
  for (;;) {
    Serial.print("Task 2 Count: ");
    Serial.println(count2 += 3);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreate(task1, "Task 1", 1000, NULL, 1, NULL);
  xTaskCreate(task2, "Task 2", 1000, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}