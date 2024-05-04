#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

using namespace std;
using namespace sf;

class menu
{
public:
	Text mainMenu[3];
	menu(float width, float hight);
	void draw(RenderWindow& window);
	void Up();
	void Down();
	void setSelected(int s);
	int preesed()
	{
		return selected;
	}
	~menu();
private:
	int selected;
	Font font;
};