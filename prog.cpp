#include "Plane.h"
#include <cmath>
#include <vector>
#include <iostream>
bool Plane::isParallel(Plane pl) {
	if (A * pl.B == B * pl.A && A * pl.C == C * pl.A && B * pl.D != D * pl.B) {
		return true;
	}
	else {
		return false;
	}
}

bool Plane::isSame(Plane pl) {
	if (A * pl.B == B * pl.A && C * pl.D == D * pl.C && C * pl.B == B * pl.C) {
		return true;
	}
	else {
		return false;
	}
}
bool Plane::only2Parallel(Plane pl1,  Plane pl2) {
	bool this_pl1 = (*this).isParallel(pl1);
	bool this_pl2 = (*this).isParallel(pl2);
	bool pl1_pl2 = pl1.isParallel(pl2);
	return (this_pl1 && !this_pl2 && !pl1_pl2) || (this_pl2 && !this_pl1 && !pl1_pl2) || (pl1_pl2 && !this_pl1 && !this_pl2);
}
bool Plane::isPerpendicular(Plane pl1) {
	VectorNormali vector1(A, B, C);
	VectorNormali vector2(pl1.A, pl1.B, pl1.C);
	double eps = 2.2e-16;
	if (std::fabs(vector1*vector2) < eps) {
		return true;
	}
	else {
		return false;
	}

}

bool Plane::BissPlanesPerpParal(Plane pl1, Plane pl2) {
	std::vector<Plane> bissectorsThisPl1 = (*this).BissPlane(pl1);
	if (bissectorsThisPl1[0].isParallel(pl2) && bissectorsThisPl1[1].isPerpendicular(pl2) || bissectorsThisPl1[0].isPerpendicular(pl2) && bissectorsThisPl1[1].isParallel(pl2)) {
		return true;
	}

	std::vector<Plane> bissectorsThisPl2 = (*this).BissPlane(pl2);
	if (bissectorsThisPl2[0].isParallel(pl1) && bissectorsThisPl2[1].isPerpendicular(pl1) || bissectorsThisPl2[0].isPerpendicular(pl1) && bissectorsThisPl2[1].isParallel(pl1)) {
		return true;
	}

	std::vector<Plane> bissectorsPl2Pl1 = (pl2).BissPlane(pl1);
	if (bissectorsPl2Pl1[0].isParallel(*this) && bissectorsPl2Pl1[1].isPerpendicular(*this) || bissectorsPl2Pl1[0].isPerpendicular(*this) && bissectorsPl2Pl1[1].isParallel(*this)) {
		return true;
	}
	return false;
}



