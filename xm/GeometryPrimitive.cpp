#include "GeometryPrimitive.h"

float xm::Line::GetDistanceFromPoint(const vec3& point)
{
	vec3 ps = point - start;
	ps.projectTo(end - start);
}

float xm::Line::GetDistanceFromLine(const Line& other)
{
	vec3 s1 = start;
	vec3 v1 = end - start;
	v1.nomalized();
	vec3 s2 = other.start;
	vec3 v2 = other.end - other.start;
	v2.nomalized();

	float v1dotv2 = v1 * v2;
	float denom = v1dotv2 - 1;
	if (denom == 0)
	{
		return GetDistanceFromPoint(other.start);
	}
	float k = 1 / denom;

	vec3 s2s1 = s2 - s1;

	float t1 = (-s2s1 * v1 + s2s1 * v2 * v1dotv2) * k;
	float t2 = (-s2s1 * v1 * v1dotv2 + s2s1 * v2) * k;

	vec3 p1 = s1 + t1 * v1;
	vec3 p2 = s2 + t2 * v2;

	return (p2 - p1).length();
}

bool xm::Plane::CollisionWithLine(const Line& line, vec3& collidePoint)
{
	vec3 v = line.end - line.start;
	v.nomalized();

	float NdotV = normal * v;
	if (NdotV == 0) return false;

	vec3 s = line.start;
	float NdotS = normal * s;

	float t = -(NdotS + d) / NdotV;
	collidePoint = s + t * v;

	return true;
}
