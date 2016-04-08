#pragma once
#include <Windows.h>

#ifdef MYGAMEENGINE_EXPORTS
  #define MYGAMEENGINE_EXPORT __declspec(dllexport)
#else
  #define MYGAMEENGINE_EXPORT __declspec(dllimport)
#endif

class MYGAMEENGINE_EXPORT Clock
{
private:
	
public:
	Clock(void);
	~Clock(void);

	//Start the clock
	void StartClock()const;

	//Get the time in milliseconds that has passed
	const float GetMilliseconds()const;

};