double VectorNormali::operator*(const Plane& pl) {
	double scal;
	scal = A * pl.getA() + B * pl.getB() + C * pl.getC();
	return scal;
}
double VectorNormali::operator*(const VectorNormali& vec) {
	double scal;
	scal = A * vec.getA() + B *vec.getB() + C * vec.getC();
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

void Plane::normalize() {
	double norm = std::sqrt(A * A + B * B + C * C);
	if (norm != 0) {
		A /= norm;
		B /= norm;
		C /= norm;
		D /= norm;
	}
}

double Plane::Distance(const Point& p) {
	return  (std::fabs(A * p.getX0() + B * p.getY0() + C * p.getZ0() + D)) / (std::sqrt(A * A + B * B + C * C));
}



int Plane::RangRash(const Plane& pl1, const Plane& pl2) {
	std::vector<std::vector <double>> matr{
		{A, B, C, D},
		{pl1.A, pl1.B, pl1.C, pl1.D},
		{pl2.A, pl2.B, pl2.C, pl2.D}
	};
	int rows = 3;
	int cols = 4;
	int rang = 0;
	double eps = 2.2e-16;

	for (int col = 0; col < cols && rang<rows; ++col) { //идем по столбцам

		int RowMax = rang;
		double maxval = std::fabs(matr[rang][col]); //максимальный за диагональный берется

		for (int i = rang + 1; i < rows; ++i) {
			if (std::fabs(matr[i][col]) > maxval){
				maxval = std::fabs(matr[i][col]);  //наибольший по модулю элемент в столбце
				RowMax = i;
			}
		}

		if (maxval < eps) {
			continue;   //если все нули будут, то скипаем столбец
		}

		if (RowMax != rang) {
			std::swap(matr[RowMax], matr[rang]);  //тут меняем строки
		}

		for (int i = rang + 1; i < rows; ++i) {
			double factor = matr[i][col] / matr[rang][col]; // ну типо множитель считаем

			for (int j = col; j < cols; ++j) {
				matr[i][j] -= factor * matr[rang][j];  //вычитание по строке
			}
		}
		++rang;
	}
	return rang;
}
int Plane::RangCas(const Plane& pl1, const Plane& pl2) {
	std::vector<std::vector <double>> matr{
		{A, B, C},
		{pl1.A, pl1.B, pl1.C},
		{pl2.A, pl2.B, pl2.C}
	};
	int rows = 3;
	int cols = 3;
	int rang = 0;
	double eps = 2.2e-16;
	for (int col = 0; col < cols && rang < rows; ++col) {

		int RowMax = rang;
		double maxval = std::fabs(matr[rang][col]);

		for (int i = rang + 1; i < rows; ++i) {
			if (std::fabs(matr[i][col]) > maxval) {
				maxval = std::fabs(matr[i][col]);
				RowMax = i;
			}
		}

		if (maxval < eps) {
			continue;
		}

		if (RowMax != rang) {
			std::swap(matr[RowMax], matr[rang]);
		}

		for (int i = rang + 1; i < rows; ++i) {
			double factor = matr[i][col] / matr[rang][col];
			for (int j = col; j < cols; ++j) {
				matr[i][j] -= factor * matr[rang][j];
			}
		}
		++rang;
	}
	return rang;
}


Plane Plane::MiddlPlane(const Plane& pl) {
	Plane middlPlane;
	middlPlane.A = A;
	middlPlane.B = B;
	middlPlane.C = C;
	middlPlane.D = (D+pl.D)/2;
	return middlPlane;
}



std::vector<Plane> Plane::BissPlane(const Plane& pl) {
	std::vector<Plane> bissPlane;
	Plane our_norm = *this;
	Plane pl_norm = pl;

	our_norm.normalize();
	pl_norm.normalize();

	bissPlane.push_back(Plane(our_norm.A + pl_norm.A, our_norm.B + pl_norm.B, our_norm.C + pl_norm.C, our_norm.D + pl_norm.D));
	bissPlane.push_back(Plane(our_norm.A - pl_norm.A, our_norm.B - pl_norm.B, our_norm.C - pl_norm.C, our_norm.D - pl_norm.D));

	return bissPlane;
}



Line Plane::FindLine3peres1line(const Plane& pl1, const Plane& pl2) {
	std::vector<std::vector <double>> matr{
		{A, B, C, D},
		{pl1.A, pl1.B, pl1.C, pl1.D},
		{pl2.A, pl2.B, pl2.C, pl2.D}
	};
	int rows = 3;
	int cols = 4;
	int rang = 0;
	double eps = 2.2e-16;

	for (int col = 0; col < cols && rang < rows; ++col) { //идем по столбцам

		int RowMax = rang;
		double maxval = std::fabs(matr[rang][col]); //максимальный за диагональный берется

		for (int i = rang + 1; i < rows; ++i) {
			if (std::fabs(matr[i][col]) > maxval) {
				maxval = std::fabs(matr[i][col]);  //наибольший по модулю элемент в столбце
				RowMax = i;
			}
		}

		if (maxval < eps) {
			continue;   //если все нули будут, то скипаем столбец
		}

		if (RowMax != rang) {
			std::swap(matr[RowMax], matr[rang]);  //тут меняем строки
		}

		for (int i = rang + 1; i < rows; ++i) {
			double factor = matr[i][col] / matr[rang][col]; // ну типо множитель считаем

			for (int j = col; j < cols; ++j) {
				matr[i][j] -= factor * matr[rang][j];  //вычитание по строке
			}
		}
		++rang;
	}
	Point point((matr[0][3] / matr[0][0]) - ((matr[0][1] * matr[1][3]) / (matr[0][0] * matr[1][1])), (matr[1][3] / matr[1][1]), 0);
	VectorNormali vectornorm(A,B,C);
	VectorNormali vectornormpl1(pl1.A, pl1.B, pl1.C);
	VectorNormali vectorRes = vectornorm ^ vectornormpl1;
	Line line(point, vectorRes);
	return line;
	//return Point( (matr[0][3]/matr[0][0]) -((matr[0][1]* matr[1][3])/ (matr[0][0]* matr[1][1])), (matr[1][3]/ matr[1][1]), 0);  //обойти деление на 0((

}

double determinat2x2(double a, double b, double c, double d) {
	return (a * d) - (b * c);
}

Point Plane::searchPoint2Planes(const Plane& pl1) {
	
	double Det = determinat2x2(A, B, pl1.A, pl1.B);
	double Det1 = determinat2x2(D, B, pl1.D, pl1.B);
	double Det2 = determinat2x2(A, D, pl1.A, pl1.D);

	return Point(Det1/Det ,Det2/Det , 0);
}

std::vector<Line> Plane::Points2ParallPlane( Plane pl1, Plane pl2) {
	Plane hl;
	Plane pp;
	double minuser;
	if (pl1.isParallel(pl2)) {
		hl = pl1.MiddlPlane(pl2);
		minuser = pl1.D - pl2.D;
		pp = *this;
	}
	else if ((*this).isParallel(pl2)) {
		hl = (*this).MiddlPlane(pl2);
		minuser = D - pl2.D;
		pp = pl1;
	}
	else {
		hl = (*this).MiddlPlane(pl1);
		minuser = D - pl1.D;
		pp = pl2;
	}
	
	double c1 = (minuser* std::sqrt(pp.A*pp.A + pp.B*pp.B + pp.C*pp.C))/(2*std::sqrt(hl.A * hl.A + hl.B * hl.B + hl.C * hl.C));
	double c2 = (-minuser * std::sqrt(pp.A * pp.A + pp.B * pp.B + pp.C * pp.C)) / (2 * std::sqrt(hl.A * hl.A + hl.B * hl.B + hl.C * hl.C));

	Plane pp1, pp2;
	pp1 = pp;
	pp2 = pp;
	pp1.D -= c1;
	pp2.D -= c2;

	Point point1 = pp1.searchPoint2Planes(hl);
	Point point2 = pp2.searchPoint2Planes(hl);

	std::vector<Line> result;
	VectorNormali vectornorm_pp(pp.A, pp.B, pp.C);
	VectorNormali vectornorm_hl(hl.A, hl.B, hl.C);
	VectorNormali vectornorm = vectornorm_pp ^ vectornorm_hl;
	Line line1(point1, vectornorm);
	Line line2(point2, vectornorm);
	result.push_back(line1);
	result.push_back(line2);

	
	return result;
}


Line Plane::FindLine2same(Plane pl1, Plane pl2) {
	Plane hl;
	Plane pp;
	if (pl1.isSame(pl2)) {
		hl = pl1;
		pp = *this;
	}
	else if ((*this).isSame(pl2)) {
		hl = *this;
		pp = pl1;
	}
	else {
		hl = *this;
		pp = pl2;
	}
	VectorNormali vectornorm_pp(pp.A, pp.B, pp.C);
	VectorNormali vectornorm_hl(hl.A, hl.B, hl.C);
	VectorNormali vectornorm = vectornorm_pp ^ vectornorm_hl;

	Point point = pp.searchPoint2Planes(hl);
	Line line(point, vectornorm);

	return line;
}


std::ostream& operator<<(std::ostream& str, const Line& line) {
	str << line.getX0() << " " << line.getY0() << " " << line.getX0() << std::endl;
	str << line.getA() << " " << line.getB() << " " << line.getC() << std::endl;
	return str;
}
