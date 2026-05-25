#pragma once

class Time
{
public:
	int h;
	int m;
	int s;
	int frame_count;

	void Set();
	void Count();
};