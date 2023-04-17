#pragma once

#include <array>
#include <string>

static const int kRowheight = 20;
static const int kColumnWidth = 60;

class Vector3D;

class Mat4x4 {
public:
	/// <summary>
	/// 規定コンストラクタ
	/// </summary>
	Mat4x4();

	/// <summary>
	/// コピーコンストラクタ
	/// </summary>
	Mat4x4(const Mat4x4& mat);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="num"></param>
	Mat4x4(std::array<std::array<float, 4>, 4> num);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Mat4x4() = default;

private:
	static const int HEIGHT = 4;
	static const int WIDTH = 4;

private:
	std::array<std::array<float, 4>, 4> m;

public:
	Mat4x4 operator*(const Mat4x4& mat) const;
	const Mat4x4& operator=(const Mat4x4& mat);
	const Mat4x4& operator*=(const Mat4x4& mat);

	Mat4x4 operator+(const Mat4x4& mat) const;
	const Mat4x4& operator+=(const Mat4x4& mat);
	Mat4x4 operator-(const Mat4x4& mat) const;
	const Mat4x4& operator-=(const Mat4x4& mat);

	std::array<float, 4>& operator[](size_t index);

	bool operator==(const Mat4x4& mat) const;
	bool operator!=(const Mat4x4& mat) const;

	inline std::array<std::array<float, 4>, 4> get() const {
		return m;
	}

public:
	/// <summary>
	/// 単位行列化
	/// </summary>
	void Indentity();

	/// <summary>
	/// 平行移動行列化
	/// </summary>
	/// <param name="vec">移動ベクトル</param>
	void Translate(const Vector3D& vec);

	/// <summary>
	/// スカラー倍行列化
	/// </summary>
	/// <param name="vec">大きさベクトル</param>
	void Scalar(const Vector3D& vec);

	/// <summary>
	/// 逆行列化
	/// </summary>
	void Inverse();

	/// <summary>
	/// 転置行列化
	/// </summary>
	void Transepose();

	
	friend void MatrixScreenPrintf(int x, int y, const Mat4x4& mat, std::string msg);
};


/// <summary>
/// 単位行列
/// </summary>
/// <returns>単位行列を返す</returns>
Mat4x4 MakeMatrixIndentity();

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="vec">移動ベクトル</param>
/// <returns>平行移動行列を返す</returns>
Mat4x4 MakeMatrixTranslate(Vector3D vec);

/// <summary>
/// スカラー倍行列
/// </summary>
/// <param name="vec">大きさベクトル</param>
/// <returns>スカラー倍行列を返す</returns>
Mat4x4 MakeMatrixScalar(Vector3D vec);

/// <summary>
/// 逆行列
/// <para>失敗したら引数の行列を返す</para>
/// </summary>
/// <param name="mat">逆行列にしたい行列</param>
/// <returns>引数の逆行列</returns>
Mat4x4 MakeMatrixInverse(Mat4x4 mat);

/// <summary>
/// 転置行列
/// </summary>
/// <param name="mat">転置行列にしたい行列</param>
/// <returns>引数の転置行列</returns>
Mat4x4 MakeMatrixTransepose(Mat4x4 mat);