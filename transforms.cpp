#include "transforms.h"
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using std::cout;
using std::endl;
using namespace boost::numeric::ublas;
matrix<float> Transforms::_matr = Transforms::identityMatrix();
Transforms::Transforms()
{
}

matrix<float> Transforms::identityMatrix(){
    matrix<float> m(4, 4);
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
                m(i, j) = 0;
        }
        m(i, i) = 1;
    }
    return std::move(m);
}

Point Transforms::transform(Point point){
    auto mpoint = point.makeMatrix();
    auto m = prod(mpoint, _matr);
    Point res(m);
    return std::move(res);
}

void Transforms::refreshMatrix(Point viewer, int center){
    matrix<float> m = identityMatrix();
    // TODO: Actually I don't know what's going on
    // Look's like we need one more check
    if(viewer.getX() != 0 || viewer.getY() != 0){
        m = prod(m, rotationZ(viewer));
        m = prod(m, rotationX(viewer));
    }
    m = prod(m, transfer(-center, center));
    m = prod(m, mirror_yoz());
    this->_matr = m;
    cout << "refreshMatrix()\n";
    cout << _matr << endl;
}


matrix<float> Transforms::projaction(){
    auto m = Transforms::identityMatrix();
    m(2, 2) = 0;
    return std::move(m);
}

matrix<float> Transforms::transfer(int x, int y){
    auto m = Transforms::identityMatrix();
    m(3, 0) = x;
    m(3, 1) = y;
    return std::move(m);
}

matrix<float> Transforms::mirror_yoz(){
    auto m = identityMatrix();
    m(0, 0) = -1;
    return std::move(m);
}

matrix<float> Transforms::rotationX(Point viewer){
    auto res = identityMatrix();
    int n = viewer.getX();
    int m = viewer.getY();
    int l = viewer.getZ();

    res(1, 1) = l / sqrt(n*n + m*m + l*l);
    res(1, 2) = sqrt(n*n + m*m) / (sqrt(n*n + m*m + l*l));

    res(2, 1) = -(sqrt(n*n + m*m) / sqrt(n*n + m*m + l*l));
    res(2, 2) = l / (sqrt(n*n + m*m + l*l));

    return std::move(res);

}

matrix<float> Transforms::rotationZ(Point viewer){
    auto res = identityMatrix();
    int n = viewer.getX();
    int m = viewer.getY();

    res(0, 0) = m / (sqrt(n*n + m*m));
    res(0, 1) = n / (sqrt(n*n + m*m));

    res(1, 0) = -(n / (sqrt(n*n + m*m)));
    res(1, 1) = m / (sqrt(n*n + m*m));

    return std::move(res);
}
