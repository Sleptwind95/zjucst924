int Led1=9;
int Key=11;
int ledON=0;
void setup()
{
  pinMode(Led1,OUTPUT);
  pinMode(Key,INPUT);
}

void loop()
{
  if(digitalRead(Key)==LOW)//不断监测按键状态，按下时执行"LedSwitch"函数
  LedSwitch();
  delay(100);//可以尝试理解为什么要有这个delay
}

void LedSwitch()
{
  if(ledON==0)
  {
    digitalWrite(Led1,HIGH);
    ledON=1;//翻转LED灯状态
  }
  else
  {
    digitalWrite(Led1,LOW);
    ledON=0;//翻转LED灯状态
  }
}
