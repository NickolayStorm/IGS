#include "tor.h"
#include <cmath>

Tor::Tor() : Shape()
{
    uMin = 0; uInitMax = uMax = 360; vMin = 0; vInitMax = vMax = 360;
    a = 70; b = 40;
    name = "Tor";
}

void Tor::func(){
    u *= M_PI / 180;
    v *= M_PI / 180;
    x = (b * cos(v) + a) * cos(u);
    y = (b * cos(v) + a) * sin(u);
    z = b * sin(v);
}
