#ifndef FROSTBYTE_KEYBOARDCONTROLCOMPONENT_H
#define FROSTBYTE_KEYBOARDCONTROLCOMPONENT_H

#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/SpriteComponent.h"

class KeyboardControlComponent : public Component {
public:
	std::string upKey;
	std::string downKey;
	std::string rightKey;
	std::string leftKey;
	std::string shootKey;
	TransformComponent* transform;
	SpriteComponent* sprite;

	KeyboardControlComponent() {}
	KeyboardControlComponent(const std::string& upKey, const std::string& downKey, const std::string& rightKey,
	                         const std::string& leftKey, const std::string& shootKey);

	void init() override;
	void update(float deltaTime) override;
	std::string getSDLKeyStringCode(const std::string& key);

private:
};

#endif //FROSTBYTE_KEYBOARDCONTROLCOMPONENT_H
