#ifndef FROSTBYTE_COMPONENT_H
#define FROSTBYTE_COMPONENT_H

class Entity;

class Component {
public:
	Entity* owner;

	virtual void init() {};
	virtual void update(float deltaTime) {};
	virtual void render() {};
};

#endif //FROSTBYTE_COMPONENT_H
