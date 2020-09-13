#include <iostream>
#include <SDL.h>
#include "Benchmark.h"

float Benchmark::startTime = 0;
float Benchmark::endTime = 0;
uint32_t Benchmark::c = 0;

void Benchmark::start() {
	startTime = SDL_GetTicks();
}

void Benchmark::log() {
	c++;
}

void Benchmark::stop() {
	endTime = SDL_GetTicks();
	std::cout << "Bench results: " << std::endl;
	std::cout << "\tNo. of frames: " << c << std::endl;
	std::cout << "\tAverage time: " << ((endTime - startTime) / c / 1000.0f) << "s" << std::endl;
}
