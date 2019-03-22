#pragma once

#include <crtdbg.h>     // For _ASSERTE
#include <Windows.h>    // For high-performance timers

namespace win32 {


class Controller
{
private:
	bool m_running;                 // is the timer running?
	long long m_start;              // start tick count
	long long m_finish;             // end tick count
	const long long m_frequency;    // cached frequency value

public:
	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;
	Controller() noexcept;
	void reset() noexcept;
	void start() noexcept;
	void stop() noexcept;
	double elapsedMilliseconds() const noexcept;
	// Wrapper to Win32 API QueryPerformanceCounter()
	static long long counter() noexcept;
	
	// Wrapper to Win32 API QueryPerformanceFrequency()
	static long long frequency() noexcept;
	
	// Calculate elapsed time in milliseconds,
	// given a start tick and end tick counts.
	double elapsedMilliseconds(long long start, long long finish) const noexcept;

	~Controller();
};

}