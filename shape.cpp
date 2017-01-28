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

std::pair <int, int> Shape::getUVMax() const{
    return std::pair<int, int>(uMax, vMax);
}

std::pair <int, int> Shape::getUVCounts() const{
    return std::pair<int, int>(uCount, vCount);
}

void Shape::setStepCounts(unsigned u, unsigned v){
    uCount = u;
    vCount = v;
}

std::pair <int, int> Shape::getInit() const{
    return std::pair<int, int>(uInitMax, vInitMax);
}

void Shape::setParams(int a, int b){
    _a = a;
    _b = b;
}

std::pair <int, int> Shape::getParams() const{
    return std::pair<int, int>(_a, _b);
}

std::vector<Point>
Shape::makePoints(std::function<Point (const Point&)> mapping){
//    int idx = P.getX() + P.getY()*_areaSize.width();

    std::vector<Point> points;
    points.reserve(uCount * vCount);
    for(unsigned i = 0; i < uCount; ++i){
        for(unsigned j = 0; j < vCount; ++j){
            auto point = this->pointOn(i, j);
            points.push_back(mapping(point));
        }
    }
    return std::move(points);
}

std::vector<ColoredPolygon>
Shape::getPolygons(std::function<Point (const Point&)> mapping){

    auto points = this->makePoints(mapping);

    std::vector<ColoredPolygon> plgns;
    plgns.reserve((uCount - 1) * (vCount - 1)* 2);

    for(unsigned i = 1; i < uCount; ++i){
        for(unsigned j = 1; j < vCount; ++j){
            ColoredPolygon fst( points[(i - 1)*vCount + j - 1]
                              , points[(i - 1)*vCount + j]
                              , points[(i)*vCount + j - 1]);
            plgns.push_back(fst);
            ColoredPolygon snd( points[(i)*vCount + j - 1]
                              , points[(i - 1)*vCount + j]
                              , points[(i)*vCount + j]);
            plgns.push_back(snd);
        }
    }
    return std::move(plgns);
}

Shape::~Shape(){

}
