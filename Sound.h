#pragma once
#include "main.h"

class Bgm
{
public:

	//	‚a‚f‚l‚ğ–Â‚ç‚·
	void Set(int bgm);

	//	‚a‚f‚lØ‚è‘Ö‚¦
	void ChangeBgm(int bgm_1,int bgm_2,int scene);

	void StopBgm(int bgm);
};

class Se
{

public:
	
	int se_check;

	void PlaySe(int se);

	void Reset_SeCheck();

	void StopSe(int se);
};