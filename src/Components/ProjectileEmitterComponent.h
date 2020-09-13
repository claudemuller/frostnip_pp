#ifndef FROSTBYTE_PROJECTILEEMITTERCOMPONENT_H
#define FROSTBYTE_PROJECTILEEMITTERCOMPONENT_H

#include "../Utils/Vec2.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"

class ProjectileEmitterComponent : public Component {
public:
	ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop);

	void init() override;
	void update(float deltaTime) override;

private:
	TransformComponent* transform;
	Vec2 origin;
	int speed;
	int range;
	float angleRad;
	bool shouldLoop;
};

#endif //FROSTBYTE_PROJECTILEEMITTERCOMPONENT_H
