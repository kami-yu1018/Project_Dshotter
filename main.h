#pragma once
#pragma once

// =======================================
//  ライブラリ読込
// =======================================
#include <ctime>		// 標準C ライブラリ ヘッダー <time.h> をインクルードし、関連する名前を std 名前空間に追加します。

#include "DxLib.h"		// DxLib

#include"Game.h"


//	定数の宣言
#define WINDOW_W 1280	// 画面サイズ　横
#define WINDOW_H 720	// 画面サイズ　縦

bool PushHitKey(int key);