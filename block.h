#pragma once

#include"main.h"

class Block
{
public:
	//	ブロックの座標
	Float2 pos;
	//	ブロックの幅と高さ
	float w;
	float h;
	//	ブロックの体力
	int life;
};