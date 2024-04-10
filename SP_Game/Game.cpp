#include "GameScenes.h"
#include "global.h"

//Press Control
float PressTimer = 0, PressDelay = 0.19;

SpriteVector DrawSprite;

//Enemies Spawn
//Monster Spawn Controls 
int SpawnDelay = 10; //Delay is random So (Max = SpawnDelay + Min - 1) & (Min = 3)
int ls = 3; // (Min)
bool chidx = 0; int FirstIdx = 0; //Show the first apear of monsters in draw array
const int MaxMonsterSpawn = 10;
bool enemiesch[MaxMonsterSpawn] = {};
enemies Monsters[MaxMonsterSpawn] = {};
void SpawnAndChace(character& x)
{
	if (GameTime % SpawnDelay == ls)
	{
		for (int i = 0; i < MaxMonsterSpawn; i++)
		{
			if (enemiesch[i] == 0)
			{
				cout << "Spawn " << i << endl;
				enemiesch[i] = 1;
				int x = rand() % 2;
				if (x)
					Monsters[i].set(rand() % window.getSize().x + 1, rand() % window.getSize().y + 1, 50, "Skelaton", "", "");
				else
					Monsters[i].set(rand() % window.getSize().x + 1, rand() % window.getSize().y + 1, 50, "Zombie", "", "");
				break;
			}
		}
		ls = rand() % SpawnDelay;
	}
	for (int i = 0; i < MaxMonsterSpawn; i++)
	{
		if (enemiesch[i] == 1)
		{
			if (Monsters[i].IsAlive && Monsters[i].health > 0)
			{
				Monsters[i].ChaceAndHit(x);
				DrawSprite.add(Monsters[i].sprite);
			}
			else if (Monsters[i].IsAlive)
			{
				Monsters[i].die("");
				DrawSprite.add(Monsters[i].sprite);
			}
			else if (!Monsters[i].IsAlive)
			{
				cout << "Erase " << i << endl;
				x.score++;
				enemiesch[i] = 0;
			}
		}
	}
	DrawSprite.add(x.sprite);
}

bool MonstersKill(character h)
{
	DrawSprite.add(h.sprite);
	for (int i = 0; i < MaxMonsterSpawn; i++)
	{
		if (enemiesch[i] == 1)
		{
			if (Monsters[i].IsAlive)
			{
				Monsters[i].die("");
				DrawSprite.add(Monsters[i].sprite);
			}
			else if (!Monsters[i].IsAlive)
			{
				cout << "Erase " << i << endl;
				enemiesch[i] = 0;
			}
		}
	}
	int j;
	for (j = 0; j < MaxMonsterSpawn; j++)
	{
		if (enemiesch[j] == 1)
			break;
	}
	if (j == MaxMonsterSpawn)
		return 1;
	else
		return 0;
}



//Window Control
RenderWindow window(VideoMode(1680, 900), "SP_Game");
Vector2f WindowSize = { (float)window.getSize().x, (float)window.getSize().y };

//Game Time Control
float DeltaTime = 0;
int GameTime = 0;

// walking to right start frame
const int WalkRightIndex = 64 * 11;

// walking to left start frame
const int WalkLeftIndex = 9 * 64;

// walking up start frame
const int WalkUpIndex = 8 * 64;

// walking down start frame
const int WalkDownIndex = 10 * 64;

const int HitRightIndex = 30 * 64;
const int HitLeftIndex = 24 * 64;
const int HitUpIndex = 21 * 64;
const int HitDownIndex = 27 * 64;

//Game Scene Tests
float TestTimer = 0, TestDelay = 4;

//Normalize to auto move
Vector2f normalize(Vector2f vec)
{
	float mag = sqrtf(vec.x * vec.x + vec.y * vec.y);
	if (mag != 0)
	{
		vec.x /= mag;
		vec.y /= mag;
	}
	return vec;
}

//Get the distance between two Sprites
int DistanceBetween(Sprite x, Sprite y)
{
	Vector2f Destance;
	Destance = (x.getPosition() - (y.getPosition()));
	return sqrt(Destance.x * Destance.x + Destance.y * Destance.y);
}

