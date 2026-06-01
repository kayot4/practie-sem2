#pragma once
#include "Plane.h"
#include <vector>
#include <cmath>

//bool Plane::isSame(const Plane& pl) {
//	if (A * pl.B == B * pl.A && C * pl.D == D * pl.C && C * pl.B == B * pl.C) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}


//bool Plane::isParallel(const Plane& pl) {
//	if (A * pl.B == B * pl.A && A * pl.C == C * pl.A && B * pl.D != D * pl.B) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

bool Plane::isParallel(const Plane& pl) {
	double eps = 2.2e-16;
	// Проверка коллинеарности нормалей: A1/A2 = B1/B2 = C1/C2
	bool normalsParallel = (fabs(A * pl.B - B * pl.A) < eps) && (fabs(A * pl.C - C * pl.A) < eps) && (fabs(B * pl.C - C * pl.B) < eps);

	if (!normalsParallel) {
		return false;
	}// Проверка, что плоскости не совпадают: пропорция D отличается
    // Если все коэффициенты пропорциональны включая D — плоскости совпадают
	bool coincident = (fabs(A * pl.D - D * pl.A) < eps) &&
		(fabs(B * pl.D - D * pl.B) < eps) &&
		(fabs(C * pl.D - D * pl.C) < eps);

	return !coincident;  // параллельны, но не совпадают
}

Plane Plane::MidPlane(const Plane& P){
	Plane res(this->A, this->B, this->C, (this->D + P.getD()) / 2);
	return res;
}

//bool Plane::isSame(const Plane& pl) {
//	double eps = 2.2e-16;
//
//	return isParallel(pl) &&
//		(fabs(A * pl.D - D * pl.A)< eps) &&
//		(fabs(B * pl.D - D * pl.B) < eps) &&
//		(fabs(C * pl.D - D * pl.C) < eps);
//}
bool Plane::isSame(const Plane& pl) {
	double eps = 2.2e-16;
	bool normalsParallel = (fabs(A * pl.B - B * pl.A) < eps) && (fabs(A * pl.C - C * pl.A) < eps) && (fabs(B * pl.C - C * pl.B) < eps);
	if (!normalsParallel) { return false; }
	bool coincident = (fabs(A * pl.D - D * pl.A) < eps) && (fabs(B * pl.D - D * pl.B) < eps) && (fabs(C * pl.D - D * pl.C) < eps);      return coincident;
}

void Plane::normalize() {
	double eps = 2.2e-16;

	double k = std::sqrt(this->A * this->A + this->B * this->B + this->C * this->C + this->D * this->D);
	this->A = this->A / k;
	this->B = this->B / k;
	this->C = this->C / k;
	this->D = this->D / k;
	//if (std::fabs(this->A - std::round(this->A)) < eps) {
	//	this->A = std::round(this->A);
	//}
	//if (std::fabs(this->B - std::round(this->B)) < eps) { // обработка погрешностей вычислений 
	//	this->B = std::round(this->B);
	//}
	//if (std::fabs(this->C - std::round(this->C)) < eps) {
	//	this->C = std::round(this->C);
	//}
	//if (std::fabs(this->D - std::round(this->D)) < eps) {
	//	this->D = std::round(this->D);
	//}
}

double Plane::getA() const { return this->A; }
double Plane::getB() const { return this->B; }
double Plane::getC() const { return this->C; }
double Plane::getD() const { return this->D; }
vec Plane::getVecNorm() const { vec vn(this->A, this->B, this->C); return vn; }

bool Plane::operator==(const Plane& pl) {
	if (A * pl.B == B * pl.A && C * pl.D == D * pl.C && C * pl.B == B * pl.C) return true;
	else return false;
}

std::ostream& operator<<(std::ostream& str, const Plane& pl) {
	str << pl.getA() << " " << pl.getB() << " " << pl.getC() << " " << pl.getD();
	return str;
}