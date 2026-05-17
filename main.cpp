#include"main.h"

char key_buffer[256];
int KeyFrame[256];
int mouse_frame_left;
int mouse_frame_right;
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

		//	マウスが押されたらカウント用変数を増やす
		if (CheckMouseInput(MOUSE_INPUT_LEFT))
		{
			mouse_frame_left++;
		}
		else
		{
			mouse_frame_left = 0;
		}
		if (CheckMouseInput(MOUSE_INPUT_RIGHT))
		{
			mouse_frame_right++;
		}
		else
		{
			mouse_frame_right = 0;
		}

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
//---------------------------------------------------------------------------------
//	マウスが押されているかを取得
//---------------------------------------------------------------------------------
bool CheckMouseInput(int button)
{
	if (GetMouseInput() & button)
	{
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	マウスクリックフレームのカウント
//---------------------------------------------------------------------------------
void GetMouseFrame()
{
	if (CheckMouseInput(MOUSE_INPUT_LEFT) == true)
	{
		mouse_frame_left++;
	}
	else
	{
		mouse_frame_left = 0;
	}
	if (CheckMouseInput(MOUSE_INPUT_RIGHT) == true)
	{
		mouse_frame_right++;
	}
	else
	{
		mouse_frame_right = 0;
	}
}

//---------------------------------------------------------------------------------
//	マウスが押された瞬間を取得
//---------------------------------------------------------------------------------
bool PushMouseInput(int button)
{
	if (button & MOUSE_INPUT_LEFT)
	{
		if (mouse_frame_left == 1)
		{
			return true;
		}
	}
	if (button & MOUSE_INPUT_RIGHT)
	{
		if (mouse_frame_right == 1)
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
// マウス座標の取得
//---------------------------------------------------------------------------------
int GetMouseX()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	return mouse_x;
}
int GetMouseY()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	return mouse_y;
}
//---------------------------------------------------------------------------------
//	２つの Float2の距離を求める
//---------------------------------------------------------------------------------
float GetFloat2Distance(Float2& pos1, Float2& pos2)
{
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;
	float distance = sqrtf(x * x + y * y);
	return distance;
}