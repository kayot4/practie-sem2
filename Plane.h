#pragma once
#include <iostream>
#include "vec.h"


class Plane
{
private:
	double A;
	double B;
	double C;	
	double D;
public:
	Plane() : A(0), B(0), C(0), D(0){}
	Plane(double A_, double B_, double C_, double D_) : A(A_), B(B_), C(C_), D(D_) {} //инициал
	bool isSame(const Plane& pl) ;
	bool isParallel(const Plane& pl);
	Plane MidPlane(const Plane& P);

	void normalize();

	double getA() const;
	double getB() const;
	double getC() const;
	double getD() const;	
	vec getVecNorm() const;
	bool operator==(const Plane& pl);
	friend std::ostream& operator<<(std::ostream& str, const Plane& pl);
};

