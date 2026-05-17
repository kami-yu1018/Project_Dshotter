#pragma once
#pragma once

// =======================================
//  ライブラリ読込
// =======================================
#include <ctime>		// 標準C ライブラリ ヘッダー <time.h> をインクルードし、関連する名前を std 名前空間に追加します。

#include "DxLib.h"		// DxLib

#include"Game.h"
#include<math.h>


//	定数の宣言
#define WINDOW_W 1280	// 画面サイズ　横
#define WINDOW_H 720	// 画面サイズ　縦

//	x座標とy座標を設定する構造体
struct Float2
{
	float x;
	float y;
};

//	マウスが押されているかを取得
bool CheckMouseInput(int button);
//	マウスが押された瞬間を取得
bool PushMouseInput(int button);
//	マウスの座標を取得
int GetMouseX();
int GetMouseY();

//	２つの Float2 の距離を求める
float GetFloat2Distance(Float2& pos1, Float2& pos2);