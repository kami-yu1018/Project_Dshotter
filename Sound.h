#pragma once
#include "main.h"

class Bgm
{
public:

	//	‚a‚f‚l‚ğ–Â‚ç‚·
	void Set(int bgm);

	//	‚a‚f‚lØ‚è‘Ö‚¦
	void ChangeBgm(int bgm_1,int bgm_2,int scene);
};

class Se
{
protected:
	int ballhit_se = LoadSoundMem("data/sound/se_hitball.mp3");
	int linehit_se = LoadSoundMem("data/sound/se_lineball.mp3");
	int victory_se = LoadSoundMem("data/sound/se_victory.mp3");
	int lose_se = LoadSoundMem("data/sound/se_lose.mp3");
};