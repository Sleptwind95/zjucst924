#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "aliyun_mqtt.h"
#include "DHT.h"

int RedLed=4;//定义绿灯为4号口
int GreenLed=5;//定义红灯为5号口
float Temp,Hum;

/* 定义DHT11引脚和传感器型号 */
#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

/* 连接您的WIFI SSID和密码 */
#define WIFI_SSID        "CHENG_Wlan"//替换自己的WIFI
#define WIFI_PASSWD      "1472583690"//替换自己的WIFI
/* 设备的三元组和其余信息*/
#define PRODUCT_KEY      "a10fZzprmx5" //替换自己的PRODUCT_KEY
#define DEVICE_NAME      "1020_home" //替换自己的DEVICE_NAME
#define DEVICE_SECRET    "21a564b647cc0d39529c9a64f0f08970"//替换自己的DEVICE_SECRET
#define DEV_VERSION       "IOT-WIFI-v1.0-20201120"        //固件版本信息

#define ALINK_BODY_FORMAT         "{\"id\":\"123\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"
#define ALINK_TOPIC_PROP_POSTRSP  "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post_reply"
#define ALINK_TOPIC_PROP_SET      "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/service/property/set"
#define ALINK_METHOD_PROP_POST    "thing.event.property.post"
#define ALINK_TOPIC_DEV_INFO      "/ota/device/inform/" PRODUCT_KEY "/" DEVICE_NAME ""    
#define ALINK_VERSION_FROMA      "{\"id\": 123,\"params\": {\"version\": \"%s\"}}"
unsigned long lastMs = 0;

WiFiClient   espClient;
PubSubClient mqttClient(espClient);

void init_wifi(const char *ssid, const char *password)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi does not connect, try again ...");
        delay(500);
    }

    Serial.println("Wifi is connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    payload[length] = '\0';
    Serial.println((char *)payload);

    if (strstr(topic, ALINK_TOPIC_PROP_SET))
    {
        StaticJsonBuffer<100> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(payload);
        if (!root.success())
        {
            Serial.println("parseObject() failed");
            return;
        }
    }
}
void mqtt_version_post()
{
    char param[512];
    char jsonBuf[1024];

    //sprintf(param, "{\"MotionAlarmState\":%d}", digitalRead(13));
    sprintf(param, "{\"id\": 123,\"params\": {\"version\": \"%s\"}}", DEV_VERSION);
   // sprintf(jsonBuf, ALINK_BODY_FORMAT, ALINK_METHOD_PROP_POST, param);
    Serial.println(param);
    mqttClient.publish(ALINK_TOPIC_DEV_INFO, param);
}

void mqtt_check_connect()
{
    while (!mqttClient.connected())//mqttδ����
    {
        while (connect_aliyun_mqtt(mqttClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET))
        {
            Serial.println("MQTT connect succeed!");
            //client.subscribe(ALINK_TOPIC_PROP_POSTRSP);
            mqttClient.subscribe(ALINK_TOPIC_PROP_SET);
            
            Serial.println("subscribe done");
            mqtt_version_post();
        }
    }
    
}

void mqtt_interval_post()
{
    char param[512];
    char jsonBuf[1024];

    sprintf(param, "{\"CurrentTemperature\":%f}",dht.readTemperature());
    sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
    Serial.println(jsonBuf);
    boolean d =  mqttClient.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
    if(d){
      Serial.println("publish Temperature success"); 
    }else{
      Serial.println("publish Temperature fail"); 
    }
    sprintf(param, "{\"CurrentHumidity\":%f}",dht.readHumidity());
    sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
    Serial.println(jsonBuf);
    d =  mqttClient.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
    if(d){
      Serial.println("publish Humidity success"); 
    }else{
      Serial.println("publish Humidity fail"); 
    }
    
}


void setup()
{

    Serial.begin(115200);
    Serial.println("Demo Start");

    dht.begin();

    pinMode(RedLed,OUTPUT);
    pinMode(GreenLed,OUTPUT);

    init_wifi(WIFI_SSID, WIFI_PASSWD);

    mqttClient.setCallback(mqtt_callback);
}

// the loop function runs over and over again forever
void loop()
{
    delay(1000);
    
    float Hum = dht.readHumidity();
    float Temp = dht.readTemperature();

    /* 如果需要在串口监视温度信息，请取消以下Serial.print语句注释*/
    //Serial.print(F("Humidity: "));
    //Serial.print(Hum);
    //Serial.print(F("%  Temperature: "));
    //Serial.print(Temp);
    //Serial.println(F("°C "));
    
    if(Hum>80)
    {
      digitalWrite(RedLed,HIGH);
      digitalWrite(GreenLed,LOW);
    }
   else
   {
      digitalWrite(RedLed,LOW);
      digitalWrite(GreenLed,HIGH);
   }
   
    if (millis() - lastMs >= 20000)
    {
        lastMs = millis();
        mqtt_check_connect();
        /* Post */        
        mqtt_interval_post();
    }

    mqttClient.loop();
   
}
