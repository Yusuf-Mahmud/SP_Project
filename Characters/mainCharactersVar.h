#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

string mainHero;

string weapon;
bool isWeapon = 0, Walk = 0, isAttacking;

RenderWindow window(VideoMode::getDesktopMode(), "Game");
Vector2u windowSize = window.getSize();
int HeroWidth{ 64 }, HeroLength{ 64 }, HitI;
bool x = false;
int AnimationI;
float dt;
float AnemationTimer, AnemationDelay{0.01f};
float HitTimer, HitDelay{ 0.05 };
void heroAnimations();
void chooseHero();


