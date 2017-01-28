#include "toruscurve.h"

TorusCurve::TorusCurve()
{
    uMin = 0; uInitMax = uMax = 360; vMin = 0; vInitMax = vMax = 360;
    _a = 70; _b = 40;
}

void TorusCurve::func(){
    u *= M_PI / 180;
    v *= M_PI / 180;
    float xx = _a * cos(v);
    float yy = _b * sin(v);
    float r = u * 4;
    float xr = xx * cos(r) + yy * sin(r);
    float yr = -xx * sin(r) + yy * cos(r);
    x = (yr + 150) * cos(u);
    y = (yr + 150) * sin(u);
    z = xr;
}
