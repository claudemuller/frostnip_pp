#ifndef FROSTBYTE_TRANSFORMCOMPONENT_H
#define FROSTBYTE_TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include "../Utils/Vec2.h"
#include "../Game.h"

class TransformComponent : public Component {
public:
	Vec2 position;
	Vec2 velocity;
	int width;
	int height;
	int scale;
	int speed;

	TransformComponent(int x, int y, int velX, int velY, int w, int h, int s, int sp = 0);

	void init() override;
	void update(float deltaTime) override;
	void render() override;
};

#endif //FROSTBYTE_TRANSFORMCOMPONENT_H
