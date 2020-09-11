#include <cmath>
#include "Utils.h"

bool isEqual(float x, float y) {
	return fabsf(x - y) < EPSILON;
}

bool isGreatThanOrEqual(float x, float y) {
	return x > y || isEqual(x, y);
}

bool isLessThanOrEqual(float x, float y) {
	return x < y || isEqual(x, y);
}

