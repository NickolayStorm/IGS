#include "transforms.h"
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using std::cout;
using std::endl;
using namespace boost::numeric::ublas;

// Fuck you and your singleton
#define DO_ONCE(...) { static bool _do_once_ = ([&](){ __VA_ARGS__ }(), true); (void)_do_once_; }

Transforms* Transforms::_self = nullptr;

Transforms::Transforms()
{
    _matr = identityMatrix();
}

Transforms* Transforms::instance(){
    DO_ONCE(
                Transforms::_self = new Transforms();
            )
    return _self;
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

void Transforms::bindGeneralMatrix(){
    matrix<float> m = identityMatrix();
    m = prod(m, _rotations);
    m = prod(m, _move);
    m = prod(m, mirror_yoz());
    _matr = m;
    printMatrix();
}

void Transforms::refreshMatrix(Point viewer, int center){
    _rotations = prod(rotationZ(viewer), rotationX(viewer));
    _move = transfer(-center, center);
    bindGeneralMatrix();
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

void Transforms::rotateY(float angle){
    float cosinus = cos(angle);
    float sinus = sin(angle);
    auto rotation = identityMatrix();
    rotation(0, 0) = cosinus;
    rotation(0, 2) = -sinus;
    rotation(2, 0) = sinus;
    rotation(2, 2) = cosinus;
    _rotations = prod(_rotations, rotation);
    bindGeneralMatrix();
}

void Transforms::rotateX(float angle){
    float cosinus = cos(angle);
    float sinus = sin(angle);
    auto rotation = identityMatrix();
    rotation(0, 0) = 1;
    rotation(1, 1) = cosinus;
    rotation(1, 2) = sinus;
    rotation(2, 1) = -sinus;
    rotation(2, 2) = cosinus;
    _rotations = prod(_rotations, rotation);
    bindGeneralMatrix();
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
