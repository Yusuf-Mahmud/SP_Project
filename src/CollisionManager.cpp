#include "CollisionManager.h"

void collisionManager1::setObjectBound(Sprite & a, Sprite & b){
	ob1Bounds = a.getGlobalBounds(), ob2Bounds = b.getGlobalBounds();
}
//Testing
void collisionManager1::setObjectBound(RectangleShape& a, RectangleShape& b) {
	ob1Bounds = a.getGlobalBounds(), ob2Bounds = b.getGlobalBounds();
}
//Testing
void collisionManager1::setObjectBound(RectangleShape& a, Sprite& b) {
	ob1Bounds = a.getGlobalBounds(), ob2Bounds = b.getGlobalBounds();
}


bool collisionManager1::isColliding(Sprite& a, Sprite& b)
{ 
	setObjectBound(a, b);
	return ob1Bounds.intersects(ob2Bounds);
}
bool collisionManager1::isColliding(RectangleShape& a, RectangleShape& b)
{ 
	setObjectBound(a, b);
	return ob1Bounds.intersects(ob2Bounds);
}

float collisionManager1::calcOverlapX(FloatRect& ob1Bounds, FloatRect& ob2Bounds)
{
	return min(ob1Bounds.left + ob1Bounds.width - ob2Bounds.left, ob2Bounds.left + ob2Bounds.width - ob1Bounds.left);
}

float collisionManager1::calcOverlapY(FloatRect& a, FloatRect& b)
{
	return min(a.top + a.height - b.top, b.top + b.height - a.top);
}

void collisionManager1::Movement(Sprite& a, Sprite& b){
	
	Vector2f Dirction;
	float xOverlap = calcOverlapX( ob1Bounds ,ob2Bounds );
	float yOverlap = calcOverlapY(ob1Bounds, ob2Bounds);

	if (xOverlap < yOverlap)
		Dirction.x = (ob1Bounds.left < ob2Bounds.left) ? -xOverlap : xOverlap;
	else
		Dirction.y = (ob1Bounds.top < ob2Bounds.top) ? -yOverlap : yOverlap;

	a.move(Dirction);
}

void collisionManager1::Movement(RectangleShape& a, RectangleShape& b) {

	Vector2f Dirction;
	float xOverlap = calcOverlapX(ob1Bounds, ob2Bounds);
	float yOverlap = calcOverlapY(ob1Bounds, ob2Bounds);

	if (xOverlap < yOverlap)
		Dirction.x = (ob1Bounds.left < ob2Bounds.left) ? -xOverlap : xOverlap;
	else
		Dirction.y = (ob1Bounds.top < ob2Bounds.top) ? -yOverlap : yOverlap;

	a.move(Dirction);
}

//Collision Manager 2

void collisionManager2::setNextBound(FloatRect& ob1Bounds, Vector2f& Velocity)
{
	nextStep = ob1Bounds;
	nextStep.left += Velocity.x;
	nextStep.top += Velocity.y;
}

/*
	This Function is handling Collision by another approach (like as suraj tutorial approach)
Parameters -> 1- walls (or anything that have colliding with object
			  2- movementSpeed of object (To handle movement when colliding)
			  3- objects to check that every object(like as cheep or enemy and so on...) 
			     has been colliding with walls (or anything in map)
*/
void collisionManager2::applyCollision(vector<Sprite>& walls, Vector2f& Velocity, vector<Sprite>& objects)
{
	for (auto& object : objects) {
		for (auto& wall : walls) {
			setObjectBound(object, wall);
			setNextBound(ob1Bounds, Velocity);
			if (ob2Bounds.intersects(nextStep)) {
				//Handle Left Collision
				if (leftCollision()) {
					Velocity.x = 0;
					object.setPosition(ob2Bounds.left + ob2Bounds.width, object.getPosition().y);
				}
				//Handle Right Collision
				else if (rightCollision()) {
					Velocity.x = 0;
					object.setPosition(ob2Bounds.left - ob1Bounds.width, object.getPosition().y);
				}

				//Handle Top Collision
				if (topCollision()) {
					Velocity.y = 0;
					object.setPosition(object.getPosition().x, ob2Bounds.top + ob2Bounds.height);
				}
				//Handle Bottom Collision
				else if (bottomCollision()) {
					Velocity.y = 0;
					object.setPosition(object.getPosition().x, ob2Bounds.top - ob1Bounds.height);
				}
			}
		}
	}
}

