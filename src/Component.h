#ifndef FROSTNIP_PP_COMPONENT_H
#define FROSTNIP_PP_COMPONENT_H

class Entity;

class Component {
public:
	Entity* owner;

	virtual void init() {};
	virtual void update(float deltaTime) {};
	virtual void render() {};
};

#endif //FROSTNIP_PP_COMPONENT_H
