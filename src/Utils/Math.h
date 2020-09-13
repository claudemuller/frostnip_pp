#ifndef FROSTBYTE_MATH_H
#define FROSTBYTE_MATH_H

#include <cmath>
#include "Vec2.h"

class Math {
public:
	static float radians(float degrees) {
		return degrees * M_PI / 180;
	}

	static float distance(Vec2 v1, Vec2 v2) {
		return sqrt(pow(v1.getX() - v2.getX(), 2) + pow(v1.getY() - v2.getY(), 2));
	}
};

#endif //FROSTBYTE_MATH_H
