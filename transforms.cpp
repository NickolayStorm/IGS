#include "transforms.h"
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using std::cout;
using std::endl;
using namespace boost::numeric::ublas;

//Transforms::Transforms()
//{
//    if(Transforms::_self == nullptr){
//        _self = this;
//    }

//}

matrix<float> Transforms::identityMatrix(){
    matrix<float> m(4, 4);
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
                m(i, j) = 0;
        }
        m(i, i) = 1;
    }
    return m;
}

QPoint Transforms::transform(Point point, Point viewer, int center){
    QPoint pcenter(-center, center);
    cout << "###################################\n";
    cout << "transform()\n";
    cout << "got point:\n" << point.makeMatrix();

    matrix<float> m = identityMatrix();
    // TODO: Actually I don't know what's going on
//    if(viewer.getX() != 0 || viewer.getY() != 0){
        m = prod(m, rotationZ(viewer));
        m = prod(m, rotationX(viewer));
//    }
    m = prod(m, mirror_yoz());
    m = prod(m, projaction());
    m = prod(m, transfer(pcenter));
    cout << "\nTransformation matrix:\n" << m;
    m = prod(point.makeMatrix(), m);
    cout << "\nResult\n" << m;
    Point res(m);
    QPoint qres(-res.getX(), res.getY());
    std::cout << "\nResult point: ("
                   << qres.x() << ", " << qres.y()
                            << ")\n";
    cout << "###################################\n" << std::endl;
    return qres;

}

matrix<float> Transforms::projaction(){
//    std::cout << "projaction()" << std::endl;
    auto m = Transforms::identityMatrix();
    m(2, 2) = 0;
//    std::cout << "Transform matrix" << m << std::endl;
    return m;
}

matrix<float> Transforms::transfer(QPoint moving){
//    std::cout << "transfer()" << std::endl;
    auto m = Transforms::identityMatrix();
    m(3, 0) = moving.x();
    m(3, 1) = moving.y();
//    cout << "Transform matrix" << m << endl;
    return m;

}

matrix<float> Transforms::mirror_yoz(){
    auto m = identityMatrix();
    m(0, 0) = -1;
//    std::cout << "mirror()" << std::endl;
//    std::cout << "Transform matrix\n" << m << std::endl;
    return m;
}

matrix<float> Transforms::rotationX(Point viewer){
    auto res = identityMatrix();
    int n = viewer.getX();
    int m = viewer.getY();
    int l = viewer.getZ();

    cout << "\nn " << n << " m " << m << " l " << l;

    res(1, 1) = l / sqrt(n*n + m*m + l*l);
    res(1, 2) = sqrt(n*n + m*m) / (sqrt(n*n + m*m + l*l));


    res(2, 1) = -(sqrt(n*n + m*m) / sqrt(n*n + m*m + l*l));
    res(2, 2) = l / (sqrt(n*n + m*m + l*l));

//    std::cout << "\nrotationX()" << std::endl;
//    std::cout << "Transform matrix\n" << res << std::endl;

    return res;

}

matrix<float> Transforms::rotationZ(Point viewer){
    auto res = identityMatrix();
    int n = viewer.getX();
    int m = viewer.getY();
//    int l = viewer.getZ();

    res(0, 0) = m / (sqrt(n*n + m*m));
    res(0, 1) = n / (sqrt(n*n + m*m));


    res(1, 0) = -(n / (sqrt(n*n + m*m)));
    res(1, 1) = m / (sqrt(n*n + m*m));


//    std::cout << "\nrotationZ()" << std::endl;
//    std::cout << "Transform matrix\n" << res << std::endl;

    return res;
}
