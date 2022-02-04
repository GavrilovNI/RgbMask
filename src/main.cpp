
#include <memory>

#include "utils/ContainerConventer.h"

#include "led/LedMatrixSet.h"
#include "led/adafruit/AdafruitLedStripContainer.h"
#include "led/adafruit/AdafruitLedSnakeMatrix.h"

#include "animations/matrix/Rainbow45.h"

#include "Vector2.h"

#include "tests/AnimationTest.h"
#include "tests/SnakeTest.h"

auto ledStrips = std::make_shared<AdafruitLedStripContainer<AdafruitLedSnakeMatrix>>();
std::shared_ptr<LedMatrixSet> matrixSet;

std::shared_ptr<Test> test;

void setup()
{
    Serial.begin(9600);

    ledStrips->push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(7, 13), 16, NEO_RGB + NEO_KHZ800));
    ledStrips->push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(7, 13), 5, NEO_RGB + NEO_KHZ800));
    ledStrips->push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(7, 13), 19, NEO_RGB + NEO_KHZ800));
    ledStrips->push_back(new AdafruitLedSnakeMatrix(Vector2<uint16_t>(4, 13), 21, NEO_RGB + NEO_KHZ800));

    matrixSet = std::make_shared<LedMatrixSet>(container_cast(ledStrips->strips), LedMatrixSet::Right);

    //test = std::make_shared<AnimationTest>(ledStrips, matrixSet, std::make_shared<Rainbow45>(20));
    test = std::make_shared<SnakeTest>(ledStrips, matrixSet);

    ledStrips->begin();
    ledStrips->clear();
    ledStrips->show();
    ledStrips->setBrightness(255);

    Serial.println("Begin");
}

void loop()
{
    test->loop();
}
