#include <Arduino.h>
#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

const char* ssid = "OneplusHotspot";
const char* password = "hensem99";

String  data =""; 

String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
  server.begin();
}

void loop(){
  client = server.available();
  if (!client)
    return;
  data = checkClient();
  Serial.println(data);
  delay(100);
}