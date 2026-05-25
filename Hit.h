#pragma once

#include"main.h"
#include"Val.h"

class Hit
{
public:
	//	位置座標を入れる用
	Float2 pos;


	//	点と円の当たり判定
	bool HitPointCircle(Float2 point, Float2 circle, float radius);
	//	線と円の当たり判定
	bool HitLineCircle(Float2 point_f, Float2 point_e, Float2 circle, float radius);
	//	四角と円の当たり判定
	bool HitBoxCircle(Float2 box, float box_w, float box_h, Float2 circle, float radius);

};

