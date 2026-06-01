#pragma once
#include "Line.h"


#include <iostream>
std::ostream& operator<<(std::ostream& str, const Line& line) {
	str << line.getX0() << " " << line.getY0() << " " << line.getZ0() << std::endl;
	str << line.getA() << " " << line.getB() << " " << line.getC() << std::endl;
	return str;
}

//bool Line::isSame(const Line& l)  {
//	vec s1 = vec(getA(), getB(), getC()); // направляющий вектор 1 прямой
//	vec s2 = vec(l.getA(), l.getB(), l.getC()); // 2 прямой
//
//	if (!s1.isCollinear(s2)) return false; // коллинеарность направляющих векторов
//
//	//vec d = vec(l.getX0() - getX0(), l.getY0() - getY0(), l.getZ0() - getZ0()); // вектор из точек на прямых
//
//	//if (!d.isCollinear(s1)) return false;
//	return true;
//}
bool Line::isSame(const Line& l) const {
    const double eps = 1e-9;

    vec s1(getA(), getB(), getC());
    vec s2(l.getA(), l.getB(), l.getC());
    vec dots(l.point.getX0() - point.getX0(), l.point.getY0() - point.getY0(), l.point.getZ0() - point.getZ0() );

    vec c1 = s1 ^ s2;
    vec c2 = s1 ^ dots;

    return std::fabs(c1.getA()) < eps && std::fabs(c1.getB()) < eps && std::fabs(c1.getC()) < eps &&
        std::fabs(c2.getA()) < eps && std::fabs(c2.getB()) < eps && std::fabs(c2.getC()) < eps;
}
