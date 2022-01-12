#include <Arduino.h>
#include <WebServer.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <Stream.h>
#include <vector>
#include "WifiManager.h"
#include "led/adafruit/AdafruitLedSnakeMatrix.h"
#include "animations/Rainbow45.h"
#include "animations/Snake.h"
#include "led/LedMatrixSet.h"

LedMatrix *matrix;
AdafruitLedSnakeMatrix *matrix1 = new AdafruitLedSnakeMatrix(7, 13, 2, NEO_GRB + NEO_KHZ800);
AdafruitLedSnakeMatrix* matrix2 = new AdafruitLedSnakeMatrix(7, 13, 4, NEO_GRB + NEO_KHZ800);

std::vector<LedMatrix*> matrixes;

LedMatrixSet* matrixSet;


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

void setupSd() {
  if(!SD.begin(5)){
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }
}

const String wifiFilePath = "/wifi.txt";

String wifiName, wifiPassword;

String readLine(Stream& stream)
{
  String result = stream.readStringUntil('\r');
  stream.readStringUntil('\n');
  return result;
}

bool loadWifiSettings()
{
  File wifiSettingsFile = SD.open(wifiFilePath);
  if(wifiSettingsFile)
  {
    wifiName = readLine(wifiSettingsFile);
    wifiPassword = readLine(wifiSettingsFile);
    wifiSettingsFile.close();
    return true;
  }
  return false;
}

void saveWifiSettings()
{
  File wifiSettingsFile = SD.open(wifiFilePath, FILE_WRITE);
  if(wifiName != "")
  {
    wifiSettingsFile.println(wifiName.c_str());
    wifiSettingsFile.println(wifiPassword.c_str());
    wifiSettingsFile.close();
  }
}

void setup() {

  matrixes.push_back(matrix1);
  matrixes.push_back(matrix2);
  matrixSet = new LedMatrixSet(matrixes, LedMatrixSet::Right);
  matrix = (LedMatrix*)matrixSet;

  Serial.begin(9600);
  matrix1->begin();
  matrix2->begin();
  
  server.on("/", onHome);
  server.on("/setcolor", onSetColor);
  server.on("/connect", onConnect);

  matrix1->LedStrip::clear();
  matrix2->LedStrip::clear();
  matrix1->show();
  matrix2->show();

  setupSd();

  loadWifiSettings();

  matrix1->setBrightness(30);
  matrix2->setBrightness(30);
}

Rainbow45 anim(25);
//Snake anim(8*32, ColorRGB(0, 0, 255));
float speed = 8.0f;
unsigned long lastMillis; 

void loop() {

  if(wifi.isAccessPoint() == false)
  {
    if(wifi.isConnected() == false)
    {
      if(serverWorking)
      {
        closeServer();
      }

      if(wifiName != "")
      {
        Serial.println(String("Connecting to '" + wifiName + "'"));
        wifi.connect(wifiName, wifiPassword);
      }

      if(wifi.isConnected() == false)
      {
        Serial.println("Failed to  connect.");

        String accessPointName = "LedMask";
        wifi.setUpAccessPoint(accessPointName);
        Serial.println(String("Access point started '" + accessPointName + "'"));
        Serial.println(wifi.getAccessPointIp());
        saveWifiSettings();
      }
      else
      {
        Serial.println("Connected!");
        Serial.println(wifi.getLocalIp());
      }
      beginServer();
    }
  }

  if(serverWorking)
    server.handleClient();

  anim.Apply(*matrix);
  matrix1->show();
  matrix2->show();

  unsigned long currMillis = millis();
  unsigned long delta = currMillis - lastMillis;
  lastMillis = currMillis;
  
  anim.MoveFrame(speed * delta / 1000);
  delay(10);
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
    matrix1->getPixel(x, y)->setColor(ColorRGB(r, g, b));
    matrix1->show();
    server.send(200, "text/plain", "done");  
  }
  else
  {
    server.send(400, "text/plain", "wrong request");  
  }
}