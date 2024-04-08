#pragma once
#include "includes.h"
#include "global.h"

struct character
{

	int score = 0, health = 200;
	float speed = 200;
	bool IsAlive = 0, isWeapon = 0, Walk = 0, isAttacking = 0;

	float AnemationTimer = 0, AnemationDelay = 0.1f;
	float HitTimer = 0, HitDelay = 0.05f;
	int AnimationI = 0, HitI = 0;

	string who, weapon, lastKey, state = "sleep";
	Vector2i HeroSize = { 64, 64 };
	const Vector2f scale = { 1.5, 1.5 };
	Sprite sprite;
	Texture tHero;

	void set(int posx, int posy, int heal);
	void walkRight();
	void walkLeft();
	void walkUp();
	void walkDown();
	void takeSword();
	void move();
	void hit();
	void chooseHero();
};