#include "ennepersurface.h"

EnneperSurface::EnneperSurface() : Shape(){
    uMin = 0; uInitMax = uMax = 50000; vMin = 0; vInitMax = vMax = 50000;
    uCount = 100;
    vCount = 100;
}

void EnneperSurface::func(){
//    u -= 25000;
//    v -= 25000;
    u /= 2000;
    v /= 2000;
    x = u*(1 - (u*u/3) + v*v) / 3;
    y = -v*(1 - (v*v/3) + u*u) / 3;
    z = (u*u - v*v) / 3;
}
