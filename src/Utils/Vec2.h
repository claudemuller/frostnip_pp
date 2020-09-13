#ifndef FROSTNIP_PP_VEC2D_H
#define FROSTNIP_PP_VEC2D_H

#include <iostream>

class Vec2 {
public:
	static const Vec2 Zero;

	Vec2() : Vec2(0, 0) {}
	Vec2(float x, float y) : x(x), y(y) {}

	inline void setX(float x) { this->x = x; }
	inline void setY(float y) { this->y = y; }
	inline float getX() { return x; }
	inline float getY() { return y; }

	void display() const {
		std::cout << "x: " << x << " y: " << y << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& consoleOut, const Vec2& vec);

	bool operator==(const Vec2& vec2) const;
	bool operator!=(const Vec2& vec2) const;

	Vec2 operator-() const;

	Vec2 operator+(const Vec2& vec) const;
	Vec2 operator-(const Vec2& vec) const;
	Vec2 operator*(float scale) const;
	Vec2 operator/(float scale) const;

	Vec2& operator+=(const Vec2& vec);
	Vec2& operator-=(const Vec2& vec);
	Vec2& operator*=(float scale);
	Vec2& operator/=(float scale);

	float mag2() const;
	float mag() const;

	Vec2 getUnitVec() const;

	friend Vec2 operator*(float scalar, const Vec2& vec);

private:
	float x;
	float y;
};

#endif //FROSTNIP_PP_VEC2D_H
