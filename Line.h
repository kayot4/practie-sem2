#pragma once
#include "Point.h"
#include "vec.h"
#include <iostream> 


class Line {
private:
	Point point;
	vec vector;
public:
	Line() : point(), vector() {}
	Line(const Point& p, const vec& v) : point(p), vector(v) {}
	~Line() {}


	bool isSame(const Line& l) const;


	double getX0() const { return point.getX0(); }
	double getY0() const { return point.getY0(); }
	double getZ0() const { return point.getZ0(); }
	double getA() const { return vector.getA(); }
	double getB() const { return vector.getB(); }
	double getC() const { return vector.getC(); }


	friend std::ostream& operator<<(std::ostream& str, const Line& line);
};