#include <Arduino.h>
#include <vector>
#include <cmath>

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

std::shared_ptr<SnakeMap> snakeMap;
std::shared_ptr<Snake> snake;
std::shared_ptr<SnakeMapUpdater> snakeMapUpdater = std::make_shared<SnakeMapUpdater>();
std::shared_ptr<AutoSnake> autoSnake;


std::shared_ptr<Colorer<LedMatrix>> colorer;

void setup()
{
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

  matrixes.begin();
  matrixes.clear();
  matrixes.show();
  matrixes.setBrightness(30);

  Serial.println("Begin");
}

unsigned long lastMillis; 
float snakeTime;
int snakeStepTime = 200;

void loop()
{
  matrixes.clear();
  auto mask = matrixSet;

  int snakeMoves = (int)floor(snakeTime / snakeStepTime);
  snakeTime -= snakeMoves * snakeStepTime;

  for(int i = 0; i < snakeMoves; i++)
  {
    if(snake->isDead() == false)
    {
      autoSnake->decide();
      snake->move(snakeMap, snakeMapUpdater);
    }
    else
    {
      delay(1000);
      ESP.restart();
    }
  }

  colorer->apply(mask);
  matrixes.show();

  unsigned long currMillis = millis();
  unsigned long delta = currMillis - lastMillis;
  lastMillis = currMillis;

  snakeTime += delta;

  delay(10);
}