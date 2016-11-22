#include "heart.h"

Heart::Heart()
{
    uMin = 0; uInitMax = uMax = 360; vMin = 0; vInitMax = vMax = 360;
    _a = 70; _b = 40;
    name = "Tor";
}

void Heart::func(){
    u *= M_PI / 180;
    v *= M_PI / 180;
    float xx = _a * cos(v);
    float yy = _b * sin(v);
    float r = u * 4;
    float xr = xx * cos(r) + yy * sin(r);
    float yr = -xx * sin(r) + yy * cos(r);
    x = (yr + 200) * cos(u);
    y = (yr + 200) * sin(u);
    z = xr;
}

