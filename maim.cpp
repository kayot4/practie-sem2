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
		std::cout << "Infinite number of lines" << std::endl; //3 совпадают
	}
	if (rangRash == 2 && rangCas == 1) {
		if (plane[0].Same2Parallel1(plane[1], plane[2])) {
			std::cout << "Infinite number of lines" << std::endl; // 2 совпа, другая параллельна
		}
		else {
			std::cout << "0 lines" << std::endl; // 3параллельны
		} 
	}
	if (rangRash == 3 && rangCas == 2) {
		if (plane[0].only2Parallel(plane[1], plane[2])) {
			std::vector<Line> lines = plane[0].Points2ParallPlane(plane[1], plane[2]); //2 парарллельны, одна пересекает
			std::cout << "2" << std::endl;
			std::cout << lines[0] << std::endl;
			std::cout << lines[1] << std::endl;
		}
		else { //3 плоскости не имеют общую точку

		}
	}
	if ( rangRash == 2 && rangCas == 2 ) {
		if (plane[0].Same2Peresec1Perp(plane[1], plane[2])) {
			std::cout << "Infinite number of lines" << std::endl;//2 совпадают 1 пересекает 
		}
		else if(plane[0].Same2Peresec1(plane[1], plane[2])) {
			Line line = plane[0].FindLine2same(plane[1], plane[2]);
			std::cout << " 1 " << std::endl;
			std::cout << line << std::endl;
		}
		else if (plane[0].BissPlanesPerpParal(plane[1], plane[2])) {
			std::cout << "Infinite number of lines" << std::endl; //3 пересекаются по одной прямой, но биссекторные плоскостии параллельны или перпендикулярны
		}
		else {
			std::cout << "1" << std::endl;
			Line line = plane[0].FindLine3peres1line(plane[1], plane[2]); //3 по одной прямой, но биссекторная не прпендикулряна и не праалеллльвдаджважэыдв
			std::cout << line;
		}
		
	}
	if (rangRash == 3 && rangCas == 3) {
		//3  плоскости имеют одну общую точку
	}
	
	
}
