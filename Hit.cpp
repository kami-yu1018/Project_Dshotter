#include"Hit.h"

//	点と円の当たり判定
bool Hit::HitPointCircle(Float2 point, Float2 circle, float radius)
{
	float distance = GetFloat2Distance(point, circle);	//	点と円の座標との距離を取得
	//	距離が半径よりも小さいとき当たっている
	if (distance <= radius)
	{
		return true;
	}
	return false;
}
//	線と円の当たり判定
bool Hit::HitLineCircle(Float2 point_f, Float2 point_e, Float2 circle, float radius)
{
	VECTOR p1 = VGet(point_f.x, point_f.y, 0.0f);
	VECTOR p2 = VGet(point_e.x, point_e.y, 0.0f);
	VECTOR cir = VGet(circle.x, circle.y, 0.0f);
	//	線分のベクトル
	VECTOR line = VSub(p2, p1);
	//	円から線の始点のベクトル
	VECTOR l_c = VSub(cir, p1);

	//	線分の長さの2乗
	float line2 = line.x * line.x + line.y * line.y;

	//	円の座標を線分に射影した時の係数（０～１ならば線分上）
	float t = (l_c.x * line.x + l_c.y * line.y) / line2;

	//	tを０～１に固定
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	if (t > 1.0f)
	{
		t = 1.0f;
	}

	//	線分上の点Pをとる
	//	この点Pは円の座標とつなげると線分から円への最短距離となる
	VECTOR p = VAdd(p1, VScale(line, t));

	DrawCircleAA(p.x, p.y, 3.0f, 50, GetColor(0, 0, 0));

	//	円の中心座標とpとの距離
	float dx = p.x - cir.x;
	float dy = p.y - cir.y;
	float dist2 = dx * dx + dy * dy;

	if (dist2 <= radius * radius)
	{
		pos.x = p.x;
		pos.y = p.y;
		return true;
	}
	return false;
}