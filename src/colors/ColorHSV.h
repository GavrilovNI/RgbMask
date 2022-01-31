#pragma once
#include <Arduino.h>

struct ColorRGB;

struct ColorHSV
{
private:
    float h, s, v;
    
public:
    ColorHSV(float h, float s, float v);

    ColorRGB toRGB() const;

    void setH(float h);
    void setS(float s);
    void setV(float v);
    
    float getH() const;
    float getS() const;
    float getV() const;

    String toString() const;
};
