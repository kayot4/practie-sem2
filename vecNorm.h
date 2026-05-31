#pragma once



class vec {
private:
	double A;
	double B;
	double C;
public:
	vec() : A(0), B(0), C(0) {} //по умолчан
	vec(double A_, double B_, double C_) : A(A_), B(B_), C(C_) {} //инициал

	double operator*(const vecNorm& vec);
	vec operator^(const vecNorm& pl);//векторн
	void normalize();

	double getA() const;
	double getB() const;  //геттеры
	double getC() const;

	~vec() {}

};

