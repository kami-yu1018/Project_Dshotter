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
bool ball_chach;			//	ボールを線でキャッチしている秒数
Float2 ball_speed;		//	ボールのスピード

bool line;				//	線が引かれている状態か

//	シーン
enum
{
	SCENE_OP,
	SCENE_GAME,
	SCENE_GAMEOVER,
	SCENE_CLEAR,
};
//	シーンを入れる用の変数
int scene;


//	撃破数
int kill;

//	インスタンス化
Hit hit_obj;

#define BLOCK_MAX 20
Block block[BLOCK_MAX];

Time g_time;

Bgm bgm;
int menu_b;
int play_b;

Se se;
int ballhit_se;
int linehit_se;
int victory_se;
int lose_se;

int fonthandle_op1;
int fonthandle_op2;
				  
int fonthandle_ed1;
int fonthandle_ed2;

int text_count;
bool text_flash;
//=====================================================================
//	初期化処理
//=====================================================================
void GameInit()
{
	scene = SCENE_OP;

	menu_b = LoadSoundMem("data/sound/bgm_menu.mp3");
	play_b = LoadSoundMem("data/sound/bgm_play.mp3");

	ballhit_se = LoadSoundMem("data/sound/se_hitball.mp3");
	linehit_se = LoadSoundMem("data/sound/se_lineball.mp3");
	victory_se = LoadSoundMem("data/sound/se_victory.mp3");
	lose_se = LoadSoundMem("data/sound/se_lose.mp3");

	bgm.Set(menu_b);

	fonthandle_op1 = CreateFontToHandle(NULL, 100, 7. - 1);;
	fonthandle_op2 = CreateFontToHandle(NULL, 30, 1. - 1);

	fonthandle_ed1 = CreateFontToHandle(NULL, 100, 1. - 1);
	fonthandle_ed2 = CreateFontToHandle(NULL, 25, 1, -1);

	text_count = 0;
	text_flash = 1;
}
//=====================================================================
//	更新処理
//=====================================================================
void GameUpdate()
{

	text_count++;
	if (text_count > 30)
	{
		text_count = 0;
		if (text_flash == 0)
		{
			text_flash = 1;
		}
		else
		{
			text_flash = 0;
		}
	}
	if (scene == SCENE_OP)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			//	スペースキーを押したらゲームを開始する
			scene = SCENE_GAME;
			GameSet();
		}
		se.Reset_SeCheck();
		if (CheckSoundMem(lose_se) == 1 || CheckSoundMem(victory_se) == 1)
		{
			se.StopSe(lose_se);
			se.StopSe(victory_se);
		}
	}

	if (scene == SCENE_GAME)
	{
		if (CheckSoundMem(lose_se) == 1 || CheckSoundMem(victory_se) == 1)
		{
			se.StopSe(lose_se);
			se.StopSe(victory_se);
		}

		//	ゲームの処理
		GamePlay();

		g_time.frame_count++;
		//	時間に変換
		g_time.Count();

		//	撃破数のカウント
		kill = Kill_Count();

		//	ゲームオーバー条件が揃ったらゲームオーバーにする
		if (GameOver() == 1)
		{
			scene = SCENE_GAMEOVER;
		}
		//	ブロックを全部消したらゲームクリア
		if (kill == BLOCK_MAX)
		{
			scene = SCENE_CLEAR;
		}
	}

	if (scene == SCENE_GAMEOVER)
	{
		EndGame_Next();
		bgm.StopBgm(play_b);
		if(se.se_check == 0)
		{
			se.PlaySe(lose_se);
			se.se_check = 1;
		}
	}

	if (scene == SCENE_CLEAR)
	{
		EndGame_Next();
		bgm.StopBgm(play_b);
		if (se.se_check == 0)
		{
			se.PlaySe(victory_se);
			se.se_check = 1;
		}
	}

	if (CheckSoundMem(lose_se) == 0 && CheckSoundMem(victory_se) == 0)
	{
		bgm.ChangeBgm(menu_b, play_b, scene);
	}

}
//=====================================================================
//	描画処理
//=====================================================================
void GameRender()
{
	if(scene==SCENE_GAME)
	{
		if(line==1)

		{
			//	点の描画
			DrawCircleAA(point[0].x, point[0].y, 5.0f, 50, GetColor(255, 255, 255));
			DrawCircleAA(point[2].x, point[2].y, 5.0f, 50, GetColor(255, 255, 255));

			//	線の描画
			Float2 pos1 = point[0];
			Float2 pos2 = point[2];
			DrawLineAA(pos1.x, pos1.y, pos2.x, pos2.y, GetColor(255, 255, 255));
		}

		//	ボールの描画
		if(ball_state!=BALL_BEFORE)
		{
			DrawCircleAA(ball_pos.x, ball_pos.y, BALL_R, 50, GetColor(255, 255, 255));
		}

		//	ブロックの描画
		for (int i = 0; i < BLOCK_MAX; ++i)
		{
			if (block[i].life > 0)
			{
				DrawBoxAA(block[i].pos.x, block[i].pos.y, block[i].pos.x + BLOCK_W, block[i].pos.y + BLOCK_H, GetColor(block[i].color.r,block[i].color.g,block[i].color.b), TRUE);
			}
		}
	}

	//	各シーン時に表示するもの
	//	タイトル
	if (scene == SCENE_OP)
	{
		DrawStringFToHandle(300.0f, 300.0f,"DragShotter", GetColor(255, 255, 255),fonthandle_op1);
		if(text_flash==1)
		{
			DrawStringFToHandle(450.0f, 500.0f, "Push Space To Start", GetColor(255, 255, 255), fonthandle_op2);
		}
	}
	//	ゲームオーバー
	if (scene == SCENE_GAMEOVER)
	{
		DrawStringFToHandle(350.0f, 300.0f, "GameOver", GetColor(0, 0, 255),fonthandle_ed1);
		if (text_flash == 1)
		{
			DrawStringFToHandle(250.0f, 500.0f, "Ｒ→リトライ", GetColor(255, 255, 255), fonthandle_ed2);
			DrawStringFToHandle(600.0f, 500.0f, "ENTER→タイトルへ戻る", GetColor(255, 255, 255), fonthandle_ed2);
		}

	}
	//	クリア
	if (scene == SCENE_CLEAR)
	{
		DrawStringFToHandle(300.0f, 300.0f, "GameClear", GetColor(255, 0, 0),fonthandle_ed1);

		DrawFormatStringFToHandle(400.0f, 500.0f, GetColor(255, 255, 0),fonthandle_ed2, "%d : %d : %d : %d", g_time.h, g_time.m, g_time.s, g_time.frame_count);
		DrawStringFToHandle(250.0f, 650.0f, "Ｒ→リトライ", GetColor(255, 255, 255), fonthandle_ed2);
		DrawStringFToHandle(600.0f, 650.0f, "ENTER→タイトルへ戻る", GetColor(255, 255, 255), fonthandle_ed2);
	}

	
}
//=====================================================================
//	終了処理
//=====================================================================
void GameExit()
{

}

