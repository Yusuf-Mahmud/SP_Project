#include "menu.h"

menu::menu(float width, float hight)
{
	font.loadFromFile("fonts/SuperMario256.ttf");

	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color(50, 150, 250));
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(90);
	mainMenu[0].setPosition(Vector2f(width / 2 - 200, hight / 4 + 100));

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("Details");
	mainMenu[1].setCharacterSize(90);
	mainMenu[1].setPosition(Vector2f(width / 2 - 200, hight / 4 + 300));

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(90);
	mainMenu[2].setPosition(Vector2f(width / 2 - 200, hight / 4 + 500));

	selected = 0;
}

menu::~menu() {}

void menu::setSelected(int s)
{
	selected = s;
}

void menu::draw(RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainMenu[i]);
	}
}

void menu::Down()
{
	if (selected < 3)
	{
		mainMenu[selected].setFillColor(Color::White);
		selected++;
		//if (selected == 3) selected = 0;
		selected %= 3;

		mainMenu[selected].setFillColor(Color(50, 150, 250));
	}
}

void menu::Up()
{
	if (selected  >  -1)
	{
		mainMenu[selected].setFillColor(Color::White);
		selected--;
		//if (selected == -1) selected = 2;
		selected = (selected % 2 + 2) % 2;
		mainMenu[selected].setFillColor(Color(50, 150, 222));
	}
}