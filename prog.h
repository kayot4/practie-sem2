#pragma once
#include <vector>

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

	bool isSame(Plane pl) {};//совп
	bool isParallel(Plane pl) {}; // паралелл

	double Distance(const Point& p) {};
	int RangRash(const Plane& pl1, const Plane& pl2) {};
	int RangCas(const Plane& pl1, const Plane& pl2) {};
	Plane MiddlPlane(const Plane& pl) {};
	void normalize() {};
	std::vector<Plane> BissPlane(const Plane& pl) {};
	Point FindCoordPoint(const Plane& pl1, const Plane& pl2) {};
	Point searchPoint2Planes(const Plane& pl1) {};
	std::vector<Point> Points2ParallPlane(const Plane& pl1, const Plane& pl2) {};

	double getA() const { return A; }
	double getB() const { return B; } //геттеры
	double getC() const { return C; }
	double getD() const { return D; }

	~Plane() {} //деструктор
};


class Point {
private:
	double x0;
	double y0;
	double z0;
public:
	Point() : x0(0), y0(0), z0(0) {}
	Point(double x0_, double y0_, double z0_) : x0(x0_), y0(y0_), z0(z0_) {}

	double getX0() const { return x0; }
	double getY0() const { return y0; } //геттеры
	double getZ0() const { return z0; }

};
class VectorNormali {
private:
	double A;
	double B;
	double C;
public:
	VectorNormali() : A(0), B(0), C(0) {} //по умолчан
	VectorNormali(double A_, double B_, double C_) : A(A_), B(B_), C(C_){} //инициал

	double operator*(const Plane& pl) {};//скаляр
	VectorNormali operator^(const VectorNormali& pl) {};//векторн

	double getA() const { return A; }
	double getB() const { return B; } //геттеры
	double getC() const { return C; }

	~VectorNormali() {}

};
#pragma once
#include <vector>

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

	bool isSame(Plane pl) {};//совп
	bool isParallel(Plane pl) {}; // паралелл

	double Distance(const Point& p) {};
	int RangRash(const Plane& pl1, const Plane& pl2) {};
	int RangCas(const Plane& pl1, const Plane& pl2) {};
	Plane MiddlPlane(const Plane& pl) {};
	void normalize() {};
	std::vector<Plane> BissPlane(const Plane& pl) {};
	Point FindCoordPoint(const Plane& pl1, const Plane& pl2) {};
	Point searchPoint2Planes(const Plane& pl1) {};
	std::vector<Point> Points2ParallPlane(const Plane& pl1, const Plane& pl2) {};

	double getA() const { return A; }
	double getB() const { return B; } //геттеры
	double getC() const { return C; }
	double getD() const { return D; }

	~Plane() {} //деструктор
};


class Point {
private:
	double x0;
	double y0;
	double z0;
public:
	Point() : x0(0), y0(0), z0(0) {}
	Point(double x0_, double y0_, double z0_) : x0(x0_), y0(y0_), z0(z0_) {}

	double getX0() const { return x0; }
	double getY0() const { return y0; } //геттеры
	double getZ0() const { return z0; }

};
class VectorNormali {
private:
	double A;
	double B;
	double C;
public:
	VectorNormali() : A(0), B(0), C(0) {} //по умолчан
	VectorNormali(double A_, double B_, double C_) : A(A_), B(B_), C(C_){} //инициал

	double operator*(const Plane& pl) {};//скаляр
	VectorNormali operator^(const VectorNormali& pl) {};//векторн

	double getA() const { return A; }
	double getB() const { return B; } //геттеры
	double getC() const { return C; }

	~VectorNormali() {}

};

