#ifndef FROSTBYTE_COLLIDERCOMPONENT_H
#define FROSTBYTE_COLLIDERCOMPONENT_H

#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"

class ColliderComponent : public Component {
public:
	std::string tag;
	SDL_Rect collider;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	TransformComponent* transform;

	ColliderComponent(std::string tag, int x, int y, int width, int height);

	void init() override;
	void update(float deltaTime) override;
	void render() override;
};

#endif //FROSTBYTE_COLLIDERCOMPONENT_H
