#ifndef FROSTNIP_PP_UTILS_H
#define FROSTNIP_PP_UTILS_H

// Tolerance value when comparing floats;
static const float EPSILON = 0.0001f;

bool isEqual(float x, float y);
bool isGreatThanOrEqual(float x, float y);
bool isLessThanOrEqual(float x, float y);

#endif //FROSTNIP_PP_UTILS_H
