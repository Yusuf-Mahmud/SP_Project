#pragma once
#include "temp.h"

struct enemies
{
	//Enemie Controls
	int health = 5, damage = 10, HitDistance = 60;
	float speed = 150, HitSpeed = 0.1;
	bool IsAlive = true, IsStanding = true;

	//Monster Spawn Controls 
	int SpawnDelay = 10; //Delay is random So (Max = SpawnDelay + Min - 1) & (Min = 3)
	int ls = 3; // (Min)

	//Constants
	string Type;
	int Animationi = 0, Hiti = 0, Deathi = 0;
	float AnimationTimer = 0, HitTimer = 0, DeathTimer = 0;
	float AnimationDelay = 10 / speed, DeathDelay = 0.5;
	int HitAnimationHandle = 6;
	RectangleShape BossHealthBar, BossHealthBarFrame;
	Font BossHealthFont;
	Text BossHealthText;
	Vector2f ChaseDestance;
	Sprite sprite;
	Texture SpriteTexture;

	//Teeeeest
	//aaah
	void set(int, int, int, string, string, string);
	void DealDamageTo(int&);
	void move(string);
	void hit(string, int&);
	void die(string);
	void GoTo(Sprite);
	void ChaceAndHit(rects &);
	Vector2f VectorDistanceBetween(RectangleShape);
	int DistanceBetween(Sprite);
	void FinalBossDraw(rects);
	void SpawnAndChace(rects &);
	bool MonstersKill(rects);
};