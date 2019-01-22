#include "FrameTime.h"

using namespace std::chrono;

FrameTime::FrameTime()
{
	last = steady_clock::now();
}

float FrameTime::Mark()
{
	const auto old = last;
	last = steady_clock::now();

	duration<float> runTime = last - old;

	return runTime.count();
}
