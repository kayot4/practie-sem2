#pragma once

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
