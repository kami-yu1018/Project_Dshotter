#include"Game.h"

//	線を繋ぐ点
Float2 point[3];
//	線の範囲
#define LENGTH 150.0f
#define HALF_LENGTH 75.0f

//	ボール
Float2 ball_pos;		//	座標
#define BALL_R 10.0f	//	半径
enum					//	ボールの状態用定数
{
	BALL_BEFORE,		//	ボールを放つ前
	BALL_MOVE,			//	ボールが動いているとき
	BALL_STAY,			//	ボールが止まっているとき（線にキャッチされているとき）
};
int ball_state;			//	ボールが今どのような状態であるか
bool first_ball;		//	最初のボールが放たれたか（０：まだ　１：放たれている）
bool ball_chach;		//	ボールを線でキャッチしているか
bool line;				//	線が引かれている状態か

//=====================================================================
//	初期化処理
//=====================================================================
void GameInit()
{
	//	各初期化処理
	ball_state = BALL_BEFORE;
	first_ball = 0;
	ball_chach = 0;
	line = 0;
}
//=====================================================================
//	更新処理
//=====================================================================
void GameUpdate()
{
	Float2 mouse;
	mouse.x = (float)GetMouseX();
	mouse.y = (float)GetMouseY();

	//	ボールが待機状態で無いとき
	if (ball_state != BALL_STAY)
	{
		//	マウスをクリックした瞬間
		if (PushMouseInput(MOUSE_INPUT_LEFT)||PushMouseInput(MOUSE_INPUT_RIGHT))
		{
			//	起点、終点、中間点を同じ座標に打つ
			for (int i = 0; i < 3; ++i)
			{
				point[i] = mouse;
			}
			//	ボールの座標もマウスの位置に設定
			ball_pos = mouse;
		}
	}

	//	マウスを押しているとき
	if (CheckMouseInput(MOUSE_INPUT_LEFT) || CheckMouseInput(MOUSE_INPUT_RIGHT))
	{
		//	起点の座標を決める
		Float2 before = point[0];
		//	２点間の距離を求める
		float distance = GetFloat2Distance(mouse, before);

		//	２点間の距離が範囲よりもでかいとき
		if (distance > LENGTH)
		{
			//	方向ベクトルの作成
			Float2 dir;
			dir.x = mouse.x - before.x;
			dir.y = mouse.y - before.y;

			//	方向ベクトルの取得（基準値 1.0f を取得する）
			dir.x /= distance;
			dir.y /= distance;

			//	長さを範囲分の長さにする
			Float2 dir_1;
			Float2 dir_2;

			dir_1.x = dir.x * HALF_LENGTH;
			dir_1.y = dir.y * HALF_LENGTH;

			dir_2.x = dir.x * LENGTH;
			dir_2.y = dir.y * LENGTH;

			//	終点座標を決める
			point[2].x = before.x + dir_2.x;
			point[2].y = before.y + dir_2.y;
			//	中間点座標を決める
			point[1].x = before.x + dir_1.x;
			point[1].y = before.y + dir_1.y;
			//	もし初球が打たれていないとき、ボールの座標を設定する
			if (first_ball == 0)
			{
				ball_pos = point[1];
			}
		}
	}

	//	始点と終点が一致していないとき
	if (point[1].x != point[2].x && point[1].y != point[2].y)
	{
		//	線が引かれている
		line = 1;
	}

	//	ラインが引かれている＆初球が打たれていない＆マウスを押していないとき
	if (line == 1 && first_ball == 0 && CheckMouseInput(MOUSE_INPUT_LEFT) == 0)
	{
		//	待機状態にする
		ball_state = BALL_STAY;
	}
}
//=====================================================================
//	描画処理
//=====================================================================
void GameRender()
{
	//	点の描画
	DrawCircleAA(point[0].x, point[0].y, 5.0f, 50, GetColor(255, 0, 0));
	DrawCircleAA(point[1].x, point[1].y, 5.0f, 50, GetColor(128, 128, 128));
	DrawCircleAA(point[2].x, point[2].y, 5.0f, 50, GetColor(0, 0, 255));

	//	線の描画
	Float2 pos1 = point[0];
	Float2 pos2 = point[2];
	DrawLineAA(pos1.x, pos1.y, pos2.x, pos2.y, GetColor(0, 255, 0));

	//	ボールの描画
	DrawCircleAA(ball_pos.x, ball_pos.y, BALL_R, 50, GetColor(0, 255, 255));
}
//=====================================================================
//	終了処理
//=====================================================================
void GameExit()
{

}