#include "ColorRGB.h"
#include "ColorHSV.h"

ColorRGB::ColorRGB(uint8_t r, uint8_t g, uint8_t b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

ColorRGB::ColorRGB(uint8_t* bytes)
{
    r = bytes[0];
    g = bytes[1];
    b = bytes[2];
}

std::vector<uint8_t> ColorRGB::toBytes() const
{
    return std::vector<uint8_t> { r, g, b };
}

uint32_t ColorRGB::toUInt32() const
{
    return (((uint32_t)r) << 16) + (((uint32_t)g) << 8) + b;
}

ColorHSV ColorRGB::toHSV() const
{
    float h, s, v;

    float min = r < g ? r : g;
    min = min < b ? min : b;
    float max = r > g ? r : g;
    max = max > b ? max : b;

    v = max / 255.0f;
    float delta = max - min;

    if (delta < 0.00001)
        h = 0;
    else if(r >= max)
        h = (g - b) / delta;
    else if(g >= max)
        h = (b - r) / delta + 2.0f;
    else
        h = (r - g) / delta + 4.0f;

    h *= 60;
    
    if(max <= 0)
        s = 0;
    else
        s = delta / max;

    if( h < 0.0 )
        h += 360.0;

    return ColorHSV(h, s, v);
}

String ColorRGB::toString() const
{
    String strR(r);
    String strG(g);
    String strB(b);

    return String("ColorRGB(" + strR + ";" + strG + ";" + strB + ")");
}
