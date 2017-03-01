#include "shell.h"

Shell::Shell()
{
    uMin = 0;
    uMax = 2000;//  # 1440
    vMin = 0;
    vMax = 360;

    uCount = vCount = 20;

    uInitMax = 1500;
    vInitMax = 360;

    _a = 90;
    _b = 30;

    u = 1800;
    v = 360;

}

void Shell::func(){
    u *= M_PI / 180;
    v *= M_PI / 180;

    x = u * cos(u) * (cos(v) + _b/10);
    y = - u * sin(u) * (cos(v) + _b/10);
    z = u * sin(v) - (M_PI * (u + 7) / (_a/10 + 1) )*((M_PI * (u + 7) / (_a/10 + 1) )) + 100;
}

Shell::~Shell(){

}
