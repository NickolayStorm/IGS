#include "shape.h"

Shape::Shape() {
    a = b = c = DEFAULT_PARAMETR_VALUE;
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

Shape::~Shape(){

}
