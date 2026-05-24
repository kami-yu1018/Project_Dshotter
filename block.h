#pragma once

#include"main.h"

class Block
{
public:
	//	ブロックの座標
	Float2 pos;
	//	ブロックの幅と高さ
#define BLOCK_W
#define BLOCK_H
	//	ブロックの体力
	int life;

	//	初期設定
	void Init()
	{
		pos.x = (GetRand(21) + 1) * 50;
		pos.y = (GetRand(11) + 1) * 50;

		life = 2;
	}
};