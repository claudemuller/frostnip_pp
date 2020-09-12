#include "TransformComponent.h"

TransformComponent::TransformComponent(int x, int y, int velX, int velY, int w, int h, int s, int sp)
		: position(Vec2(x, y)), velocity(Vec2(velX, velY)), width(w), height(h), scale(s), speed(sp) {
}

void TransformComponent::init() {
}

void TransformComponent::update(float deltaTime) {
	position += velocity * deltaTime;
}

void TransformComponent::render() {
}
