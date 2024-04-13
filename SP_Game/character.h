#pragma once
#include "includes.h"
#include "global.h"

struct character
{
	//Stamina Control
	int stamina = 100, MaxStamina = 100;//Initial Stamina
	float StaminaConsumtionTime = 0, StaminaConsumtionDelay = 0.01;
	float StaminaRestoreTime = 0, StaminaRestoreDelay = 0.1;

	//Speed Control
	float walk = 150, speed = walk;//Initial Speed
	float run = walk + (walk * (50.0 / 100));

	//Helth Control
	int health = 20, MaxHealth = 100;//Initial Health
	float HealthRestoreTime = 0, HealthRestoreDelay = 0.1;

	//Hit Control
	int damage = 100, HitDistance = 60;
	float HitSpeed = 0.1f;

	//Death Control
	float DeathDelay = 0.5;


	//Not Controls (Don't touch)
	int score = 0, var;
	bool IsAlive = 0, IsWeapon = 0, IsWalking = 0, IsAttacking = 0, IsStanding = 1, arrive = 0;
	float AnemationTimer = 0, HitTimer = 0, DeathTimer = 0;
	int AnimationI = 0, HitI = 0, DeathI = 0;
	float AnemationDelay = 10 / speed;

	string who, weapon = "Saber", shadow = "NoShadow", lastKey, state = "sleep";
	Vector2i HeroSize = { 64, 64 };
	Vector2f scale = { 1.5, 1.5 };
	Sprite sprite;
	Texture tHero;
	Sound walking;
	SoundBuffer Bwalking;
	RectangleShape HealthBar, HealthBarFrame;
	Font HealthFont;
	Text HealthText;
	RectangleShape StaminaBar, StaminaBarFrame;
	Font StaminaFont;
	Text StaminaText;

	void set(int posx, int posy);
	void HealthBarSet(int NewHeal);
	void StaminaBarSet(int NewStamina);
	void walkRight(bool Move);
	void walkLeft(bool Move);
	void walkUp(bool Move);
	void walkDown(bool Move);
	void ChangeWeapon(string weapon);
	void ChangeShadow(string shadow);
	void move();
	void die(string);
	void hit();
	void DealDamage(Sprite&, int& heal);
	void GoTo(Vector2f Destination,int DestanceToStopBeforeDestenation, int Speed);
	void chooseHero();
	void ShowHealthBar();
	void ShowStaminaBar();
};