#pragma once

class VectorNormali {
private:
	double A;
	double B;
	double C;
public:
	VectorNormali() : A(0), B(0), C(0) {} //по умолчан
	VectorNormali(double A_, double B_, double C_) : A(A_), B(B_), C(C_) {} //инициал

	double operator*(const VectorNormali& vec) ;
	VectorNormali operator^(const VectorNormali& pl) ;//векторн

	double getA() const { return A; }
	double getB() const { return B; } //геттеры
	double getC() const { return C; }

	~VectorNormali() {}

};
