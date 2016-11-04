#ifndef SHAPE_H
#define SHAPE_H
#include <QString>
#include "point.h"
//public int vCount, uCount;
//		public double a, b, c;
//		public double uMin, uMax, vMin, vMax, uInitMax, vInitMax;
//		const int DEFAULT_PARAMETR_VALUE = 50;
//		const int DEFAULT_COUNT = 20;
//		const int DEFAULT_MAX = 100;
//		public string name;
//		public Shape() {
//			a = b = c = DEFAULT_PARAMETR_VALUE;
//			uCount = vCount = DEFAULT_COUNT;
//			u = v = x = y = z = 0;
//			uMin = vMin = 0;
//			uInitMax = vInitMax = uMax = vMax = DEFAULT_MAX;
//		}
//		public override string ToString() {
//			return name;
//		}
//		protected double u, v, x, y, z;
//		public HomogenPoint3d func(int i, int j) {
//			u = uMin + ((double)i) / (uCount - 1) * (uMax - uMin);
//			v = vMin + ((double)j) / (vCount - 1) * (vMax - vMin);
//			calc();
//			return new HomogenPoint3d(x, y, z);
//		}
//		public virtual void calc() { }
//	}


class Shape
{
protected:
    int vCount, uCount;
    double a, b, c;
    double uMin, uMax, vMin, vMax, uInitMax, vInitMax;
    const int DEFAULT_PARAMETR_VALUE = 50;
    const int DEFAULT_COUNT = 20;
    const int DEFAULT_MAX = 100;
    QString name;
    double u, v, x, y, z;
public:
    Shape();
    Point pointOn(int i, int j);
    virtual void func() = 0;

};

#endif // SHAPE_H
