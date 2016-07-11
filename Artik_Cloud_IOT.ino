/*
 * Auth : Algobel Technology & Innovation 
 * Date : 11 july 2016
 * Email : algobelforum@gmail.com
 * Free to Use under MIT licence
 *  All libraries can download from github 
 */


#include <MQTTClient.h>

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

// DHT11 Sensor Setting 

#include "DHT.h"
#define DHTPIN D5 // Connects DHT11 Sensor Output to NodeMcu PIN D5
#define DHTTYPE DHT11   // etc.. DHT22/ DH11 
 
float t=0; // DHT11 temperature
float h=0; // DHT11 Humidity 

const char* _SSID     = ":::::::::"; //Wi-Fi SSID 
const char* _PASSWORD = "::::::::::::"; // Wi-Fi Password 


// MQTT - Artik Cloud Server params
char Artik_Cloud_Server[]     = "api.artik.cloud"; // Server 
int  Artik_Cloud_Port         = 8883; // MQTT Port
char Client_Name[] = "ARTIK-NodeMcu"; // Any Name 
char Device_ID[]   = "6e9d::::::::::::::::::::b38"; // DEVICE ID
char Device_TOKEN[]   = "a9a::::::::::::::::::::094"; //  DEVICE TOKEN
char MQTT_Publish[]      = "/v1.1/messages/6e9d::::::::::::b38"; // (/v1.1/messages/"DEVICE ID")

char buf[200]; // Json Data to Artik Cloud 


WiFiClientSecure SSL_ESP; // ESP SSL Connection to Artik cloud 

MQTTClient MQTT_Artik_Client; // MQTT Protocol

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  delay(1000);
  Serial.begin(115200);  
  // Wifi Setting
  WiFi.begin(_SSID, _PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  MQTT_Artik_Client.begin(Artik_Cloud_Server, Artik_Cloud_Port, SSL_ESP); // Connect to Artik Server
  
  while (!MQTT_Artik_Client.connect(Client_Name, Device_ID, Device_TOKEN)) { // Connect to Artik IOT Device 
    Serial.print("*");
    delay(1000);
  }
}

void loadBuffer(float Temp, float Hum, float Light) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& dataPair = jsonBuffer.createObject();
  dataPair["temperature"] = t ;
  dataPair["humidity"] = h;
  dataPair["Light"] = Light;
  dataPair.printTo(buf, sizeof(buf));
  Serial.println(buf);
}


void loop() {
  t = dht.readTemperature();
  h = dht.readHumidity();
  
  loadBuffer(t, h, 23.7);  // Publishing data list 
  delay(1000);
  
  MQTT_Artik_Client.publish(MQTT_Publish, buf);// Publishing data to the Artik Cloud 
  delay(3000);
  Serial.println("Publishing..");     
  for (int i =0; i<100;i++){ // delay 10 Mnts ( as per Artik Free package specifications) 
    delay(6000);
  }  
  MQTT_Artik_Client.loop();
  delay(10); 
}
