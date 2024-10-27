#include "Quaternion.h"
#include "mathUtil.h"

const xm::quat kQuaternionIdenttity = { 1.0f, 0.0f, 0.0f, 0.0f };

xm::quat::quat(const vec3& erlarAngles)
{
	float sp, sb, sh;
	float cp, cb, ch;

	sp = sin(erlarAngles.x * 0.5f);
	cp = cos(erlarAngles.x * 0.5f);
	sb = sin(erlarAngles.y * 0.5f);
	cb = cos(erlarAngles.y * 0.5f);
	sh = sin(erlarAngles.z * 0.5f);
	ch = cos(erlarAngles.z * 0.5f);

	w =  ch * cp * cb + sh * sp * sb;
	x =  ch * sp * cb + sh * cp * sb;
	y = -ch * sp * sb + sh * cp * cb;
	z = -sh * sp * cb + ch * cp * sb;
}

xm::quat::quat(const mat4& rotM)
{
	float m11 = rotM[0][0];
	float m12 = rotM[0][1];
	float m13 = rotM[0][2];

	float m21 = rotM[1][0];
	float m22 = rotM[1][1]; 
	float m23 = rotM[1][2];

	float m31 = rotM[2][0];
	float m32 = rotM[2][1];
	float m33 = rotM[2][2];

	float fourSquaredMinus1[4];
	fourSquaredMinus1[0] = m11 + m22 + m33;
	fourSquaredMinus1[1] = m11 - m22 - m33;
	fourSquaredMinus1[2] = m22 - m11 - m33;
	fourSquaredMinus1[3] = m33 - m22 - m11;

	int biggestIndex = 0;
	float fourBiggestSqauredMinus1 = fourSquaredMinus1[0];

	for (size_t i = 1; i < 4; ++i)
	{
		if (fourSquaredMinus1[i] > fourBiggestSqauredMinus1)
		{
			biggestIndex = i;
			fourBiggestSqauredMinus1 = fourSquaredMinus1[i];
		}
	}

	float biggestValue = sqrt(fourBiggestSqauredMinus1 + 1) * 0.5f;
	float multi = 0.25f / biggestValue;
	
	switch (biggestIndex)
	{
	case 0:
		w = biggestValue;
		x = (m23 - m32) * multi;
		y = (m31 - m13) * multi;
		z = (m12 - m21) * multi;
		break;

	case 1:
		x = biggestValue;
		w = (m23 - m32) * multi;
		y = (m12 + m21) * multi;
		z = (m31 + m13) * multi;
		break;

	case 2:
		y = biggestValue;
		w = (m31 - m13) * multi;
		x = (m12 + m21) * multi;
		z = (m23 + m32) * multi;
		break;
		break;

	case 3:
		z = biggestValue;
		w = (m12 - m21) * multi;
		x = (m31 + m13) * multi;
		y = (m23 + m32) * multi;
		break;
		break;
	}
}

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


void xm::quat::normalize()
{
	float mag = (float)sqrt(w * w + x * x + y * y + z * z);
	if (mag <= 0.0f)
	{
		assert(false);
		identity();
	}

	float oneOverMag = 1.0f / mag;
	w *= oneOverMag;
	x *= oneOverMag;
	y *= oneOverMag;
	z *= oneOverMag;
}

xm::quat xm::quat::operator*(const quat& q) const
{
	quat result;
	result.w = w * q.w - x * q.x - y * q.y - z * q.z;
	result.x = w * q.x + x * q.w + z * q.y - y * q.z;
	result.y = w * q.y + y * q.w + x * q.z - z * q.x; 
	result.z = w * q.z + z * q.w + y * q.x - x * q.y;

	return result;
}

xm::quat& xm::quat::operator*=(const quat& q)
{
	*this = *this * q;
	return *this;
}

xm::quat xm::quat::pow(float exponent) const
{
	if (fabs(w) > 0.9999999f) return *this;

	float alpha = safeAcos(w);
	float newAlpha = exponent * alpha;
	
	quat result;
	result.w = cos(newAlpha);
	float mult = sin(newAlpha) / sin(alpha);
	result.x = x * mult;
	result.y = y * mult;
	result.z = z * mult;

	return result;
}

xm::mat4 xm::quat::getRotMatrix() const
{
	mat4 result;
	result[0][0] = 1.0f - 2.0f * (y * y + z * z);
	result[0][1] = 2.0f * (x * y + w * z);
	result[0][2] = 2.0f * (x * z - w * y);

	result[1][0] = 2.0f * (x * y - w * z);
	result[1][1] = 1.0f - 2.0f * (x * x + z * z);
	result[1][2] = 2.0f * (y * z + w * x);

	result[2][0] = 2.0f * (x * z + w * y);
	result[2][1] = 2.0f * (y * z - w * x);
	result[2][2] = 1.0f - 2.0f * (x * x + y * y);

	result[3][3] = 1.0f;	// TODO: check if this equation is correct
}

xm::vec3 xm::quat::getEularAngles() const
{
	vec3 result;

	float sp = -2.0f * (y * z - w * x);
	if (fabs(sp) > 0.999999f)
	{
		result.x = kPi * 0.5f * sp;
		result.y = atan2(-x * z + w * y, 0.5f - y * y - z * z);
		result.z = 0.0f;
	}
	else
	{
		result.x = -asin(sp);
		result.y = atan2(x * z + w * y, 0.5f - x * x - y * y);
		result.z = atan2(x * y + w * z, 0.5f - x * x - z * z);
	}

}


