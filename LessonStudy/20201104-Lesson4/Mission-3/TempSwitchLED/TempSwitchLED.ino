#include <dht11.h>//dht11温湿度传感器库

dht11 DHT11;//定义变量
// 设置 DHT 引脚 为 Pin 7，替代原来7号口的开关
#define DHT11PIN 7

int RedLed=8;
int GreenLed=9;

int Temp=0;//声明变量，用来存储读取到的温度值
int Hum=0; //声明变量，用来存储读取到的湿度值

void setup()
{
  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  Serial.begin(9600);// 串口波特率
}

void loop()
 {
    int chk = DHT11.read(DHT11PIN);                 //将读取到的值赋给chk
    int Temp=(float)DHT11.temperature;               //将温度值赋值给Temp
    int Hum=(float)DHT11.humidity;                   //将湿度值赋给Hum

    Serial.print("Tempeature:");                        
    Serial.print(Temp); //将温度输出到串口                                    
    Serial.println("C°");  
    
    Serial.print("Humidity:");
    Serial.print(Hum);//将湿度输出到串口
    Serial.println("%");  
                             
	  if(Hum>85)
    {
      digitalWrite(RedLed,HIGH);
      digitalWrite(GreenLed,LOW);
    }
   else
   {
      digitalWrite(RedLed,LOW);
      digitalWrite(GreenLed,HIGH);
   }
   delay(1000);
 }
