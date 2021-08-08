int RLed=2;
int YLed=3;
int GLed=4;
int RKey=5;
int YKey=6;
int GKey=7;
int resetKey=8;

void setup() {
  pinMode(RLed,OUTPUT);
  pinMode(YLed,OUTPUT);
  pinMode(GLed,OUTPUT);
  pinMode(RKey,INPUT_PULLUP);
  pinMode(YKey,INPUT_PULLUP);
  pinMode(GKey,INPUT_PULLUP);
  pinMode(resetKey,INPUT_PULLUP);
}

void loop() {
  if(digitalRead(RKey)==LOW)
  RED();
  if(digitalRead(YKey)==LOW)
  YELLOW();
  if(digitalRead(GKey)==LOW)
  GREEN();
}

//以下为函数定义
void RED()
{
  while(digitalRead(resetKey)==1)//判断复位键是否按下
  {
  digitalWrite(RLed,HIGH);
  digitalWrite(YLed,LOW);
  digitalWrite(GLed,LOW);
  }
  CLEAR();
}
void YELLOW()
{
  while(digitalRead(resetKey)==1)
  {
  digitalWrite(RLed,LOW);
  digitalWrite(YLed,HIGH);
  digitalWrite(GLed,LOW);
  }
  CLEAR();
}
void GREEN()
{
  while(digitalRead(resetKey)==1)
  {
  digitalWrite(RLed,LOW);
  digitalWrite(YLed,LOW);
  digitalWrite(GLed,HIGH);
  }
  CLEAR();
}
void CLEAR()//复位键按下后熄灭所有小灯
{
  digitalWrite(RLed,LOW);
  digitalWrite(YLed,LOW);
  digitalWrite(GLed,LOW);
}
