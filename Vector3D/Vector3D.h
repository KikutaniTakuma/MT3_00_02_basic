#pragma once
#include <string>

class Vector3D {
public:
	Vector3D() = default;
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& vec) = default;

public:
	float x;
	float y;
	float z;

public:
	Vector3D& operator=(const Vector3D& vec) = default;
	Vector3D operator+(const Vector3D& vec);
	Vector3D operator-(const Vector3D& vec);
	Vector3D operator+=(const Vector3D& vec);
	Vector3D operator-=(const Vector3D& vec);
	Vector3D operator*(float scalar);
	Vector3D operator*=(float scalar);
	Vector3D Normalize();

	float Dot(const Vector3D& vec);
	float Length();

	friend void Vec3ScreenPrintf(int x, int y, const Vector3D& vec, std::string label);
};