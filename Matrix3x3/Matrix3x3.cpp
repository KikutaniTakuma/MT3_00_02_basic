#include "Matrix3x3.h"
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

Matrix3x3::Matrix3x3()
	:m({ 0.0f })
{}

Matrix3x3::Matrix3x3(const Matrix3x3& matrix) {
	*this = matrix;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& Matrix1) const{
	Matrix3x3 tmp;

	for (int y = 0; y < Matrix3x3::HEIGHT; y++) {
		for (int x = 0; x < Matrix3x3::WIDTH; x++) {
			for (int i = 0; i < Matrix3x3::WIDTH; i++) {
				tmp.m[y][x] += this->m[y][i] * Matrix1.m[i][x];
			}
		}
	}

	return tmp;
}

const Matrix3x3& Matrix3x3::operator=(const Matrix3x3& Matrix1) {
	this->m = Matrix1.m;

	return *this;
}

const Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& Matrix1) {
	*this = *this * Matrix1;

	return *this;
}



float Matrix3x3::SarrasRule(const Matrix3x3& m) {
	float result = m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1];
	return result;
}