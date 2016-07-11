# Artik-Cloud-ESP
Connect IOT devices with NodeMcu or ESP 

Now you can use ESP8266's (Tested with NodeMcu firmware ver -1 based ESP8266 12 E)  to connect Samsung Artik  Cloud  for controlling and monitoring of your IOT  devices

# Samsung Artik - Cloud 

Devices :  NodeMcue, ESP8266, ESP Wrrom2
package : 150 ~1 msg every 10 min
Number of devices:  	Unlimited
Price per device per month:	FREE
The maximum message size is 1024 bytes.


"Messages sent from device to cloud count toward the daily message quota. Actions sent and/or received by a device don't count towards the daily quota. For example, if a device sends 1 message to ARTIK Cloud which triggers a rule that sends actions to 5 other devices, only the message from the device to the cloud will count towards the message quota. If a message is rejected at the public API, it is does not count towards the daily quota. A few common reasons for messages being rejected can include: exceeded payload size, missing meta data, invalid authentication/authorization. Once a message enters the pipeline, it is counted even if it fails to be normalized."
(https://artik.cloud/pricing)

# MQTT - Artik Cloud Server params


char Artik_Cloud_Server[]     = "api.artik.cloud"; // Server 
int  Artik_Cloud_Port         = 8883; // MQTT Port
char Client_Name[] = "ARTIK-NodeMcu"; // Any Name 
char Device_ID[]   = "6e9d::::::::::::::::::::b38"; // DEVICE ID
char Device_TOKEN[]   = "a9a::::::::::::::::::::094"; //  DEVICE TOKEN
char MQTT_Publish[]      = "/v1.1/messages/6e9d::::::::::::b38"; // (/v1.1/messages/"DEVICE ID")

  
  MQTT_Artik_Client.begin(Artik_Cloud_Server, Artik_Cloud_Port, SSL_ESP); // Connect to Artik Server
  
  MQTT_Artik_Client.connect(Client_Name, Device_ID, Device_TOKEN)
  

  MQTT_Artik_Client.publish(MQTT_Publish, buf);// Publishing data to the Artik Cloud 
  


