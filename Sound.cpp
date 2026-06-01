#include"Sound.h"

void Bgm::Set(int bgm)
{
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

void Bgm::ChangeBgm(int bgm_1, int bgm_2,int scene)
{
	//	メニュー→本編
	if (scene == 1)
	{
		if(CheckSoundMem(bgm_2)==0)
		{
			if (CheckSoundMem(bgm_1) == 1)
			{
				StopSoundMem(bgm_1);
			}
			PlaySoundMem(bgm_2, DX_PLAYTYPE_LOOP);
		}
	}
	//	本編→メニュー
	else	
	{
		if (CheckSoundMem(bgm_1) == 0)
		{
			if (CheckSoundMem(bgm_2) == 1)
			{
				StopSoundMem(bgm_2);
			}
			PlaySoundMem(bgm_1, DX_PLAYTYPE_LOOP);
		}
	}
}

void Bgm::StopBgm(int bgm)
{
	StopSoundMem(bgm);
}

void Se::PlaySe(int se)
{
	PlaySoundMem(se, DX_PLAYTYPE_BACK);
}

void Se::Reset_SeCheck()
{
	se_check = 0;
}

void Se::StopSe(int se)
{
	StopSoundMem(se);
}