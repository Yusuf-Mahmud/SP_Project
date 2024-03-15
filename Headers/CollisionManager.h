#ifndef CollisionManager_H_
#define CollisionManager_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

struct collisionManager1
{
	//The functionName is describes what it does (: 
	bool CollidingWithScreenBounderies(Window & , Sprite&);
	//Testing
	bool CollidingWithScreenBounderies(Window&, RectangleShape&);

	//Check if two objects is Colliding or not
	bool isColliding(Sprite& a, Sprite& b);
	//Testing
	bool isColliding(RectangleShape& a, RectangleShape& b); //Overloading Function

	//Set Bounderies
	void setObjectBound(Sprite& a, Sprite& b);
	//Testing
	void setObjectBound(RectangleShape& a, RectangleShape& b); //Overloading Function
	void setObjectBound(RectangleShape& a, Sprite& b);		   //Overloading Function

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
	void applyCollision(vector<RectangleShape>& , Vector2f& , RectangleShape& );
	void applyCollision(vector<Sprite>&, Vector2f&, RectangleShape&);


	void setNextBound(FloatRect&, Vector2f&);

	//Handle collision sides
	bool leftCollision();
	bool rightCollision();
	bool topCollision();
	bool bottomCollision();

private:
	FloatRect nextStep;
};

#endif 

