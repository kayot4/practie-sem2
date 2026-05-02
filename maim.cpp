#include <iostream>
#include <vector>
#include "Plane.cpp"
#include "Plane.h"

int main()
{
	std::vector<Plane> plane(3);
	for (int i = 0; i < 3; ++i) {
		double A, B, C, D;
		std::cin >> A >> B >> C >> D;
		plane[i] = Plane(A, B, C, D);
	}

	int rangRash = plane[0].RangRash(plane[1], plane[2]);
	int rangCas = plane[0].RangCas(plane[1], plane[2]);
	if (rangRash == 1 && rangCas == 1) {
		std::cout << "Infinite number of lines" << std::endl;
	}

	if ( rangRash == 2 && rangCas == 2 ) {
		if  (plane[0].only2Parallel(plane[1], plane[2])) {
			std::vector<Line> lines = plane[0].Points2ParallPlane(plane[1], plane[2]);
			std::cout << "2" << std::endl;
			std::cout << lines[0] << std::endl;
			std::cout << lines[1];
		}
		else if (plane[0].BissPlanesPerpParal(plane[1], plane[2])) {
			std::cout << "Infinite number of lines" << std::endl;
		}
		else {
			std::cout << "1" << std::endl;
			Line line = plane[0].FindLine3peres1line(plane[1], plane[2]);
			std::cout << line;
		}
	}
}
