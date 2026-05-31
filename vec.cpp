#pragma once
#include "vec.h"
#include <cmath>



double vec::operator*(const vec& v) {
	return this->A * v.getA() + this->B * v.getB() + this->C * v.getC();
}

vec vec::operator^(const vec& v) {
	vec res;
	double eps = 2.2e-16;
	res.A = this->B * v.getC() - this->C * v.getB();
	res.B = -(this->A * v.getC() - this->C * v.getA());
	res.C = this->A * v.getB() - this->B * v.getA();

	//if (std::fabs(res.A - std::round(res.A)) < eps) {
	//	res.A = std::round(res.A);
	//}
	//if (std::fabs(res.B - std::round(res.B)) < eps) { // обработка погрешностей вычислений 
	//	res.B = std::round(res.B);
	//}
	//if (std::fabs(res.C - std::round(res.C)) < eps) {
	//	res.C = std::round(res.C);
	//}
	return res;
}

void vec::normalize() {
	double eps = 2.2e-16;

	double len = std::sqrt(this->A * this->A + this->B * this->B + this->C * this->C);
	this->A = this->A * (1.0 / len);
	this->B = this->B * (1.0 / len);
	this->C = this->C * (1.0 / len);
	//if (std::fabs(this->A - std::round(this->A)) < eps) {
	//	this->A = std::round(this->A);
	//}
	//if (std::fabs(this->B - std::round(this->B)) < eps) { // обработка погрешностей вычислений 
	//	this->B = std::round(this->B);
	//}
	//if (std::fabs(this->C - std::round(this->C)) < eps) {
	//	this->C = std::round(this->C);
	//}
}

double vec::getA() const { return A; }
double vec::getB() const { return B; }
double vec::getC() const { return C; }

