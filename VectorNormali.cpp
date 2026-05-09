#pragma once
#include "VectorNormali.h"
#include <cmath>




double VectorNormali::operator*(const VectorNormali& vec) {
	double scal;
	scal = A * vec.getA() + B * vec.getB() + C * vec.getC();
	return scal;
}


VectorNormali VectorNormali::operator^(const VectorNormali& vn) {
	VectorNormali hl;
	double eps = 2.2e-16;
	hl.A = B * vn.C - C * vn.B;
	hl.B = -(A * vn.C - C * vn.A);
	hl.C = A * vn.B - B * vn.A;
	if (std::fabs(hl.A) < eps) {
		hl.A = 0;
	}
	if (std::fabs(hl.B) < eps) {
		hl.B = 0;
	}
	if (std::fabs(hl.C) < eps) {
		hl.C = 0;
	}
	return hl;
}
