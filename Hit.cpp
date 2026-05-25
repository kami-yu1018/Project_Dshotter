#include"Hit.h"

//	“_‚Æ‰~‚Ì“–‚½‚è”»’è
bool Hit::HitPointCircle(Float2 point, Float2 circle, float radius)
{
	float distance = GetFloat2Distance(point, circle);	//	“_‚Æ‰~‚ÌÀ•W‚Æ‚Ì‹——£‚ğæ“¾
	//	‹——£‚ª”¼Œa‚æ‚è‚à¬‚³‚¢‚Æ‚«“–‚½‚Á‚Ä‚¢‚é
	if (distance <= radius)
	{
		return true;
	}
	return false;
}
//	ü‚Æ‰~‚Ì“–‚½‚è”»’è
bool Hit::HitLineCircle(Float2 point_f, Float2 point_e, Float2 circle, float radius)
{
	VECTOR p1 = VGet(point_f.x, point_f.y, 0.0f);
	VECTOR p2 = VGet(point_e.x, point_e.y, 0.0f);
	VECTOR cir = VGet(circle.x, circle.y, 0.0f);
	//	ü•ª‚ÌƒxƒNƒgƒ‹
	VECTOR line = VSub(p2, p1);
	//	‰~‚©‚çü‚Ìn“_‚ÌƒxƒNƒgƒ‹
	VECTOR l_c = VSub(cir, p1);

	//	ü•ª‚Ì’·‚³‚Ì2æ
	float line2 = line.x * line.x + line.y * line.y;

	//	‰~‚ÌÀ•W‚ğü•ª‚ÉË‰e‚µ‚½‚ÌŒW”i‚O`‚P‚È‚ç‚Îü•ªãj
	float t = (l_c.x * line.x + l_c.y * line.y) / line2;

	//	t‚ğ‚O`‚P‚ÉŒÅ’è
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	if (t > 1.0f)
	{
		t = 1.0f;
	}

	//	ü•ªã‚Ì“_P‚ğ‚Æ‚é
	//	‚±‚Ì“_P‚Í‰~‚ÌÀ•W‚Æ‚Â‚È‚°‚é‚Æü•ª‚©‚ç‰~‚Ö‚ÌÅ’Z‹——£‚Æ‚È‚é
	VECTOR p = VAdd(p1, VScale(line, t));

	DrawCircleAA(p.x, p.y, 3.0f, 50, GetColor(0, 0, 0));

	//	‰~‚Ì’†SÀ•W‚Æp‚Æ‚Ì‹——£
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
//	lŠp‚Æ‰~‚Ì“–‚½‚è”»’è
bool Hit::HitBoxCircle(Float2 box, float box_w, float box_h, Float2 circle, float radius)
{
	if (box.x<circle.x + radius && box.x + box_w>circle.x - radius)
	{
		if (box.y<circle.y + radius && box.y + box_h>circle.y - radius)
		{
			return true;
		}
	}
	return false;
}