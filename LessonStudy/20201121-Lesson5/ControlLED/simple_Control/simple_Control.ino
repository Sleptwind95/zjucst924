int led = 5;     // LED引脚
int button = 16; // 按键连接的引脚
int temp = 0;    // 用于读取按键状态的临时变量

void setup() {
  pinMode(led, OUTPUT);   // LED设置为输入
  pinMode(button, INPUT); // 按键设置为输出
}

void loop() {
  temp = digitalRead(button);
  if (temp == HIGH) {
    digitalWrite(led, HIGH);
    Serial.println("LED Turned ON");
    delay(1000);
  }
  else {
    digitalWrite(led, LOW);
    Serial.println("LED Turned OFF");
    delay(1000);
  }
}
