#pragma once

/**
 * Quaternion is used to represent the rotation state in a 3D space
 * Basically, a rot axis N and a rot degree theta is used to generate the rotation
 * w x y z 
 */

namespace xm
{
	class quat
	{
	private:
		float w, x, y, z;

	public:
		quat(float iw, float ix, float iy, float iz) : w(iw), x(ix), y(iy), z(iz) {}

		void identity() { w = 1.0f; x = y = z = 0.0f; }


	};

	extern const quat kQuaternionIdenttity;
}