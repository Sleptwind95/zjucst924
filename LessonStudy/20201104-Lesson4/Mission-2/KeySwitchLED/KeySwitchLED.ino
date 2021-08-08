int RedLed=8;
int GreenLed=9;
int Key=7;
int val=0; //声明变量，用来存储按钮返回值HIGH或者LOW；
int val_old=1;//声明变量，存储上一次按钮返回值；比对val和val_old的值，来判断按钮是按下还是抬起
			  //val==LOW && val_old==HIGH 按下状态；val==HIGH && val_old==LOW 抬起状态
			  //注：if((A)&&(B)) 表示只有在括号内的A和B两个条件都为满足的情况下，才会执行后面{}里的语句
int state=0;//0=关灯动作,1=开灯动作,一个巧妙的设计，起到中转的作用；
void setup()
{
  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(Key,INPUT);
}

void loop()
 {
  val=digitalRead(Key);//读取按键的值；
	  if((val==LOW) && (val_old==HIGH))//比较前一次和现在的按钮返回的值，
	                                   //只有在按下按钮这个状态下，才改变state的值
    {
    state=1-state;//巧妙的状态切换设计
    }
    if((val==HIGH && val_old==LOW)) //去抖的作用，一般10-15ms；
    {
      delay(10);
    }
  val_old=val;//把现在按钮返回的值赋予val_old；
  if(state==1)//控制灯的开关；
    {
      digitalWrite(RedLed,HIGH);
      digitalWrite(GreenLed,LOW);
    }
   else
   {
      digitalWrite(RedLed,LOW);
      digitalWrite(GreenLed,HIGH);
   }
 }
