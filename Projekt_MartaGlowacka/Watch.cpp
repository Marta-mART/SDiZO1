#include "Watch.h"

#include <iostream>

using namespace std::chrono;

void Watch::start() {
	startTime = high_resolution_clock::now();
}

void Watch::stop() {
	stopTime = high_resolution_clock::now();
}

double Watch::timeSpan() {
	duration<double> difference = duration_cast<duration<double>>(stopTime - startTime);
	timeSpanValue = difference.count();
	return timeSpanValue;
}

Watch::Watch()
{
}

Watch::~Watch()
{
}
