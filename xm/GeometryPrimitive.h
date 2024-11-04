#pragma once
#include "Vector.h"

namespace xm
{
	class Line
	{
	public:
		vec3 start;
		vec3 end;

	public:
		float GetDistanceFromPoint(const vec3& point);

		float GetDistanceFromLine(const Line& other);
	};

	class Ray
	{
	public:
		vec3 origin;
		vec3 diretion;
	};

	class Plane
	{
	public:
		vec3 normal;
		float d;

	public:
		bool CollisionWithLine(const Line& line, vec3& collidePoint);
	};
}


