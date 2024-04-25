#ifndef CollisionManager_H_
#define CollisionManager_H_
#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<set>
#include<map>
using namespace std;
using namespace sf;
bool checkCollision(const sf::Sprite& Animal, const sf::Sprite& box2, const sf::Vector2f& velocity1);

struct collisionManager1
{
	//The functionName is describes what it does (: 
	bool CollidingWithScreenBounderies(Window&, Sprite&);
	//Testing
	bool CollidingWithScreenBounderies(Window&, RectangleShape&);

	//Check if two objects is Colliding or not
	bool isColliding(Sprite& a, Sprite& b);
	//Testing
	bool isColliding(RectangleShape& a, RectangleShape& b); //Overloading Function
	bool isColliding(Sprite& a, RectangleShape& b); //Overloading Function

	//Set Bounderies
	void setObjectBound(Sprite& a, Sprite& b);
	//Testing
	void setObjectBound(RectangleShape& a, RectangleShape& b); //Overloading Function
	void setObjectBound(RectangleShape& a, Sprite& b);		   //Overloading Function

	void setObjectBound(Sprite& a, RectangleShape& b);

	//Calculate OverLap on X-axis
	float calcOverlapX(FloatRect& ob1Bounds, FloatRect& ob2Bounds);

	//Calculate OverLap on Y-axis
	float calcOverlapY(FloatRect& a, FloatRect& b);

	//Movement when Collision
	void Movement(Sprite& s, Sprite& b);
	//Testing 
	void Movement(RectangleShape& s, RectangleShape& b); //Overloading Function

	collisionManager1() {}
	~collisionManager1() {}

protected:
	FloatRect ob1Bounds, ob2Bounds;
};

//Explain in source code
struct collisionManager2 : public collisionManager1
{
	void applyCollision(vector<Sprite>&, Vector2f&, vector<Sprite>&);
	void applyCollision(vector<RectangleShape>&, Vector2f&, RectangleShape&);
	int applyCollisionAnimal(Sprite& wall, Vector2f& Velocity, Sprite& object);
	//int applyCollision(Sprite& wall, Vector2f& Velocity, Sprite& object);
	void applyCollision(vector<Sprite>&, Vector2f&, RectangleShape&);


	void setNextBound(FloatRect&, Vector2f&);

	//Handle collision sides
	bool leftCollision();
	bool rightCollision();
	bool topCollision();
	bool bottomCollision();

	void applyCollisionWithAnimals(vector<Sprite>& walls, Vector2f& Velocity, RectangleShape& object);

private:
	FloatRect nextStep;
};

#endif