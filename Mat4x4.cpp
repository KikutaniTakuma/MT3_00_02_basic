#include "Mat4x4.h"
#include "Vector3D/Vector3D.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include "Novice.h"

#if _DEBUG
#include <chrono>
#endif // _DEBUG

#include "Matrix3x3/Matrix3x3.h"


Mat4x4::Mat4x4()
	:m({ 0.0f })
{}

Mat4x4::Mat4x4(const Mat4x4& mat) {
	*this = mat;
}

Mat4x4 Mat4x4::operator*(const Mat4x4& mat) const{
	Mat4x4 tmp;

	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			for (int i = 0; i < Mat4x4::WIDTH; i++) {
				tmp.m[y][x] += this->m[y][i] * mat.m[i][x];
			}
		}
	}

	return tmp;
}

Mat4x4::Mat4x4(std::array<std::array<float, 4>, 4> num) {
	m = num;
}

const Mat4x4& Mat4x4::operator=(const Mat4x4& mat) {
	this->m = mat.m;

	return *this;
}

const Mat4x4& Mat4x4::operator*=(const Mat4x4& mat) {
	*this = *this * mat;

	return *this;
}

Mat4x4 Mat4x4::operator+(const Mat4x4& mat) const {
	Mat4x4 tmp;

	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			tmp[y][x] = this->m[y][x] + mat.m[y][x];
		}
	}

	return tmp;
}
const Mat4x4& Mat4x4::operator+=(const Mat4x4& mat) {
	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			this->m[y][x] += mat.m[y][x];
		}
	}

	return *this;
}
Mat4x4 Mat4x4::operator-(const Mat4x4& mat) const {
	Mat4x4 tmp;

	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			tmp[y][x] = this->m[y][x] - mat.m[y][x];
		}
	}

	return tmp;
}
const Mat4x4& Mat4x4::operator-=(const Mat4x4& mat) {
	for (int y = 0; y < Mat4x4::HEIGHT; y++) {
		for (int x = 0; x < Mat4x4::WIDTH; x++) {
			this->m[y][x] -= mat.m[y][x];
		}
	}

	return *this;
}

std::array<float, 4>& Mat4x4::operator[](size_t index) {
	return m[index];
}

bool Mat4x4::operator==(const Mat4x4& mat) const {
	return m == mat.m;
}

bool Mat4x4::operator!=(const Mat4x4& mat) const {
	return m != mat.m;
}

void Mat4x4::Indentity() {
	m = { 0.0f };

	for (int i = 0; i < WIDTH; i++) {
		m[i][i] = 1.0f;
	}
}

void Mat4x4::Translate(const Vector3D& vec) {
	this->m = { 0.0f };

	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;

	this->m[3][0] = vec.x;
	this->m[3][1] = vec.y;
	this->m[3][2] = vec.z;
}

void Mat4x4::Scalar(const Vector3D& vec) {
	this->m = { 0.0f };

	this->m[0][0] = vec.x;
	this->m[1][1] = vec.y;
	this->m[2][2] = vec.z;
	this->m[3][3] = 1.0f;
}

Mat4x4 operator*(float scalar, Mat4x4 mat) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			mat[y][x] *= scalar;
		}
	}

	return mat;
}

void Mat4x4::Inverse() {
#ifdef _DEBUG
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
#endif

	Mat4x4 result = {};

	float A[4] = {};

	//小行列
	Matrix3x3 b[4][4] = {};
	int B[4][4] = {};
	for (int i = 0; i < 4; i++) {
		A[i] = m[i][0];
		for (int j = 0; j < 4; j++) {
			B[i][j] = i + j;
			for (int row = 0; row < 3; row++) {
				for (int column = 0; column < 3; column++) {
					if (i <= row) {
						if (j <= column) {
							b[i][j].m[row][column] = m[row + 1][column + 1];
						}
						else {
							b[i][j].m[row][column] = m[row + 1][column];
						}
					}
					else {
						if (j <= column) {
							b[i][j].m[row][column] = m[row][column + 1];
						}
						else {
							b[i][j].m[row][column] = m[row][column];
						}
					}
				}
			}
		}
	}

	float num = 0;

	Mat4x4 c = {};
	for (int row = 0; row < 4; row++) {
		if (row == 0 || row == 2) {
			num += A[row] * Matrix3x3::SarrasRule(b[row][0]);
		}
		else {
			num -= A[row] * Matrix3x3::SarrasRule(b[row][0]);
		}
		for (int column = 0; column < 4; column++) {
			if (B[row][column] % 2 == 0) {
				c.m[row][column] = Matrix3x3::SarrasRule(b[column][row]);
			}
			else {
				c.m[row][column] = -1 * Matrix3x3::SarrasRule(b[column][row]);
			}
		}
	}

	if (num != 0) {
		num = float(1 / num);
	}

	result = num * c;

	*this = result;

#ifdef _DEBUG
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::string msg = "Inverse Matrix Process Time : " + std::to_string(static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count())) + " microseconds\n";
	OutputDebugStringA(msg.c_str());
#endif


	/// 苦労した割にはすっきりしないプログラムでつらい
}


void Mat4x4::Transepose() {
	std::swap(m[1][0], m[0][1]);
	std::swap(m[2][0], m[0][2]);
	std::swap(m[3][0], m[0][3]);
	std::swap(m[2][1], m[1][2]);
	std::swap(m[2][3], m[3][2]);
	std::swap(m[3][1], m[1][3]);
}


void MatrixScreenPrintf(int x, int y, const Mat4x4& mat, std::string msg) {
	Novice::ScreenPrintf(x + 10, y, msg.c_str());
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + (row+1) * kRowheight, "%6.02f", mat.m[row][column]);
		}
	}
}


Mat4x4 MakeMatrixIndentity() {
	Mat4x4 tmp;
	tmp.Indentity();
	return tmp;
}

Mat4x4 MakeMatrixInverse(Mat4x4 mat) {
	Mat4x4 tmp = mat;
	tmp.Inverse();
	return tmp;
}

Mat4x4 MakeMatrixTransepose(Mat4x4 mat) {
	Mat4x4 tmp = mat;
	tmp.Transepose();
	return tmp;
}

Mat4x4 MakeMatrixTranslate(Vector3D vec) {
	Mat4x4 mat;

	mat.Translate(vec);

	return mat;
}

Mat4x4 MakeMatrixScalar(Vector3D vec) {
	Mat4x4 mat;

	mat.Scalar(vec);

	return mat;
}