#include <LedControl.h>
 
int Heartmonitor=0;//定义手动开关为A0号口
int buzzer=5;//设置控制蜂鸣器的数字口对应板子上5口
int CLK = 4;//定义arduino的数字口4
int CS = 3;//定义arduino的数字口3
int DIN = 2; ////定义arduino的数字口2

int HeartBeat=0; //声明变量，用来存储心跳监测数据；
int HeartBeat_Old=0; //声明变量，用来对比心跳监测数据；
int state=0;//0=关灯动作,1=开灯动作

byte HeartBig[8]= {0x66,0xFF,0xFF,0xFF,0xFF,0x7E,0x3C,0x18};  //大♥图案
byte HeartSmall[8]= {0x00,0x24,0x7E,0x7E,0x3C,0x18,0x18,0x00,};  //小♥图案
 
LedControl lc=LedControl(DIN,CLK,CS,4);
 
void setup(){
 pinMode(Heartmonitor,INPUT);//设置A0号口
 pinMode(buzzer,OUTPUT);//设置对应的输出模式
 Serial.begin(9600);// 串口波特率
 lc.shutdown(0,false);       //启动时，MAX72XX处于省电模式
 lc.setIntensity(0,8);       //将亮度设置为最大值
 lc.clearDisplay(0);         //清除显示
}
 
void loop()
{ 
    HeartBeat=analogRead(Heartmonitor);//读取按键的值；
    Serial.println(HeartBeat, DEC);//输出到串口
    if((HeartBeat>995) && (HeartBeat_Old<990))//比较传感器返回的值，
                                     //只有在心率确实变化的状态下，才改变state的值
    {
    state=1-state;//状态切换
    }
    HeartBeat_Old=HeartBeat;
  if(state==1)//控制灯的开关；
    {
    printByte(HeartBig);//显示大♥
    delay(100);//延时
    digitalWrite(buzzer,HIGH);//高电平打开蜂鸣器发声
    }
       else
   {
    printByte(HeartSmall);//显示小♥
    delay(100);//延时
    digitalWrite(buzzer,LOW);//低电平关闭蜂鸣器不发声音
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
 
