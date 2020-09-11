#ifndef FROSTNIP_PP_TRANSFORMCOMPONENT_H
#define FROSTNIP_PP_TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include "../Vec2.h"

class TransformComponent : Component {
public:
	Vec2 position;
	Vec2 velocity;
	int width;
	int height;
	int scale;

	TransformComponent(int x, int y, int velX, int velY, int w, int h, int s);

	void init() override;
	void update(float deltaTime) override;
	void render() override;

private:
};

#endif //FROSTNIP_PP_TRANSFORMCOMPONENT_H
