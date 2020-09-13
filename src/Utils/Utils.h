#ifndef FROSTBYTE_UTILS_H
#define FROSTBYTE_UTILS_H

// Tolerance value when comparing floats;
static const float EPSILON = 0.0001f;

bool isEqual(float x, float y);
bool isGreatThanOrEqual(float x, float y);
bool isLessThanOrEqual(float x, float y);

#endif //FROSTBYTE_UTILS_H
