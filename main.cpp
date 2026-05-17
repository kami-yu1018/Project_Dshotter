#include"main.h"

char key_buffer[256];
int KeyFrame[256];
int mouse_frame;
// ------------------------------
// WinMain
// ------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	// =======================================
	//  初期化処理
	// =======================================
	// ログの書き出しを無効化
	SetOutApplicationLogValidFlag(FALSE);	// ログの書き出しを無効化

	// ウィンドウモードの設定
	ChangeWindowMode(TRUE);					// ウインドウモードを有効化

	// ウィンドウサイズとカラービットの設定
	SetGraphMode(WINDOW_W, WINDOW_H, 32);

	// ウィンドウのタイトル
	SetMainWindowText("DxLib Template");

	// 背景色の設定
	SetBackgroundColor(128, 128, 128);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;							// エラーが起きたら直ちに終了
	}

	// ウィンドウ描画モード設定
	SetDrawScreen(DX_SCREEN_BACK);			// 裏画面に描画する

	GameInit();

	for (int i = 0; i < 256; ++i) {
		KeyFrame[i] = 0;
	}

	// ------------------------------
	//  ゲームループ
	// ------------------------------
	while (ProcessMessage() == 0)
	{
		GetHitKeyStateAll(key_buffer);

		for (int i = 0; i < 256; ++i) {
			if (key_buffer[i]) {
				KeyFrame[i]++;
			}
			else {
				KeyFrame[i] = 0;
			}
		}

		// リフレッシュレートを設定するための処理
		clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;

		// マウスカーソル表示設定
		SetMouseDispFlag(TRUE);

		// printfDxの初期化
		clsDx();

		// 画面上の描画を初期化（画面を消去）
		ClearDrawScreen();

		GameUpdate();
		GameRender();

		// リフレッシュレートが一定になるまで待つ処理
		while (clock() < check_fps) {}

		// 裏画面の描画を表に反映
		ScreenFlip();


		// ESCキーでループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

	}

	// =======================================
	//  終了処理
	// =======================================
	GameExit();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();							// ＤＸライブラリ使用の終了処理

	// ソフトの終了
	return 0;
}
// =================================
// キーを押した瞬間
// =================================
bool PushHitKey(int key) {
	if (KeyFrame[key] == 1) {
		return true;
	}
	return false;
}
//	キーを押した瞬間
bool PushMouseInput()
{
	if (GetMouseInput())
	{
		mouse_frame++;
	}
	if (mouse_frame == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}