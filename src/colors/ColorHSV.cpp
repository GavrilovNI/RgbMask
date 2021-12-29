#include <cmath>
#include "ColorHSV.h"
#include "ColorRGB.h"

ColorHSV::ColorHSV(float h, float s, float v)
{
    setH(h);
    setS(s);
    setV(v);
}

void ColorHSV::setH(float h)
{
    if(h < 0 || h > 360)
        throw "Hue out of range[0-360].";
    this->h = h;
}

void ColorHSV::setS(float s)
{
    if(s < 0 || s > 1)
        throw "Saturation out of range[0-1].";
    this->s = s;
}
void ColorHSV::setV(float v)
{
    if(v < 0 || v > 1)
        throw "Value out of range[0-1].";
    this->v = v;
}
    
float ColorHSV::getH()
{
    return h;
}
float ColorHSV::getS()
{
    return s;
}
float ColorHSV::getV()
{
    return v;
}

ColorRGB ColorHSV::toRGB() const
{
    float C = s*v;
    float X = C*(1-std::abs(std::fmod(h/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(h >= 0 && h < 60){
        r = C,g = X,b = 0;
    }
    else if(h >= 60 && h < 120){
        r = X,g = C,b = 0;
    }
    else if(h >= 120 && h < 180){
        r = 0,g = C,b = X;
    }
    else if(h >= 180 && h < 240){
        r = 0,g = X,b = C;
    }
    else if(h >= 240 && h < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    r = (r+m)*255;
    g = (g+m)*255;
    b = (b+m)*255;
    return ColorRGB(r, g, b);
}