//Testing 
void collisionManager2::applyCollision(vector<RectangleShape>& walls, Vector2f& Velocity, RectangleShape& object)
{
	for (auto& wall : walls) {
		setObjectBound(object,wall);
		setNextBound(ob1Bounds, Velocity);
		if (ob2Bounds.intersects(nextStep)) {
			//Handle Left Collision
			if (leftCollision()) {
				Velocity.x = 0;
				object.setPosition(ob2Bounds.left + ob2Bounds.width, object.getPosition().y);
			}
			//Handle Right Collision
			else if (rightCollision()) {
				Velocity.x = 0; 
				object.setPosition(ob2Bounds.left - ob1Bounds.width, object.getPosition().y);
			}

			//Handle Top Collision
			if (topCollision()) {
				Velocity.y = 0;
				object.setPosition(object.getPosition().x, ob2Bounds.top + ob2Bounds.height);
			}
			//Handle Bottom Collision
			else if (bottomCollision()) {
				Velocity.y = 0;
				object.setPosition(object.getPosition().x, ob2Bounds.top - ob1Bounds.height);
			}

		}
	}
}

//Testing 
void collisionManager2::applyCollision(vector<Sprite>& walls, Vector2f& Velocity, RectangleShape& object)
{
	for (auto& wall : walls) {
		setObjectBound(object, wall);
		setNextBound(ob1Bounds, Velocity);
		if (ob2Bounds.intersects(nextStep)) {
			//Handle Left Collision
			if (leftCollision()) {
				Velocity.x = 0;
				object.setPosition(ob2Bounds.left + ob2Bounds.width, object.getPosition().y);
			}
			//Handle Right Collision
			else if (rightCollision()) {
				Velocity.x = 0;
				object.setPosition(ob2Bounds.left - ob1Bounds.width, object.getPosition().y);
			}

			//Handle Top Collision
			if (topCollision()) {
				Velocity.y = 0;
				object.setPosition(object.getPosition().x, ob2Bounds.top + ob2Bounds.height);
			}
			//Handle Bottom Collision
			else if (bottomCollision()) {
				Velocity.y = 0;
				object.setPosition(object.getPosition().x, ob2Bounds.top - ob1Bounds.height);
			}

		}
	}
}

//Check the collision from Left side
bool collisionManager2::leftCollision()
{
	return (ob1Bounds.left > ob2Bounds.left
			&& ob1Bounds.left + ob1Bounds.width > ob2Bounds.left + ob2Bounds.width
			&& ob1Bounds.top < ob2Bounds.top + ob2Bounds.height
			&& ob2Bounds.top < ob1Bounds.top + ob2Bounds.height);
}

//Check the collision from Right side
bool collisionManager2::rightCollision()
{
	return (ob1Bounds.left < ob2Bounds.left
			&& ob1Bounds.left + ob1Bounds.width < ob2Bounds.left + ob2Bounds.width
			&& ob1Bounds.top < ob2Bounds.top + ob2Bounds.height
			&& ob2Bounds.top < ob1Bounds.top + ob2Bounds.height);
}


//Check the collision from Top 
bool collisionManager2::topCollision()
{
	return (ob1Bounds.top > ob2Bounds.top
			&& ob1Bounds.top + ob1Bounds.height > ob2Bounds.top + ob2Bounds.height
			&& ob1Bounds.left < ob2Bounds.left + ob2Bounds.width
			&& ob2Bounds.left < ob1Bounds.left + ob1Bounds.width);
}

//Check the collision from Bottom 
bool collisionManager2::bottomCollision()
{
	return (ob1Bounds.top < ob2Bounds.top
			&& ob1Bounds.top + ob1Bounds.height < ob2Bounds.top + ob2Bounds.height
			&& ob1Bounds.left < ob2Bounds.left + ob2Bounds.width
			&& ob2Bounds.left < ob1Bounds.left + ob1Bounds.width);
}


bool collisionManager1::CollidingWithScreenBounderies(Window& window, RectangleShape& object)
{
	FloatRect objectBounds = object.getGlobalBounds();
	bool isCollidWithLeftBound = (objectBounds.left <= 0);
	bool isCollidWithRightBound = (objectBounds.left + objectBounds.width > window.getSize().x);
	bool isCollidWithTopBound = (objectBounds.top <= 0);
	bool isCollidWithBottomBound = (objectBounds.top + objectBounds.height > window.getSize().y);
	return (isCollidWithLeftBound || isCollidWithRightBound || isCollidWithTopBound || isCollidWithBottomBound);
}
bool collisionManager1::CollidingWithScreenBounderies(Window& window, Sprite& object)
{
	FloatRect objectBounds = object.getGlobalBounds();
	bool isCollidWithLeftBound = (objectBounds.left <= 0);
	bool isCollidWithRightBound = (objectBounds.left + objectBounds.width > window.getSize().x);
	bool isCollidWithTopBound = (objectBounds.top <= 0);
	bool isCollidWithBottomBound = (objectBounds.top + objectBounds.height > window.getSize().y);
	return (isCollidWithLeftBound || isCollidWithRightBound || isCollidWithTopBound || isCollidWithBottomBound);
}




