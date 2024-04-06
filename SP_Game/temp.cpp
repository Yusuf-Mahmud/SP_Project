#include "temp.h"

void rects::set()
{
	rect.setSize(size);
	rect.setOrigin(size.x / 2, size.y / 2);
	rect.setFillColor(Color::Blue);
	rect.setPosition(0, 0);
}

void rects::move()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
		rect.move(0, -speed * DeltaTime);
	if (Keyboard::isKeyPressed(Keyboard::D))
		rect.move(speed * DeltaTime, 0);
	if (Keyboard::isKeyPressed(Keyboard::S))
		rect.move(0, speed * DeltaTime);
	if (Keyboard::isKeyPressed(Keyboard::A))
		rect.move(-speed * DeltaTime, 0);
}