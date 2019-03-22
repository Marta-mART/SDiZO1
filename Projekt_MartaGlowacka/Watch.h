#pragma once
#include <chrono>

class Watch
{
private:
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point stopTime;
	double timeSpanValue;
public:
	void start();
	void stop();
	double timeSpan();
	Watch();
	~Watch();
};

