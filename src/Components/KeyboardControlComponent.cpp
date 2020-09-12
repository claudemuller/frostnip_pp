#include "KeyboardControlComponent.h"

KeyboardControlComponent::KeyboardControlComponent(
		const std::string& upKey, const std::string& downKey, const std::string& rightKey,
		const std::string& leftKey, const std::string& shootKey) {
	this->upKey = getSDLKeyStringCode(upKey);
	this->downKey = getSDLKeyStringCode(downKey);
	this->rightKey = getSDLKeyStringCode(rightKey);
	this->leftKey = getSDLKeyStringCode(leftKey);
	this->shootKey = getSDLKeyStringCode(shootKey);
}

void KeyboardControlComponent::init() {
	transform = owner->getComponent<TransformComponent>();
	sprite = owner->getComponent<SpriteComponent>();
}

void KeyboardControlComponent::update(float deltaTime) {
	if (Game::event.type == SDL_KEYDOWN) {
		std::string keyCode = std::to_string(Game::event.key.keysym.sym);

		// TODO: fix this speed issue.
		int speed = transform->speed * 20;
		if (keyCode == upKey) {
			transform->velocity.setY(-speed);
			sprite->play("UpAnimation");
		}
		if (keyCode == rightKey) {
			transform->velocity.setX(speed);
			sprite->play("RightAnimation");
		}
		if (keyCode == downKey) {
			transform->velocity.setY(speed);
			sprite->play("DownAnimation");
		}
		if (keyCode == leftKey) {
			transform->velocity.setX(-speed);
			sprite->play("LeftAnimation");
		}
		if (keyCode == shootKey) {
		}
	}

	if (Game::event.type == SDL_KEYUP) {
		std::string keyCode = std::to_string(Game::event.key.keysym.sym);

		if (keyCode == upKey) {
			transform->velocity.setY(0);
		}
		if (keyCode == rightKey) {
			transform->velocity.setX(0);
		}
		if (keyCode == downKey) {
			transform->velocity.setY(0);
		}
		if (keyCode == leftKey) {
			transform->velocity.setX(0);
		}
	}
}
std::string KeyboardControlComponent::getSDLKeyStringCode(const std::string& key) {
	if (key == "up") return "1073741906";
	if (key == "down") return "1073741905";
	if (key == "left") return "1073741904";
	if (key == "right") return "1073741903";
	if (key == "space") return "32";
	return std::to_string(static_cast<int>(key[0]));
}
