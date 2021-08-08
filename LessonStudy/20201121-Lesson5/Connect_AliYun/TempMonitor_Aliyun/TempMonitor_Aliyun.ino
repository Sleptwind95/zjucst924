#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "aliyun_mqtt.h"
#include "DHT.h"

// GPIO 13, D7 on the Node MCU v3
#define SENSOR_PIN 13

#define WIFI_SSID        "CHENG_Wlan"//定义为自己的WIFI名称
#define WIFI_PASSWD      "1472583690"//定义为自己的WIFI密码

#define PRODUCT_KEY      "a10fZzprmx5" //替换自己的PRODUCT_KEY（阿里云生成）
#define DEVICE_NAME      "1020_home" //替换自己的DEVICE_NAME（阿里云生成）
#define DEVICE_SECRET    "21a564b647cc0d39529c9a64f0f08970"//替换自己的DEVICE_SECRET（阿里云生成）
#define DEV_VERSION       "IOT-WIFI-v1.0-20201120"        //固件版本信息（自定义）

#define ALINK_BODY_FORMAT         "{\"id\":\"123\",\"version\":\"1.0\",\"method\":\"%s\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"
#define ALINK_TOPIC_PROP_POSTRSP  "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post_reply"
#define ALINK_TOPIC_PROP_SET      "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/service/property/set"
#define ALINK_METHOD_PROP_POST    "thing.event.property.post"
#define ALINK_TOPIC_DEV_INFO      "/ota/device/inform/" PRODUCT_KEY "/" DEVICE_NAME ""    
#define ALINK_VERSION_FROMA      "{\"id\": 123,\"params\": {\"version\": \"%s\"}}"
unsigned long lastMs = 0;

WiFiClient   espClient;
PubSubClient mqttClient(espClient);
//init_wifi（连接WiFi）
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
//mqtt_callback（mqtt协议连接阿里云）
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

    //sprintf(param, "{\"MotionAlarmState\":%d}", digitalRead(13));
    sprintf(param, "{\"CurrentHumidity\":%d,\"CurrentTemperature\":12,\"GeoLocation\":{\"CoordinateSystem\":2,\"Latitude\":2,\"Longitude\":123,\"Altitude\":1}}", digitalRead(13));
    sprintf(jsonBuf, ALINK_BODY_FORMAT, ALINK_METHOD_PROP_POST, param);
    Serial.println(jsonBuf);
    mqttClient.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
}


void setup()
{

    pinMode(SENSOR_PIN, INPUT);
    /* initialize serial for debugging */
    Serial.begin(115200);

    Serial.println("Demo Start");

    init_wifi(WIFI_SSID, WIFI_PASSWD);

    mqttClient.setCallback(mqtt_callback);
}

// the loop function runs over and over again forever
void loop()
{
    if (millis() - lastMs >= 20000)
    {
        lastMs = millis();
        mqtt_check_connect();
        /* Post */        
        mqtt_interval_post();
    }

    mqttClient.loop();

    unsigned int WAIT_MS = 2000;
    if (digitalRead(SENSOR_PIN) == HIGH)
    {
        Serial.println("Motion detected!");
    }
    else
    {
        Serial.println("Motion absent!");
    }
    delay(WAIT_MS); // ms
    Serial.println(millis() / WAIT_MS);
}