Vector2f VectorDistanceBetween(Sprite x, Sprite y)
{
	return (x.getPosition() - (y.getPosition()));
}

void Game::Begin()
{
	//temp
	RectangleShape r;
	r.setSize(Vector2f(20, 20));
	r.setPosition(500, 500);
	r.setFillColor(Color::White);


	srand(time(0));

	enemies FinalBoss;
	FinalBoss.HitDistance = 100;
	FinalBoss.HitSpeed = 0.07;
	FinalBoss.damage = 10;
	FinalBoss.health = 50;
	FinalBoss.set(500, 400, 500, "FinalBoss", "Shadow", "Shield"); //set(StartPosX, StartPosY, Health, Type, Shadow?, Shield?)

	character hero;
	hero.chooseHero();
	hero.set(0, 0, 50);

	GameScenes scene;
	scene.Scene0Set();
	scene.Scene1Set(FinalBoss, hero);
	scene.Scene2Set();
	scene.Scene3Set();
	scene.Scene4Set();

	Clock DTclock;
	Clock GameClock;

	Vector2f destance;

	while (window.isOpen())
	{
		DTclock.restart();
		GameTime = GameClock.getElapsedTime().asSeconds();
		for (int i = 0; i < WindowSize.y; i++)
		{
			for (int j = 0; j < DrawSprite.size(); j++)
			{
				if ((int)DrawSprite.pvec[j].getPosition().y == i)
					window.draw(DrawSprite.pvec[j]);
			}
		}
		DrawSprite.clear();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		while (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			scene.skip = 1;
			scene.typing.pause();
		}

		if (scene.scene0ch)
		{
			scene.scene0(FinalBoss, hero);
		}
		else if (scene.scene1ch)
		{
			scene.scene1(FinalBoss, hero);
		}
		else if (hero.health > 20 && scene.scene2ch)
		{
			if (hero.sprite.getGlobalBounds().intersects(r.getGlobalBounds())) 
			{
				hero.weapon = "sword";
				hero.IsWeapon = true;
				r.setPosition(10000, 10000);
				hero.takeSword();
			}
			hero.move();
			hero.hit();
			hero.DealDamage(FinalBoss.sprite, FinalBoss.health); 
			if (hero.var == 6)
				hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
			if (FinalBoss.IsAlive && FinalBoss.health > 0)
			{
				FinalBoss.ChaceAndHit(hero);
				DrawSprite.add(FinalBoss.sprite);
				DrawSprite.add(hero.sprite);
				if (FinalBoss.health < 0)
					FinalBoss.health = 0;
				FinalBoss.ShowHealthBar();
			}
			window.draw(r);
		}
		else if (scene.scene2ch)
		{
			// To look at the hero when he defeat him
			if (hero.health <= 0)
				hero.health = 2;
			Vector2f ChaseDestance = VectorDistanceBetween(hero.sprite, FinalBoss.sprite);
			if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			{
				FinalBoss.sprite.setTextureRect(IntRect(0, 64 * 11, 64, 64));
				FinalBoss.sprite.setOrigin(32, 32);
			}
			if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			{
				FinalBoss.sprite.setTextureRect(IntRect(0, 64 * 10, 64, 64));
				FinalBoss.sprite.setOrigin(32, 32);
			}
			if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			{
				FinalBoss.sprite.setTextureRect(IntRect(0, 64 * 9, 64, 64));
				FinalBoss.sprite.setOrigin(32, 32);
			}
			if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			{
				FinalBoss.sprite.setTextureRect(IntRect(0, 64 * 8, 64, 64));
				FinalBoss.sprite.setOrigin(32, 32);
			}
			if (hero.health <= 0)
				hero.health = 2;
			hero.die("defeated");
			scene.scene2(FinalBoss, hero);
		}
		else if (hero.state == "sleep")
		{
			FinalBoss.health = 500;
			if (TestDelay < 0)
			{
				hero.state = "BeingStronger";
				hero.sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
				TestDelay = 4;
			}
			else
				TestDelay -= DeltaTime;
		}
		else if (hero.state == "BeingStronger")
		{
			if (scene.IsBlinking)
			{
				window.draw(hero.sprite);
				scene.blink();
			}
			else if (!hero.IsAlive)
			{
				hero.die("stand");
				hero.lastKey = "down";
				DrawSprite.add(hero.sprite);
			}
			else
			{
				//GamePlay
				if (hero.score >= 5)
				{
					hero.walk.pause();
					if (MonstersKill(hero))
					{
						destance = {(hero.sprite.getPosition().x - WindowSize.x),(hero.sprite.getPosition().y - (WindowSize.y / 2)) };
						if (sqrt(destance.x * destance.x + destance.y * destance.y) > 3)
						{
							hero.GoTo({WindowSize.x, WindowSize.y / 2});
							DrawSprite.add(hero.sprite);
						}
						else
						{
							if (TestDelay < 0)
							{
								hero.state = "FinalBossFight";
								hero.sprite.setPosition(0, window.getSize().y / 2);
								TestDelay = 4;
							}
							else
								TestDelay -= DeltaTime;
						}
					}
				}
				else
				{
					hero.move();
					hero.hit();
					SpawnAndChace(hero);
					for (int i = 0; i < MaxMonsterSpawn; i++)
					{
						if (enemiesch[i] == 1)
							hero.DealDamage(Monsters[i].sprite, Monsters[i].health);
						if (i == MaxMonsterSpawn - 1 && hero.var == 6)
							hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
					}
				}
			}
		}
		if (hero.state == "FinalBossFight")
		{
			if (scene.scene3ch)
			{
				FinalBoss.sprite.setOrigin(32, 32);
				FinalBoss.sprite.setPosition(window.getSize().x * 3 / 4, window.getSize().y / 2);
				FinalBoss.sprite.setTextureRect(IntRect(0, 64 * 9, 64, 64));
				scene.scene3(FinalBoss, hero);
			}
			else if (FinalBoss.health > 20 && scene.scene4ch)
			{
				hero.move();
				hero.hit();
				hero.DealDamage(FinalBoss.sprite, FinalBoss.health); 
				if (hero.var == 6)
					hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
				if (FinalBoss.IsAlive && FinalBoss.health > 0)
				{
					FinalBoss.ChaceAndHit(hero);
					DrawSprite.add(FinalBoss.sprite);
					DrawSprite.add(hero.sprite);
					FinalBoss.ShowHealthBar();
				}
			}
			else if (scene.scene4ch)
			{
				if (FinalBoss.health <= 0)
					FinalBoss.health = 2;
				//to make the hero look at the boss when defeat him
				/*Vector2f ChaseDestance = FinalBoss.VectorDistanceBetween(hero.rect);
				if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
				{
					FinalBoss.sprite.setTextureRect(IntRect(0, 64 * 11, 64, 64));
					FinalBoss.sprite.setOrigin(32, 32);
				}
				if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
				{
					FinalBoss.sprite.setTextureRect(IntRect(0, 64 * 10, 64, 64));
					FinalBoss.sprite.setOrigin(32, 32);
				}
				if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
				{
					FinalBoss.sprite.setTextureRect(IntRect(0, 64 * 9, 64, 64));
					FinalBoss.sprite.setOrigin(32, 32);
				}
				if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
				{
					FinalBoss.sprite.setTextureRect(IntRect(0, 64 * 8, 64, 64));
					FinalBoss.sprite.setOrigin(32, 32);
				}*/
				FinalBoss.ShowHealthBar();
				FinalBoss.die("defeated");
				scene.scene4(FinalBoss, hero);
			}
		}
		/*else if (FinalBoss.IsAlive)
		{
			FinalBoss.die();
			DrawSprite.add(FinalBoss.BossHealthBar);
			DrawSprite.add(FinalBoss.BossHealthBarFrame);
			DrawSprite.add(FinalBoss.BossHealthText);
			DrawSprite.add(FinalBoss.sprite);
			DrawSprite.add(hero.rect);
		}
		else if (!FinalBoss.IsAlive)
		{
			DrawSprite.add(hero.rect);
		}*/
		window.display();
		window.clear();

		

		DeltaTime = DTclock.getElapsedTime().asSeconds();
	}
}