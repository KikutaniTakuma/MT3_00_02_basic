#include "Vector3D/Vector3D.h"
#include <cmath>
#include "Novice.h"

Vector3D::Vector3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D Vector3D::operator+(const Vector3D& vec) {
	Vector3D tmp(x + vec.x, y + vec.y, z + vec.z);

	return tmp;
}
Vector3D Vector3D::operator-(const Vector3D& vec) {
	Vector3D tmp(x - vec.x, y - vec.y, z - vec.z);

	return tmp;
}
Vector3D Vector3D::operator+=(const Vector3D& vec) {
	*this = *this + vec;

	return *this;
}
Vector3D Vector3D::operator-=(const Vector3D& vec) {
	*this = *this - vec;

	return *this;
}

Vector3D Vector3D::operator*(float scalar) {
	Vector3D tmp(x * scalar, y * scalar, z * scalar);

	return tmp;
}
Vector3D Vector3D::operator*=(float scalar) {
	*this = *this * scalar;

	return *this;
}

Vector3D Vector3D::Normalize() {
	float nor = this->Length();

	return Vector3D(x / nor, y / nor, z / nor);
}

float Vector3D::Length() {
	return sqrtf(powf(x,2.0f)+ powf(y, 2.0f)+ powf(z, 2.0f));
}

float Vector3D::Dot(const Vector3D& vec) {
	return x * vec.x + y * vec.y + z * vec.z;
}

static const int kColumnWidth = 60;

void Vec3ScreenPrintf(int x, int y, const Vector3D& vec, std::string label) {
	Novice::ScreenPrintf(x, y, "%0.02f", vec.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.02f", vec.y);
	Novice::ScreenPrintf(x+kColumnWidth*2, y, "%0.02f", vec.z);
	Novice::ScreenPrintf(x+kColumnWidth*3, y, "%s", label.c_str());
}