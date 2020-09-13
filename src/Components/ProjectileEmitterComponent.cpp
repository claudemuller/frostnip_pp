#include "../Utils/Math.h"
#include "ProjectileEmitterComponent.h"

ProjectileEmitterComponent::ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop)
		: speed(speed), range(range), shouldLoop(shouldLoop) {
	angleRad = Math::radians(static_cast<float>(angleDeg));
}
void ProjectileEmitterComponent::init() {
	transform = owner->getComponent<TransformComponent>();
	origin = Vec2(transform->position.getX(), transform->position.getY());
	transform->velocity = Vec2(cos(angleRad) * speed, sin(angleRad) * speed);
}

void ProjectileEmitterComponent::update(float deltaTime) {
	if (Math::distance(transform->position, origin) > range) {
		if (shouldLoop) {
			transform->position = origin;
		} else {
			owner->destroy();
		}
	}
}
