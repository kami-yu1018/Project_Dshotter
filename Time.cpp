#include "Time.h"

void Time::Set()
{
	h = 0;
	m = 0;
	s = 0;
	frame_count = 0;
}

void Time::Count()
{
	if (frame_count > 60)
	{
		frame_count = 0;
		s++;
	}
	if (s > 60)
	{
		s = 0;
		m++;
	}
	if (m > 60)
	{
		m = 0;
		h++;
	}
}