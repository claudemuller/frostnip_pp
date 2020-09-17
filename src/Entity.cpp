#include <iostream>
#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"

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

void Entity::addComponentsFromScript(sol::table components) {
	sol::table component;

	if (components["transform"] != sol::nullopt) {
		component = components["transform"];
		int posX = static_cast<int>(component["position"]["x"]);
		int posY = static_cast<int>(component["position"]["y"]);
		int velX = static_cast<int>(component["velocity"]["x"]);
		int velY = static_cast<int>(component["velocity"]["y"]);
		int width = static_cast<int>(component["width"]);
		int height = static_cast<int>(component["height"]);
		int scale = static_cast<int>(component["scale"]);

		addComponent<TransformComponent>(posX, posY, velX, velY, width, height, scale);
	}

	if (components["sprite"] != sol::nullopt) {
		component = components["sprite"];
		std::string textureAssetId = component["textureAssetId"];
		bool isAnimated = static_cast<bool>(component["animated"]);
		if (isAnimated) {
			int numFrames = static_cast<int>(component["frameCount"]);
			int animationSpeed = static_cast<int>(component["animationSpeed"]);
			bool hasDirections = static_cast<int>(component["hasDirections"]);
			bool isFixed = static_cast<int>(component["fixed"]);

			addComponent<SpriteComponent>(textureAssetId.c_str(), numFrames, animationSpeed, hasDirections, isFixed);
		} else {
			addComponent<SpriteComponent>(textureAssetId.c_str());
		}
	}

	if (components["input"] != sol::nullopt) {
		component = components["input"]["keyboard"];
		if (components["input"]["keyboard"] != sol::nullopt) {
			sol::table keyboardInput = components["input"]["keyboard"];
			std::string upKey = keyboardInput["up"];
			std::string downKey = keyboardInput["down"];
			std::string leftKey = keyboardInput["left"];
			std::string rightKey = keyboardInput["right"];
			std::string shootKey = keyboardInput["shoot"];

			addComponent<KeyboardControlComponent>(upKey, rightKey, downKey, leftKey, shootKey);
		}
	}

	if (components["collider"] != sol::nullopt) {
		component = components["collider"];
	}

	if (components["projectileEmitter"] != sol::nullopt) {
		component = components["projectileEmitter"];
	}
}