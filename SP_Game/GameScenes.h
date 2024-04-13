#pragma once
#include "Game.h"

struct GameScenes
{
	//Text appearance Control
	float InitTextDelay = 0.045, ComaDelay = 0.5; //Typing Speed
	float SlowTextDelay = 0.2; //While being defeated in scene 2


	//Constants
	bool IsBlinking = 1, scene0ch = 1, scene1ch = 1, scene2ch = 1, scene3ch = 1, scene4ch = 1,
		 scene5ch = 1, typech = 0, scene6ch = 1;
	float TextTimer = 0.085, TextDelay = InitTextDelay;
	SoundBuffer Btyping;
	Sound typing;
	enemies FinalBossTalk;
	character HeroTalk;

	void DisplayText(Text& t, string& s, int& idx, enemies& e, character& h, string talker);
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
	void Scene5Set();
	void scene5(enemies&, character&);
	void Scene6Set(character);
	void scene6(enemies&, character&);
};