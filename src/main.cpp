#include <Arduino.h>
#include <WebServer.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <Stream.h>
#include <vector>
#include <cmath>
#include "WifiManager.h"
#include "led/adafruit/AdafruitLedSnakeMatrix.h"
#include "led/adafruit/AdafruitLedStripContainer.h"
#include "led/LedMatrixSet.h"
#include "utils/ContainerConventer.h"
#include "masks/BrightnessLedPixel.h"

#include "snake/Snake.h"
#include "snake/SnakeMap.h"
#include "snake/SnakeMapUpdater.h"
#include "snake/AutoSnake.h"

#include "animations/matrix/Rainbow45.h"
#include "animations/matrix/SnakeAnim.h"

#include "masks/matrix/Circle.h"
#include "masks/matrix/Square.h"
#include "masks/matrix/BrightnessGradient.h"

#include "colorer/matrix/Solid.h"
#include "colorer/matrix/SnakeMapDrawer.h"

AdafruitLedStripContainer<AdafruitLedSnakeMatrix> matrixes;

std::shared_ptr<LedMatrixSet> matrixSet;


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


std::shared_ptr<SnakeMap> snakeMap;
std::shared_ptr<Snake> snake;
std::shared_ptr<SnakeMapUpdater> snakeMapUpdater = std::make_shared<SnakeMapUpdater>();
std::shared_ptr<AutoSnake> autoSnake;



//std::shared_ptr<Colorer<LedMatrix>> colorer = std::make_shared<Solid>(ColorRGB(255, 0, 0));
std::shared_ptr<Colorer<LedMatrix>> colorer;

void setup()
{
  //matrixes.push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(16, 8), 16, NEO_GRB + NEO_KHZ800));
  //matrixes.push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(16, 8), 21, NEO_GRB + NEO_KHZ800));
  
  matrixes.push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(7, 13), 16, NEO_RGB + NEO_KHZ800));
  matrixes.push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(7, 13), 5, NEO_RGB + NEO_KHZ800));
  matrixes.push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(7, 13), 19, NEO_RGB + NEO_KHZ800));
  matrixes.push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(4, 13), 21, NEO_RGB + NEO_KHZ800));
  
  matrixSet = std::make_shared<LedMatrixSet>(container_cast(matrixes.strips), LedMatrixSet::Right);

  snake = std::make_shared<Snake>(Vector2<int32_t>(3, 3), Direction::Right, 3);
  snakeMap = std::make_shared<SnakeMap>(Vector2<int32_t>(matrixSet->getSize()));
  snakeMap->addSnake(snake);

  snakeMapUpdater->spawnFood(snakeMap);

  autoSnake = std::make_shared<AutoSnake>(snake, snakeMap);

  colorer = std::make_shared<SnakeMapDrawer>(snakeMap, ColorRGB(255, 0, 0), ColorRGB(0, 255, 0), ColorRGB(255, 255, 0));

  Serial.begin(9600);
  
  //server.on("/", onHome);
  //server.on("/setcolor", onSetColor);
  //server.on("/connect", onConnect);

  matrixes.begin();
  matrixes.clear();
  matrixes.show();
  matrixes.setBrightness(30);

  Serial.println("Begin");

  //setupSd();

  //loadWifiSettings();

}



//Animation<LedMatrix>* animation = new Rainbow45(25);
//Animation<LedMatrix>* animation = new Snake(8*32, ColorRGB(0, 0, 255));

float speed = 8.0f;
unsigned long lastMillis; 


float snakeTime;

int snakeStepTime = 200;

void loop()
{
  //Serial.println("loop");

  /*if(wifi.isAccessPoint() == false)
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
*/

  matrixes.clear();

  //auto circle = std::make_shared<Circle>(matrixSet, Vector2<uint16_t>(5, 4), 0, 4);
  //auto square = std::make_shared<Square>(matrixSet, Bounds<uint16_t>(1, 2, 9, 5));

  //auto mask = circle->max_(square);
  //auto mask = std::make_shared<Circle>(matrixSet, Vector2<uint16_t>(12, 6), 3, 5);
  //auto mask = std::make_shared<BrightnessGradient>(matrixSet, matrixSet->getSize().x);
  //auto mask = circle;
  auto mask = matrixSet;

  int snakeMoves = (int)floor(snakeTime / snakeStepTime);
  snakeTime -= snakeMoves * snakeStepTime;

  //Serial.println("asd1");
  
  for(int i = 0; i < snakeMoves; i++)
  {
    if(snake->isDead() == false)
    {
      //Serial.println("asd4");
      autoSnake->decide();
      //Serial.println("asd5");
      snake->move(snakeMap, snakeMapUpdater);
      //Serial.println("asd6");
    }
    else
    {
      sleep(1000);
      ESP.restart();
    }
  }

  //Serial.println("asd2");
  colorer->apply(mask);
  matrixes.show();

  unsigned long currMillis = millis();
  unsigned long delta = currMillis - lastMillis;
  lastMillis = currMillis;

  snakeTime += delta;
  
  //Serial.println("asd3");
  //animation->moveTime(speed * delta / 1000);
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
    matrixSet->getPixel(Vector2<uint16_t>(x, y))->setColor(ColorRGB(r, g, b));
    matrixes.show();
    server.send(200, "text/plain", "done");  
  }
  else
  {
    server.send(400, "text/plain", "wrong request");  
  }
}