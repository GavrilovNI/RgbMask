#include <Arduino.h>
#include <WebServer.h>
#include "LedSnakeMatrix.h"
#include "WifiManager.h"

LedSnakeMatrix matrix(8, 32, 2, NEO_GRB + NEO_KHZ800);
WifiManager wifi;

WebServer server(80);
bool serverWorking = false;

void onSetColor();
void onConnect();
void onHome() {
    server.send(200, "text/plain", "Hello!");
}

void beginServer()
{
  server.begin();
  serverWorking = true;
}

void closeServer()
{
  server.close();
  serverWorking = false;
}

void setup() {
  Serial.begin(9600);
  matrix.begin();
  
  server.on("/", onHome);
  server.on("/setcolor", onSetColor);
  server.on("/connect", onConnect);


  matrix.clear();
  matrix.show();

  wifi.setUpAccessPoint("LedMask");
  Serial.println(wifi.getAccessPointIp());
  beginServer();
}

String wifiName, wifiPassword;

void loop() {

  if(wifi.isAccessPoint() == false)
  {
    if(wifi.isConnected() == false)
    {
      if(serverWorking) {
        closeServer();
      }
      wifi.connect(wifiName, wifiPassword);

      if(wifi.isConnected() == false)
      {
        wifi.setUpAccessPoint("LedMask");
        Serial.println(wifi.getAccessPointIp());
      }
      else
      {
        Serial.println(wifi.getLocalIp());
      }
      beginServer();
    }
  }

  if(serverWorking)
    server.handleClient();

  delay(100);
}

String getArgOrDefault(String argName, String defaultValue)
{
  String value = server.arg(argName);
  if(value == "")
    value = defaultValue;
  return value;
}

void onConnect()
{
  wifiName = server.arg("name");
  wifiPassword = server.arg("password");

  server.send(200, "text/plain", "trying to connect");

  closeServer();
  if(wifi.isAccessPoint())
    wifi.stopAccesPoint();
  else if(wifi.isConnected())
    wifi.disconnect();
}

void onSetColor()
{
  int16_t x = getArgOrDefault("x", "-1").toInt();
  int16_t y = getArgOrDefault("y", "-1").toInt();
  uint8_t r = getArgOrDefault("r", "0").toInt();
  uint8_t g = getArgOrDefault("g", "0").toInt();
  uint8_t b = getArgOrDefault("b", "0").toInt();

  if(x >= 0 && y >= 0)
  {
    matrix.GetPixel(x, y).SetColor(r, g, b);
    matrix.show();
    server.send(200, "text/plain", "done");  
  }
  else
  {
    server.send(400, "text/plain", "wrong request");  
  }
}