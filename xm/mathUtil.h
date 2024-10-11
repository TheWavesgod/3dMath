#pragma once

#include <cmath>

const float kPi = 3.14159265f;


extern float safeAcos(float x)
{
	if (x <= -1.0f)
	{
		return kPi;
	}
	if (x >= 1.0f)
	{
		return 0.0f; 
	}

	return acos(x);
}
