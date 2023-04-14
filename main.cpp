#include <Novice.h>
#include "Mat4x4.h"
#include "Vector3D/Vector3D.h"

const char kWindowTitle[] = "LE2A_04_キクタニ_タクマ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Mat4x4 m1({
		3.2f, 0.7f, 9.6f,4.4f,
		5.5f,1.3f,7.8f,2.1f,
		6.9f,8.0f,2.6f,1.0f,
		0.5f,7.2f,5.1f,3.3f
	});

	Mat4x4 m2({
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f
		});

	Mat4x4 resultAdd = m1 + m2;
	Mat4x4 resultMultiply = m1 * m2;
	Mat4x4 resultSubtract = m1 - m2;
	Mat4x4 inverseM1 = m1;
	inverseM1.Inverse();
	Mat4x4 inverseM2 = m2;
	inverseM2.Inverse();
	Mat4x4 transposeM1 = m1;
	transposeM1.Transepose();
	Mat4x4 transposeM2 = m2;
	transposeM2.Transepose();
	Mat4x4 identity = MakeMatrixIndentity();




	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrintf(0, 0, resultAdd, "Add");
		MatrixScreenPrintf(0, kRowheight * 5, resultSubtract, "Subtract");
		MatrixScreenPrintf(0, kRowheight * 5 * 2, resultMultiply, "Multiply");
		MatrixScreenPrintf(0, kRowheight * 5 * 3, inverseM1, "inverseM1");
		MatrixScreenPrintf(0, kRowheight * 5 * 4, inverseM2, "inverseM2");
		MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1, "transposeM1");
		MatrixScreenPrintf(kColumnWidth * 5, kRowheight * 5, transposeM2, "transposeM2");
		MatrixScreenPrintf(kColumnWidth * 5, kRowheight * 5 * 2, identity, "identity");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
