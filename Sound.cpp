#include"Sound.h"

void Bgm::Play(int bgm)
{
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

void Bgm::ChangeBgm(int bgm_1, int bgm_2,int mode)
{
	if (CheckMusic() == 0)
	{
		if (mode == 1)
		{
			if (CheckSoundMem(bgm_1) == 1)
			{
				StopMusic();
				PlaySoundMem(bgm_2,DX_PLAYTYPE_LOOP);

			}
			else
			{
				if (CheckMusicMem(bgm_2) == 1)
				{
					StopMusic();
					PlaySoundMem(bgm_1, DX_PLAYTYPE_LOOP);
				}
			}
		}
	}
}