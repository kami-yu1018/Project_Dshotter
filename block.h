#pragma once

#include"main.h"

class Block
{
public:
	//	ブロックの座標
	Float2 pos;

	//	座標を決めるための数
	int num_x;
	int num_y;

	//	ブロックの幅と高さ
#define BLOCK_W	50.0f
#define BLOCK_H 25.0f
	//	ブロックの体力
	int life;

	unsigned int color;

	//	ブロックの位置を決める
	void Block_area()
	{
		num_x = GetRand(21) + 1;
		num_y = GetRand(11) + 1;
	}

	//	初期設定
	void Init()
	{
		pos.x = num_x * 50.0f + 10.0f;
		pos.y = num_y * 50.0f;

		life = 2;

		color = (255,255,0);
	}

	void ColorChange()
	{
		if (life == 1)
		{
			color = (255, 0, 0);
		}
	}
};