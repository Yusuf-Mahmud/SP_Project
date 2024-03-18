#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

string mainHero;

string weapon;
bool isWeapon = 0;

RenderWindow window(VideoMode::getDesktopMode(), "Game");
float windowWidth = window.getSize().x;
float windowHight = window.getSize().y;

void gamePlay();
void chooseHero();

