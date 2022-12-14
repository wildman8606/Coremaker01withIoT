/*
 IDEASCHAIN MQTT example for DSI5168 
*/
#include <SoftwareSerial.h>
// software serial #1: RX = digital pin 10, TX = digital pin 11
SoftwareSerial SoftwareSerial2(10, 11);

#include <WiFi.h>

// WPA/WPA2 SSID and password
char ssid[] = "Yamato";      // your network SSID (name)
char pass[] = "27182818";  // your network password
String Linetoken = "yh9ROd3r9eH6adLmgesVg4DkdOxFiF2Jpsj48Y78CJg";
int status  = WL_IDLE_STATUS;   // the Wifi radio's status
char host[] = "notify-api.line.me";

WiFiSSLClient client;

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
  String message="PEKO";
  if (client.connect(host, 443)) {
  int LEN = message.length();
  //1.傳遞網站
  String url = "/api/notify"; //Line API網址
  client.println("POST " + url + " HTTP/1.1");
  client.print("Host: "); client.println(host);//Line API網站
  //2.資料表頭
  client.print("Authorization: Bearer "); client.println(Linetoken);
  //3.內容格式
  client.println("Content-Type: application/x-www-form-urlencoded");
  //4.資料內容
  client.print("Content-Length: "); client.println( String((LEN + 8)) ); //訊息長度
  client.println();
  client.print("message="); client.println(message); //訊息內容
  //等候回應
  delay(2000);
  String response = client.readString();
  //顯示傳遞結果
  Serial.println(response);
  client.stop();//斷線
  }
  else {
  //傳送失敗
  Serial.println("connected fail");
  }
  delay(5000);
  

}
