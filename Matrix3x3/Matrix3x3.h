#pragma once

#include <array>

class Matrix3x3 {
public:
	using arr3x3 = std::array<std::array<float, 3>, 3>;

public:
	Matrix3x3();
	Matrix3x3(const Matrix3x3& matrix);

	inline ~Matrix3x3() {}

private:
	static const int HEIGHT = 3;
	static const int WIDTH = 3;

public:
	arr3x3 m;

public:
	Matrix3x3 operator*(const Matrix3x3& Matrix1) const;
	const Matrix3x3& operator=(const Matrix3x3& Matrix1);
	const Matrix3x3& operator*=(const Matrix3x3& Matrix1);

public:


	static float SarrasRule(const Matrix3x3& m);
};