#pragma once

#include<random>


inline int random() { return rand(); }
inline int random(unsigned int max) { return rand() % max; }
inline int random(int min, int max) { return min + rand() % (max - min); }

inline float randomf() { return rand() / (float)RAND_MAX; } //0 -1
inline float randomf(float max) { return max * randomf(); } //0 and max number
inline float randomf(float min, float max) { return min + randomf(max - min); }

//inline isn't treated like a function by the computer
//rather the computer injects that code dirrectly into the line of code where the "function" is called