#pragma once
#include "global.h"

struct rects
{
	float speed = 500;
	int health = 100, kills = 0;

	float TestDelay = 4;
	string state = "sleep";
	RectangleShape rect;
	Vector2f size;
	void set();
	void move();
};