#pragma once
#include "Line.h"
#include <iostream>
std::ostream& operator<<(std::ostream& str, const Line& line) {
	str << line.getX0() << " " << line.getY0() << " " << line.getZ0() << std::endl;
	str << line.getA() << " " << line.getB() << " " << line.getC() << std::endl;
	return str;
}