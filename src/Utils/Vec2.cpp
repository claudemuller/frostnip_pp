#include <math.h>
#include "Vec2.h"
#include "Utils.h"

const Vec2 Vec2::Zero;

std::ostream& operator<<(std::ostream& consoleOut, const Vec2& vec) {
	consoleOut << "friend-> x: " << vec.x << " y: " << vec.y << std::endl;
	return consoleOut;
}

bool Vec2::operator==(const Vec2& vec2) const {
	return isEqual(x, vec2.x) && isEqual(y, vec2.y);
}

bool Vec2::operator!=(const Vec2& vec2) const {
	return !(*this == vec2);
}

Vec2 Vec2::operator-() const {
	return Vec2(-x, -y);
}

Vec2 Vec2::operator*(float scale) const {
	return Vec2(x * scale, y * scale);
}

Vec2 Vec2::operator/(float scale) const {
	assert(fabsf(scale) > EPSILON);
	return Vec2(x / scale, y / scale);
}

Vec2 Vec2::operator+(const Vec2& vec) const {
	return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator-(const Vec2& vec) const {
	return Vec2(x - vec.x, y - vec.y);
}

Vec2& Vec2::operator+=(const Vec2& vec) {
	*this = *this + vec;
	return *this; // So that can chain.
}

Vec2& Vec2::operator-=(const Vec2& vec) {
	*this = *this - vec;
	return *this; // So that can chain.
}

Vec2& Vec2::operator*=(float scale) {
	*this = *this * scale;
	return *this; // So that can chain.
}

Vec2& Vec2::operator/=(float scale) {
	assert(fabsf(scale) > EPSILON);
	*this = *this / scale;
	return *this; // So that can chain.
}

float Vec2::mag2() const {
	return x * x + y * y;
}

float Vec2::mag() const {
	return sqrt(mag2());
}

Vec2 operator*(float scalar, const Vec2& vec) {
	return vec * scalar;
}
