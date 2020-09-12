#ifndef FROSTNIP_PP_ANIMATION_H
#define FROSTNIP_PP_ANIMATION_H

class Animation {
public:
	Animation();
	Animation(unsigned int index, unsigned int numFrames, unsigned int speed);

	unsigned int index;
	unsigned int numFrames;
	unsigned int speed;
};

#endif //FROSTNIP_PP_ANIMATION_H
