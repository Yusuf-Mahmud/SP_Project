#include "includes.h"

struct SpriteVector
{
	int VecSize = 0;
	int memory = 64;
	Sprite* pvec = new Sprite[memory];

	void add(Sprite);
	void remove(int);
	void clear();
	bool empty();
	int size();
};