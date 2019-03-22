#include "Controller.h"
#include <fstream>
#include <iostream>
#include <ctime>

namespace win32 {

	inline Controller::Controller() noexcept
		: m_running{ false }
		, m_start{ 0 }
		, m_finish{ 0 }
		, m_frequency{ frequency() }
	{}


	inline void Controller::reset() noexcept
	{
		m_finish = m_start = 0;
		m_running = false;
	}


	inline void Controller::start() noexcept
	{
		m_running = true;
		m_finish = 0;

		m_start = counter();
	}


	inline void Controller::stop() noexcept
	{
		m_finish = counter();
		m_running = false;
	}


	inline double Controller::elapsedMilliseconds() const noexcept
	{
		if (m_running)
		{
			const long long current{ counter() };
			return elapsedMilliseconds(m_start, current);
		}

		return elapsedMilliseconds(m_start, m_finish);
	}


	inline long long Controller::counter() noexcept
	{
		LARGE_INTEGER li;
		::QueryPerformanceCounter(&li);
		return li.QuadPart;
	}


	inline long long Controller::frequency() noexcept
	{
		LARGE_INTEGER li;
		::QueryPerformanceFrequency(&li);
		return li.QuadPart;
	}


	inline double Controller::elapsedMilliseconds(long long start, long long finish) const noexcept
	{
		_ASSERTE(start >= 0);
		_ASSERTE(finish >= 0);
		_ASSERTE(start <= finish);

		return ((finish - start) * 1000.0) / m_frequency;
	}

}