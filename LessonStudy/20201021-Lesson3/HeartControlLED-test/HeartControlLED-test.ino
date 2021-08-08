#include <LedControl.h>
 
int HeartKey=12;//定义手动开关为12号口
int buzzer=5;//设置控制蜂鸣器的数字口对应板子上5口
int CLK = 4;//定义arduino的数字口4
int CS = 3;//定义arduino的数字口3
int DIN = 2; ////定义arduino的数字口2

int val=0; //声明变量，用来存储按钮返回值HIGH或者LOW；
int val_old=1;//声明变量，存储上一次按钮返回值；比对val和val_old的值，来判断按钮是按下还是抬起
        //val==LOW && val_old==HIGH 按下状态；val==HIGH && val_old==LOW 抬起状态
int state=0;//0=关灯动作,1=开灯动作

byte HeartBig[8]= {0x66,0xFF,0xFF,0xFF,0xFF,0x7E,0x3C,0x18};  //大♥图案
byte HeartSmall[8]= {0x00,0x24,0x7E,0x7E,0x3C,0x18,0x18,0x00,};  //小♥图案
 
LedControl lc=LedControl(DIN,CLK,CS,4);
 
void setup(){
 pinMode(HeartKey,INPUT);//设置8号口
 pinMode(buzzer,OUTPUT);//设置对应的输出模式
 lc.shutdown(0,false);       //启动时，MAX72XX处于省电模式
 lc.setIntensity(0,8);       //将亮度设置为最大值
 lc.clearDisplay(0);         //清除显示
}
 
void loop()
{ 
    val=digitalRead(HeartKey);//读取按键的值；
   if((val==LOW) && (val_old==HIGH))//比较前一次和现在的按钮返回的值，
                                     //只有在按下按钮这个状态下，才改变state的值
    {
    state=1-state;//状态切换
    }
    if((val==HIGH && val_old==LOW)) //去抖的作用，一般10-15ms；
    {
      delay(10);
    }
  val_old=val;//把现在按钮返回的值赋予val_old；
  if(state==1)//控制灯的开关；
    {
    printByte(HeartBig);//显示大♥
    delay(1000);//延时1秒
     digitalWrite(buzzer,HIGH);//高电平打开蜂鸣器发声
    printByte(HeartSmall);//显示小♥
    delay(1000);//延时1秒
    digitalWrite(buzzer,LOW);//低电平关闭蜂鸣器不发声音
    }
       else
   {
     lc.clearDisplay(0);
   }
}


void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
 
