#include "shape.h"

Shape::Shape() {
    _a = _b = _c = DEFAULT_PARAMETR_VALUE;
    uCount = vCount = DEFAULT_COUNT;
    u = v = x = y = z = 0;
    uMin = vMin = 0;
    uInitMax = vInitMax = uMax = vMax = DEFAULT_MAX;
}

Point Shape::pointOn(int i, int j){
    u = uMin + ((double)i) / (uCount - 1) * (uMax - uMin);
    v = vMin + ((double)j) / (vCount - 1) * (vMax - vMin);
    func();
    return Point(x, y, z);
}

void Shape::setUV(int u, int v){
    uMax = u;
    vMax = v;
}

QPair <int, int> Shape::getUVMax(){
    return QPair<int, int>(uMax, vMax);
}

void Shape::setStepCounts(unsigned u, unsigned v){
    uCount = u;
    vCount = v;
}

QPair <int, int> Shape::getInit(){
    return QPair<int, int>(uInitMax, vInitMax);
}

void Shape::setParams(int a, int b){
    _a = a;
    _b = b;
}

QPair <int, int> Shape::getParams(){
    return QPair<int, int>(_a, _b);
}

Shape::~Shape(){

}
