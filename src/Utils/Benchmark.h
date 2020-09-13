#ifndef FROSTBYTE__BENCHMARK_H
#define FROSTBYTE__BENCHMARK_H

class Benchmark {
public:
	static void start();
	static void log();
	static void stop();

private:
	static float startTime;
	static float endTime;
	static uint32_t c;
};

#endif //FROSTBYTE__BENCHMARK_H
