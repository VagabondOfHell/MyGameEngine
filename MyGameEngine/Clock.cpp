#include "Clock.h"
#include <iostream>

float startTicks;
float processorFrequency;

Clock::Clock(void)
{
}


Clock::~Clock(void)
{
}

void Clock::StartClock()const
{
	LARGE_INTEGER current;

	//Grab the Processor Frequency and check for errors
    if(!QueryPerformanceFrequency(&current))
		std::cout << "QueryPerformanceFrequency failed!\n";

	//Multiply by 1000th to get milliseconds
	processorFrequency = float(current.QuadPart)* 0.001f;

	//Get the counter again to set our start time
    QueryPerformanceCounter(&current);
	startTicks = current.QuadPart;
}

const float Clock::GetMilliseconds()const
{
	LARGE_INTEGER current;
    //Get the current ticks
	QueryPerformanceCounter(&current);

	//Get the milliseconds since the program started, dividing by the frequency we received earlier
	return float(current.QuadPart-startTicks)/processorFrequency;
}