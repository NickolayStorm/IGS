#ifndef TRANSFORMS_H
#define TRANSFORMS_H
#include "point.h"
#include <QPoint>
using namespace boost::numeric::ublas;
class Transforms
{
private:
    matrix<float> _matr;
    matrix<float> _rotations;
    matrix<float> _move;
    Transforms();
    static Transforms *_self;
    static matrix<float> transfer(int, int);
    static matrix<float> rotationX(Point viewer);
    static matrix<float> rotationZ(Point viewer);
    static matrix<float> projaction();
    static inline matrix<float> mirror_yoz();
    static matrix<float> identityMatrix();
public:
    static Transforms* instance();
    void bindGeneralMatrix();
    // X and Y are center of coordinats
    void refreshMatrix(Point viewer, int x, int y);
    Point transform(Point point);
    void printMatrix(){
        std::cout << "Transforms::printMatrix()\n"
                  << _matr << std::endl;
    }
    void rotateX(float angle);
    void rotateY(float angle);

};

#endif // TRANSFORMS_H
