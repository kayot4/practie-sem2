#include <iostream>
#include <cmath>
#include <vector>
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

double VectorNormali::operator*(const Plane& pl) {
	double scal;
	scal = A * pl.getA() + B * pl.getB() + C * pl.getC();
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



Point Plane::FindCoordPoint(const Plane& pl1, const Plane& pl2) {
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

	return Point( (matr[0][3]/matr[0][0]) -((matr[0][1]* matr[1][3])/ (matr[0][0]* matr[1][1])), (matr[1][3]/ matr[1][1]), 0);  //обойти деление на 0((

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

std::vector<Point> Plane::Points2ParallPlane( const Plane& pl1,const Plane& pl2) {
	Plane hl;
	Plane pp;
	if (pl1.isParallel(pl2)) {
		hl = pl1.MiddlPlane(pl2);
		pp = *this;
	}
	else if ((*this).isParallel(pl2)) {
		hl = (*this).MiddlPlane(pl2);
		pp = pl1;
	}
	else {
		hl = (*this).MiddlPlane(pl1);
		pp = pl2;
	}
	


}
