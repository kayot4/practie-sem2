#pragma once
#include <vector>
#include "Line.h"
#include "Point.h"
#include "VectorNormali.h"






class Plane
{
private:
	double A;
	double B;
	double C;
	double D;
public:
	Plane() : A(0), B(0), C(0), D(0) {} //по умолчан
	Plane(double A_, double B_, double C_, double D_) : A(A_), B(B_), C(C_), D(D_) {} //инициал

	bool isSame(const Plane& pl) ;//совп
	bool isParallel(const Plane& pl) ;// паралелл
	bool only2Parallel(const Plane& p1, const Plane& p2) ;
	bool isPerpendicular(const Plane& pl1) ;
	bool BissPlanesPerpParal(const Plane& p1, const Plane& p2) ;


	bool Same2Parallel1(const Plane& p1, const Plane& p2) ;
	bool Same2Peresec1Perp(const Plane& p1, const Plane& p2) ;
	bool Same2Peresec1(const Plane& p1, const Plane& p2) ;

	double Distance(const Point& p) ;
	int RangRash(const Plane& pl1, const Plane& pl2) ;
	int RangCas(const Plane& pl1, const Plane& pl2) ;
	Plane MiddlPlane(const Plane& pl) ;
	void normalize() ;
	std::vector<Plane> BissPlane(const Plane& pl) ;
	Line FindLine3peres1line(const Plane& pl1, const Plane& pl2) ;
	Point searchPoint2Planes(const Plane& pl1) ;

	std::vector<Line> Points2ParallPlane(const Plane& p1, const Plane& p2) ;
	Line FindLine2same(const Plane& p1, const Plane& p2) ;

	std::vector<Line> Find4Lines(const Plane& p1, const Plane& p2) ;




	double getA() const { return A; }
	double getB() const { return B; } //геттеры
	double getC() const { return C; }
	double getD() const { return D; }

	~Plane() {} //деструктор
};

