#pragma once
#include"main.h"
#include"Hit.h"
#include"Val.h"
#include"Block.h"
#include"Time.h"

void GameInit();
void GameUpdate();
void GameRender();
void GameExit();

void GameSet();
void GamePlay();
int Kill_Count();

bool GameOver();
void EndGame_Next();