//	ゲーム本編の初期設定
void GameSet()
{
	//	各初期化処理
	//	ボール
	ball_pos = { NULL,NULL };
	ball_state = BALL_BEFORE;
	first_ball = 0;
	ball_chach = 0;
	ball_speed = { 0.0f,0.0f };


	for (int i = 0; i < 3; ++i)
	{
		point[i] = { NULL,NULL };
	}
	line = 0;

	//	ブロックの位置を決める
	for (int i = 0; i < BLOCK_MAX; ++i)
	{
		block[i].Block_area();
		block[i].Init();
	}

	//	カウントの初期設定
	g_time.Set();
}

//	ゲーム中の処理
void GamePlay()
{
	//	ボールが待機状態で無いとき
	if (ball_state != BALL_STAY)
	{
		Float2 mouse;
		mouse.x = (float)GetMouseX();
		mouse.y = (float)GetMouseY();

		//	マウスをクリックした瞬間
		if (PushMouseInput(MOUSE_INPUT_LEFT) || PushMouseInput(MOUSE_INPUT_RIGHT))
		{
			//	起点、終点、中間点を同じ座標に打つ
			for (int i = 0; i < 3; ++i)
			{
				point[i] = mouse;
			}
			//	ボールの座標もマウスの位置に設定
			//	（初球のみ）
			if (first_ball == 0)
			{
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
					hit_obj.pos = point[1];
				}
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

	//	待機状態のとき
	if (ball_state == BALL_STAY)
	{
		//	マウスを押しているとき
		if (CheckMouseInput(MOUSE_INPUT_LEFT) || CheckMouseInput(MOUSE_INPUT_RIGHT))
		{
			//	マウス座標の取得
			Float2 mouse;
			mouse.x = (float)GetMouseX();
			mouse.y = (float)GetMouseY();
			//	マウスと円の当たり判定
			if (hit_obj.HitPointCircle(mouse, ball_pos, BALL_R))
			{
				//	ボールがマウス座標と同じになる
				ball_pos = mouse;
				//	ボールをキャッチしている秒数をカウント
				ball_chach = 1;
			}
		}
		//	マウスを押していない時
		if (CheckMouseInput(MOUSE_INPUT_LEFT) == 0 && CheckMouseInput(MOUSE_INPUT_RIGHT) == 0)
		{
			//	ボールをキャッチしている状態のとき
			if (ball_chach == 1)
			{
				//	０にする
				ball_chach = 0;
				//	ボールを移動している状態にする
				ball_state = BALL_MOVE;

				//	最初のボールが打たれた判定を返す
				first_ball = 1;

				//	ボールのスピードと放つ方向を決める
				//	ボールと中間点との距離を取得する
				Float2 pos;
				pos.x = ball_pos.x - hit_obj.pos.x;
				pos.y = ball_pos.y - hit_obj.pos.y;

				//	ボールの移動量を設定
				ball_speed.x = pos.x * -0.1f;
				ball_speed.y = pos.y * -0.1f;

				//	線を消す
				line = 0;
				for (int i = 0; i < 3; ++i)
				{
					point[i] = { NULL,NULL };
				}
			}
		}
	}

	//	ボールが移動している時
	if (ball_state == BALL_MOVE)
	{
		//	ボール座標にスピードを足す
		ball_pos.x += ball_speed.x;
		ball_pos.y += ball_speed.y;

		//	線とボールの当たり判定
		if (hit_obj.HitLineCircle(point[0], point[2], ball_pos, BALL_R))
		{
			if (line == 1)
			{
				ball_pos = hit_obj.pos;

				ball_speed = { 0.0f,0.0f };

				ball_state = BALL_STAY;

				//	Seを鳴らす（1回のみ）
				if (se.se_check == 0)
				{
					se.PlaySe(linehit_se);
					se.se_check = 1;
				}
			}
		}
		else
		{
			se.Reset_SeCheck();
		}
	}

	for (int i = 0; i < BLOCK_MAX; ++i)
	{
		//	ボールとブロックの当たり判定
		if (hit_obj.HitBoxCircle(block[i].pos, BLOCK_W, BLOCK_H, ball_pos, BALL_R) == 1)
		{

			//	ブロックの体力があるときに作動するようにする
			if (block[i].life > 0)
			{
				//	プレイヤーのスピードを変える
				if (block[i].pos.x < ball_pos.x < block[i].pos.x + BLOCK_W)
				{
					if (block[i].pos.y > ball_pos.y || block[i].pos.y + BLOCK_H < ball_pos.y)
					{
						ball_speed.y *= -1.0f;
					}
				}
				
				if (block[i].pos.y < ball_pos.y + BALL_R && ball_pos.y - BALL_R < block[i].pos.y + BLOCK_H)
				{
					if (block[i].pos.x > ball_pos.x || block[i].pos.x + BLOCK_W < ball_pos.x)
					{
						ball_speed.x *= -1.0f;
					}
				}

				//	ブロックの体力を減らす
				block[i].life--;
				if (block[i].life < 0)
				{
					block[i].life = 0;
				}

				//	Seを鳴らす（1回のみ）
				if (se.se_check == 0)
				{
					se.PlaySe(ballhit_se);
					se.se_check = 1;
				}
			}
		}
		else
		{
			se.Reset_SeCheck();
		}
		//	ブロックの色を変更する
		block[i].ColorChange();
	}
}

//	撃破数の計算
int Kill_Count()
{
	int num = 0;
	for (int i = 0; i < BLOCK_MAX; ++i)
	{
		if (block[i].life == 0)
		{
			num++;
		}
	}

	return num;
}

//	ゲームオーバーになる時の処理
bool GameOver()
{
	if (ball_pos.x + BALL_R<0 ||
		ball_pos.x - BALL_R>WINDOW_W ||
		ball_pos.y + BALL_R<0 ||
		ball_pos.y - BALL_R>WINDOW_H)
	{
		return true;
	}
	return false;
}

//	ゲーム終了時にキーによって次のシーンを決める処理
void EndGame_Next()
{
	//	Ｒキーを押したらリトライ
	if (CheckHitKey(KEY_INPUT_R))
	{
		scene = SCENE_GAME;
		GameSet();
	}
	//	エンターキーでタイトルへ
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		scene = SCENE_OP;
	}
}