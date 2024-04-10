#pragma once
#include "CollisionManager.h"
#include "SpriteVector.h"
#ifndef GLOBALS_H 
#define GLOBALS_H 

//Window Control
extern RenderWindow window;
extern Vector2f WindowSize;

//DeltaTime and GameClock Measure
extern float DeltaTime;
extern int GameTime;

// walking to right start frame
extern const int WalkRightIndex;

// walking to left start frame
extern const int WalkLeftIndex;

// walking up start frame
extern const int WalkUpIndex;

// walking down start frame
extern const int WalkDownIndex;

extern const int HitRightIndex;
extern const int HitLeftIndex;
extern const int HitUpIndex;
extern const int HitDownIndex;

//Press Control
extern float PressTimer, PressDelay;

extern SpriteVector DrawSprite;

Vector2f normalize(Vector2f vec);
int DistanceBetween(Sprite, Sprite);
Vector2f VectorDistanceBetween(Sprite, Sprite);

#endif