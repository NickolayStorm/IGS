#ifndef TRANSFORMS_H
#define TRANSFORMS_H
#include "point.h"
#include <QPoint>
using namespace boost::numeric::ublas;
class Transforms
{
private:
    static matrix<float> _matr;
    static matrix<float> transfer(QPoint);
    static matrix<float> rotationX(Point viewer);
    static matrix<float> rotationZ(Point viewer);
    static matrix<float> projaction();
    static inline matrix<float> mirror_yoz();
    static matrix<float> identityMatrix();
public:
    Transforms();
    void refreshMatrix(Point viewer, int center);
    QPoint transform(Point point);
    void printMatrix(){
        std::cout << "Transforms::printMatrix()\n"
                  << _matr << std::endl;
    }

};

#endif // TRANSFORMS_H
