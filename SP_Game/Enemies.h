#pragma once
#include "character.h"

struct enemies
{
	//Enemie Controls
	int health = 5, damage = 10, HitDistance = 60;
	float speed = 150, HitSpeed = 0.1, DeathDelay = 0.5;


	//Constants
	bool IsAlive = true, IsStanding = true, arrive = 0;
	int Animationi = 0, Hiti = 0, Deathi = 0;
	float AnimationTimer = 0, HitTimer = 0, DeathTimer = 0;
	float AnimationDelay = 10 / speed;
	int HitAnimationHandle = 6;
	string Type;
	RectangleShape BossHealthBar, BossHealthBarFrame;
	Font BossHealthFont;
	Text BossHealthText;
	Vector2f ChaseDestance;
	Sprite sprite;
	Texture SpriteTexture;

	void set(int posx, int posy, int heal, string type, string shadow, string shield);
	void DealDamageTo(int&);
	void move(string);
	void hit(string, int&);
	void die(string);
	void GoTo(Vector2f Destination, float Speed);
	void ChaceAndHit(character &);
	void FinalBossDraw(character);
	void ShowHealthBar();
};