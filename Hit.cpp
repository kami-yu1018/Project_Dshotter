#include"Hit.h"

//	“_‚Æ‰~‚Ì“–‚½‚è”»’è
bool HitPointCircle(Float2 point, Float2 circle, float radius)
{
	float distance = GetFloat2Distance(point, circle);	//	“_‚Æ‰~‚ÌÀ•W‚Æ‚Ì‹——£‚ğæ“¾
	//	‹——£‚ª”¼Œa‚æ‚è‚à¬‚³‚¢‚Æ‚«“–‚½‚Á‚Ä‚¢‚é
	if (distance <= radius)
	{
		return true;
	}
	return false;
}