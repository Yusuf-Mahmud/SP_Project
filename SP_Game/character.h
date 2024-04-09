#pragma once
#include "includes.h"
#include "global.h"

struct character
{

	int score = 0, health = 20, HitDistance = 60, damage = 40, var;
	float speed = 200, HitSpeed = 0.1f;
	bool IsAlive = 0, IsWeapon = 0, IsWalking = 1, IsAttacking = 0, IsStanding = 1;

	float AnemationTimer = 0, HitTimer = 0, DeathTimer = 0;
	float AnemationDelay = 10 / speed, DeathDelay = 0.5;
	int AnimationI = 0, HitI = 0, DeathI = 0;

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
	void die(string);
	void hit();
	void DealDamage(Sprite&, int& heal);
	void GoTo(Vector2f);
	void chooseHero();
};