#pragma once

namespace BorderlessEngine
{
	struct Vector3
	{
	public:
		Vector3()
		{
			X = Y = Z = 0.0f;
		}
		Vector3(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}
		float X;
		float Y;
		float Z;
	};
}