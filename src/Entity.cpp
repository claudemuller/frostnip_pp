#include <iostream>
#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/ProjectileEmitterComponent.h"

Entity::Entity(EntityManager& manager) : manager(manager) {
	active = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer) : manager(manager), name(name), layer(layer) {
	active = true;
}

void Entity::update(float deltaTime) {
	for (auto& component : components) {
		component->update(deltaTime);
	}
}

void Entity::render() {
	for (auto& component : components) {
		component->render();
	}
}

void Entity::destroy() {
	active = false;
}

void Entity::listComponents() {
	unsigned int i = 0;
	for (auto& componentType : componentTypeMap) {
		std::cout << "\t|_Component<" << componentType.first->name() << ">" << std::endl;
		i++;
	}
}

void Entity::addComponentsFromTable(sol::table components) {
	sol::table component;

	sol::optional<sol::table> transformComponentExists = components["transform"];
	if (transformComponentExists != sol::nullopt) {
		component = components["transform"];
		int posX = static_cast<int>(component["position"]["x"]);
		int posY = static_cast<int>(component["position"]["y"]);
		int velX = static_cast<int>(component["velocity"]["x"]);
		int velY = static_cast<int>(component["velocity"]["y"]);
		int width = static_cast<int>(component["width"]);
		int height = static_cast<int>(component["height"]);
		int scale = static_cast<int>(component["scale"]);
		int speed = static_cast<int>(component["speed"]);

		addComponent<TransformComponent>(posX, posY, velX, velY, width, height, scale, speed);
	}

	sol::optional<sol::table> spriteComponentExists = components["transform"];
	if (spriteComponentExists != sol::nullopt) {
		component = components["sprite"];
		std::string textureAssetId = component["textureAssetId"];
		bool isAnimated = static_cast<bool>(component["animated"]);
		if (isAnimated) {
			int numFrames = static_cast<int>(component["frameCount"]);
			int animationSpeed = static_cast<int>(component["animationSpeed"]);
			bool hasDirections = static_cast<bool>(component["hasDirections"]);
			bool isFixed = static_cast<bool>(component["fixed"]);

			addComponent<SpriteComponent>(textureAssetId.c_str(), numFrames, animationSpeed, hasDirections, isFixed);
		} else {
			addComponent<SpriteComponent>(textureAssetId.c_str());
		}
	}
//
	sol::optional<sol::table> inputComponentExists = components["input"];
	if (inputComponentExists != sol::nullopt) {
		sol::optional<sol::table> keyboardComponentExists = components["input"]["keyboard"];
		if (keyboardComponentExists != sol::nullopt) {
			component = components["input"]["keyboard"];
			std::string upKey = component["up"];
			std::string downKey = component["down"];
			std::string leftKey = component["left"];
			std::string rightKey = component["right"];
			std::string shootKey = component["shoot"];

			addComponent<KeyboardControlComponent>(upKey, downKey, rightKey, leftKey, shootKey);
		}
	}

	sol::optional<sol::table> colliderComponentExists = components["collider"];
	if (colliderComponentExists != sol::nullopt) {
		component = components["collider"];
		std::string colliderTag = component["tag"];
		//bool showBoundingBox = static_cast<bool>(component["debug"]);
		TransformComponent* transformComponent = getComponent<TransformComponent>();
		if (transformComponent != nullptr) {
			int x = transformComponent->position.getX();
			int y = transformComponent->position.getY();
			int width = transformComponent->width;
			int height = transformComponent->height;

			addComponent<ColliderComponent>(colliderTag, x, y, width, height);//, showBoundingBox);
		}
	}

	sol::optional<sol::table> projectileEmitterComponentExists = components["projectileEmitter"];
	if (projectileEmitterComponentExists != sol::nullopt) {
		component = components["projectileEmitter"];
		TransformComponent* transformComponent = getComponent<TransformComponent>();
		int parentX = transformComponent->position.getX();
		int parentY = transformComponent->position.getY();
		int parentWidth = transformComponent->width;
		int parentHeight = transformComponent->height;
		int projectileWidth = static_cast<int>(component["width"]);
		int projectileHeight = static_cast<int>(component["height"]);
		int projectileSpeed = static_cast<int>(component["speed"]);
		int projectileRange = static_cast<int>(component["range"]);
		int projectileAngle = static_cast<int>(component["angle"]);
		bool projectileShouldLoop = static_cast<bool>(component["shouldLoop"]);
		//bool showBoundingBox = static_cast<bool>(component["debug"]);
		std::string textureAssetId = component["textureAssetId"];

		Entity& projectile(manager.addEntity("projectile", PROJECTILE_LAYER));
		projectile.addComponent<TransformComponent>(
				parentX + (parentWidth / 2),
				parentY + (parentHeight / 2),
				0,
				0,
				projectileWidth,
				projectileHeight,
				1
		);
		projectile.addComponent<SpriteComponent>(textureAssetId.c_str());
		projectile.addComponent<ProjectileEmitterComponent>(
				projectileSpeed,
				projectileAngle,
				projectileRange,
				projectileShouldLoop
		);
		projectile.addComponent<ColliderComponent>(
				"projectile",
				parentX,
				parentY,
				projectileWidth,
				projectileHeight
		);
	}
}