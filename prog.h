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
	bool only2Parallel( Plane pl1, Plane pl2) {};
	bool isPerpendicular(Plane pl1) {};
	bool BissPlanesPerpParal(Plane pl1, Plane pl2) {};

	double Distance(const Point& p) {};
	int RangRash(const Plane& pl1, const Plane& pl2) {};
	int RangCas(const Plane& pl1, const Plane& pl2) {};
	Plane MiddlPlane(const Plane& pl) {};
	void normalize() {};
	std::vector<Plane> BissPlane(const Plane& pl) {};
	Line FindLine3peres1line(const Plane& pl1, const Plane& pl2) {};
	Point searchPoint2Planes(const Plane& pl1) {};
	std::vector<Line> Points2ParallPlane(Plane pl1,Plane pl2) {};
	Line FindLine2same(Plane pl1, Plane pl2) {};






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
	double operator*(const VectorNormali& vec) {};
	VectorNormali operator^(const VectorNormali& pl) {};//векторн

	double getA() const { return A; }
	double getB() const { return B; } //геттеры
	double getC() const { return C; }

	~VectorNormali() {}

};


class Line {
private: 
	Point point;
	VectorNormali vector;
public:
	Line() : point(), vector() {}
	Line(const Point& p, const VectorNormali& v): point(p), vector(v) {}
	~Line() {}


    


	double getX0() const { return point.getX0(); }
	double getY0() const { return point.getY0(); }
	double getZ0() const { return point.getZ0(); }
	double getA() const { return vector.getA(); }
	double getB() const { return vector.getB(); }
	double getC() const { return vector.getC(); }


	friend std::ostream& operator<<(std::ostream& str, const Line& line);
};

