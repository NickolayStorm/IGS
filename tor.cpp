#include "tor.h"
#include <cmath>

Tor::Tor() : Shape()
{
    uMin = 0; uInitMax = uMax = 360; vMin = 0; vInitMax = vMax = 360;
    _a = 70; _b = 40;
}

void Tor::func(){
    u *= M_PI / 180;
    v *= M_PI / 180;
    x = (_b * cos(v) + _a) * cos(u);
    y = (_b * cos(v) + _a) * sin(u);
    z = _b * sin(v);
}

Tor::~Tor(){

}
