#include "Quaternion.h"
#include "mathUtil.h"
#include "assert.h"

const xm::quat kQuaternionIdenttity = { 1.0f, 0.0f, 0.0f, 0.0f };

void xm::quat::setToRatateAboutX(float theta)
{
	float thetaOver2 = theta * 0.5f;
	
	w = cos(thetaOver2);
	x = sin(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

void xm::quat::setToRatateAboutY(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = sin(thetaOver2);
	z = 0.0f;
}

void xm::quat::setToRatateAboutZ(float theta)
{
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(thetaOver2);
}

void xm::quat::setToRotateAboutAxis(const vec3& axis, float theta)
{
	assert(fabs(axis.length() - 1.0f < 0.01f));

	float thetaOver2 = theta * 0.5f;
	vec3 axisTemp = axis * sin(thetaOver2);
	w = cos(thetaOver2);
	x = axisTemp.x;
	y = axisTemp.y;
	z = axisTemp.z;
}

float xm::quat::getRotationAngle() const
{
	float thetaOver2 = safeAcos(w);
	return thetaOver2 * 2.0f;
}

xm::vec3 xm::quat::getRotationAxis() const
{
	float sinThetaOver2Sq = 1 - w * w;
	float oneOverSin = 1 / sqrt(sinThetaOver2Sq);
	return vec3(x, y, z) * oneOverSin;
}
