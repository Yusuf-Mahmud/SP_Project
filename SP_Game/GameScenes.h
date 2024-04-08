#pragma once
#include "Game.h"

struct GameScenes
{
	bool IsBlinking = 1, scene0ch = 1, scene1ch = 1, scene2ch = 1, scene3ch = 1, scene4ch = 1;

	void blink();
	void Scene0Set();
	void scene0(enemies&, character&);
	void Scene1Set(enemies&, character&);
	void scene1(enemies&, character&);
	void Scene2Set();
	void scene2(enemies&, character&);
	void Scene3Set();
	void scene3(enemies&, character&);
	void Scene4Set();
	void scene4(enemies&, character&);
};