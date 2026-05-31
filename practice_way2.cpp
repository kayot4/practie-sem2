#include <iostream>
#include <vector>
#include <set>
#include "Plane.h"
#include "vec.h"
#include "Point.h"
#include "Line.h"

struct MatrWRang {
	std::vector<std::vector <double>> matr;
	int rang;
	MatrWRang() :matr(), rang(0){}
	MatrWRang(std::vector<std::vector<double>> matr_, int rang_) : matr(matr_), rang(rang_) {}
};

std::vector<Plane> BissPlanes(Plane P1, Plane P2) {
    std::vector<Plane> res;
	if (P1.isParallel(P2)) {
		double k = P1.getA() / P2.getA();
		double p2d= P2.getD() * k; 
		Plane biss = Plane(P1.getA(), P1.getB(), P1.getC(), (P1.getD() + p2d) / 2);
		res.push_back(biss);
		return res;
	}

	double P1len = std::sqrt(P1.getA() * P1.getA() + P1.getB() * P1.getB() + P1.getC() * P1.getC());
	double P2len = std::sqrt(P2.getA() * P2.getA() + P2.getB() * P2.getB() + P2.getC() * P2.getC());
	double k = P1len / P2len;

    /*P1.normalize();
    P2.normalize();*/
    res.push_back(Plane(P1.getA() + k * P2.getA(), P1.getB() + k * P2.getB(), P1.getC() + k * P2.getC(), P1.getD() + k * P2.getD()));
    res.push_back(Plane(P1.getA() - k * P2.getA(), P1.getB() - k * P2.getB(), P1.getC() - k * P2.getC(), P1.getD() - k * P2.getD()));
    return res;
}
MatrWRang RangM(const Plane pl1, const Plane pl2, const Plane pl3) {
	std::vector<std::vector <double>> matr{
		{pl1.getA(), pl1.getB(), pl1.getC()},
		{pl2.getA(), pl2.getB(), pl2.getC()},
		{pl3.getA(), pl3.getB(), pl3.getC()}
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

	MatrWRang res = MatrWRang(matr, rang);
	return res;
}


MatrWRang RangR(const Plane pl1, const Plane pl2, const Plane pl3) {

	std::vector<std::vector <double>> matr{
		{pl1.getA(), pl1.getB(), pl1.getC(), pl1.getD()},
		{pl2.getA(), pl2.getB(), pl2.getC(), pl2.getD()},
		{pl3.getA(), pl3.getB(), pl3.getC(), pl3.getD()}
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
				matr[i]
					[j] -= factor * matr[rang][j];  //вычитание по строке
			}
		}
		++rang;
	}

	/*std::cout << matr[0][0] << " " << matr[0][1] << " " << matr[0][2] << " " << matr[0][3] << std::endl;
	std::cout << matr[1][0] << " " << matr[1][1] << " " << matr[1][2] << " " << matr[1][3] << std::endl;
	std::cout << matr[2][0] << " " << matr[2][1] << " " << matr[2][2] << " " << matr[2][3] << std::endl;*/

	MatrWRang res = MatrWRang(matr, rang);
	return res;
}


Point solveSYS(std::vector<std::vector<double>>& sys, bool& f) {
	double eps = 2.2e-16;
	double y = 0.0;
	// y - свободная переменная, будем всегда брать за 0
					// система имеет вид:
					//a1x + c1z = -d1 
					//a2x + c2z = -d2      решим крамером
	double a1 = sys[0][0], c1 = sys[0][2], f1 = - sys[0][3];
	double a2 = sys[1][0], c2 = sys[1][2], f2 = - sys[1][3];
	double det = a1 * c2 - c1 * a2;
	/*if (std::fabs(det) < eps) {
		f = true;
		Point p = Point(0, 0, 0);
		return p;
	};*/
	double d1 = f1 * c2 - c1 * f2;
	double d2 = a1 * f2 - f1 * a2;
	double x = d1 / det;
	double z = d2 / det;

	//if (std::fabs(x - std::round(x)) < eps) { // обработка погрешностей вычислений 
	//	x = std::round(x);
	//}
	//if (std::fabs(z - std::round(z)) < eps) {
	//	z = std::round(z);
	//}
	Point ans = Point(x, y, z);
	return ans;
}

Point solveSYS1(std::vector<std::vector<double>>& matr) {
	double eps = 2.2e-16;
	double z = 0.0;
	double y, x;
	if (fabs(matr[1][1]) < eps) y = 0; //коэф при y = 0 => можем брать любой y и берем y = 0 
	else  y = -(matr[1][3] / matr[1][1]);

	if (fabs(matr[0][0]) < eps) x = 0;
	else x = -( (matr[0][3]+matr[0][1]*y) / matr[0][0] );
	std::cout << "P0: " << x << " " << y << " " << z << std::endl;
	return Point(x, y, z);
	
}




int main()
{
    std::vector<Plane> planes(3); // вектор исходных плоскостей
    for (int i = 0; i < 3; ++i) {
        double A, B, C, D;
        std::cin >> A >> B >> C >> D;
        planes[i] = Plane(A, B, C, D);
    }
	std::cout << "----------------------------------------" << std::endl;


    std::vector<Plane> biss12 = BissPlanes(planes[0], planes[1]);

	for (auto& i : biss12) {
		std::cout << i << std::endl;
	}
	std::cout << "----------------------------------------" << std::endl;


    std::vector<Plane> biss13 = BissPlanes(planes[0], planes[2]);

	for (auto& i : biss13) {
		std::cout << i << std::endl;
	}



	std::cout << "----------------------------------------" << std::endl;


    std::vector<Plane> biss23 = BissPlanes(planes[1], planes[2]);
	for (auto& i : biss23) {
		std::cout << i << std::endl;
	}

	std::cout << "----------------------------------------" << std::endl;


	/*std::vector<Line> ans;

    for (auto& i : biss12) {
        for (auto& j : biss13) {
            for (auto& k : biss23) {
				MatrWRang M = RangM(i, j, k);
				MatrWRang MR = RangR(i, j, k);
				if (M.rang == 2 && MR.rang == 2) { // три плоскости пересекаются по прямой, т.е. на самом деле 3 плоскости превратились в две в системе, а две плоскости пересекаются по прямой.
					std::vector<std::vector<double>> sys = MR.matr;	//функция подсчёта ранга теперь возвращает и итоговую систему в супенчатом виде
					for (int i = 0; i < 3; ++i) {
						for (int j = 0; j < 4; ++j) {
							std::cout << sys[i][j] << " ";
						}
						std::cout << std::endl;
					}
					//bool flag = false;
					//Point P0 = solveSYS(sys, flag);
					//if (flag) continue;
					Point P0 = solveSYS1(sys);
					vec vN1 = vec(MR.matr[0][0], MR.matr[0][1], MR.matr[0][2]); //вектор нормали 1 плоскости из ситсемы после нахождения ранга
					vec vN2 = vec(MR.matr[1][0], MR.matr[1][1], MR.matr[1][2]); //вектор нормали 2 плоскости из ситсемы после нахождения ранга
					vec dir = vN1 ^ vN2;
					Line l = Line(P0, dir);
					ans.push_back(l);
					std::cout << "----------------------------------------" << std::endl;
				}
            }
        }
    }

	std::cout << ans.size() << std::endl;
	for (Line i : ans) {
		std::cout << i << std::endl;
	}*/
	//std::cout << -1 * 0;
}


