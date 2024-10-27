#pragma once
#include <cmath>
#include "Matrix.h"
#include "assert.h"

/**
 * Quaternion is used to represent the rotation state in a 3D space
 * Basically, a rot axis N and a rot degree theta is used to generate the rotation
 * w x y z 
 * cos(T/2) sin(T/2)N 
 */

namespace xm
{
	class quat
	{ 
	private:
		float w, x, y, z;

	public:
		quat() {}
		quat(const vec3& erlarAngles);
		quat(const mat4& rotM);
		quat(float iw, float ix, float iy, float iz) : w(iw), x(ix), y(iy), z(iz) {}

		void identity() { w = 1.0f; x = y = z = 0.0f; }

		void setToRatateAboutX(float theta);
		void setToRatateAboutY(float theta);
		void setToRatateAboutZ(float theta);
		void setToRotateAboutAxis(const vec3& axis, float theta);

		float getRotationAngle() const;
		vec3 getRotationAxis() const;

		void normalize();

		quat operator *(const quat& q) const;
		quat& operator *=(const quat& q);

		static float dot(const quat& a, const quat& b) 
		{
			return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
		}

		quat conjugate() const { return quat(w, -x, -y, -z); }
		quat pow(float exponent) const;

		mat4 getRotMatrix() const;
		vec3 getEularAngles() const;
	};

	extern const quat kQuaternionIdenttity;
}