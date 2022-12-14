/*
 IDEASCHAIN MQTT example for DSI5168 
*/
#include <SoftwareSerial.h>
// software serial #1: RX = digital pin 10, TX = digital pin 11
SoftwareSerial SoftwareSerial2(10, 11);

#include <WiFi.h>
#include <PubSubClient.h>

// WPA/WPA2 SSID and password
char ssid[] = "Yamato";      // your network SSID (name)
char pass[] = "27182818";  // your network password
int status  = WL_IDLE_STATUS;   // the Wifi radio's status

char mqttServer[]     = "iiot.ideaschain.com.tw";  // new ideaschain dashboard MQTT server
int mqttPort          = 1883;
char clientId[]       = "ddfe6db9-3dcc-4cd4-b211-2c15a6980733"; // MQTT client ID. it's better to use unique id.
char username[]       = "5qmCDay5NMRVlp6xeK8Y";    // device access token(存取權杖)
char password[]       = "";                        // no need password
char subscribeTopic[] = "v1/devices/me/attributes"; // Fixed topic. ***DO NOT MODIFY***
char publishTopic[]   = "v1/devices/me/telemetry";  // Fixed topic. ***DO NOT MODIFY***
char publishPayload[] = "{\"TEST\":\"0\"}";        // String of stringified JSON Object (key value pairs)
char publishTopicStr[] = "TEST";


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(clientId, username, password)) {
		Serial.println(" MQTT connection Successfully, PEKO!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MQTT_publish(char DATA){
      Serial.println("MQTT connected");
      // Once connected, publish an announcement...
	    char sensorDist [30];
      sprintf (sensorDist , "{\"%s \":\"%.d \"}", publishTopicStr, int(DATA)-48);
      Serial.println(sensorDist);
      client.publish(publishTopic, sensorDist);
      // resubscribe topics
      client.subscribe(subscribeTopic);
}

void setup()
{
  Serial.begin(9600);
  SoftwareSerial2.begin(115200);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  printWifiData();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  // Allow the hardware to sort itself out
  delay(1500);
}

void printWifiData() {
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  if (SoftwareSerial2.available()) {
    char c = SoftwareSerial2.read();
    Serial.print("coremaker01:");Serial.println(c);
	if (c=='1' && c=='2'){
    MQTT_publish(c);
	}
  }
  client.loop();
}
