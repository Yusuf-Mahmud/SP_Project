#include "GameScenes.h"
#include "global.h"

//Press Control
float PressTimer = 0, PressDelay = 0.19;

//Sprite flow control
SpriteVector DrawSprite;

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
RenderWindow window(VideoMode(1430, 870), "siltara");
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

//Hiting Right Start Frame
const int HitRightIndex = 30 * 64;
//Hiting Left Start Frame
const int HitLeftIndex = 24 * 64;
//Hiting Up Start Frame
const int HitUpIndex = 21 * 64;
//Hiting Down Start Frame
const int HitDownIndex = 27 * 64;

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
	srand(time(0));

	//Initializing FinalBoss
	enemies FinalBoss;
	FinalBoss.set(500, 400, 500, "FinalBoss", "NoShadow", "NoShield");
	FinalBoss.HitDistance = 100;
	FinalBoss.HitSpeed = 0.07;
	FinalBoss.damage = 10;
	FinalBoss.health = 50;

	//Initializing Hero
	character hero;
	hero.chooseHero();
	hero.set(0, 0);

	//Set Game Scenes
	GameScenes scene;
	scene.GameScenesSet(FinalBoss, hero);

	//Control DeltaTime
	Clock DTclock;

	//Count the game time begin from it's run
	Clock GameClock;

	//Count the need time to avoid the FinalBoss and win
	Clock WinClock;
	bool IsWining = 0;

	//Day and Night Control
	bool Day = 0, InCave = 1; int DayDate = 0;
	Clock DNclock;
	RectangleShape night;
	int Suni = 170;
	float SunSetDelay = 0.015, SunRiseDelay = 0.015;//The Time SunSet And SunRise Take
	float SunSetTimer = 0, SunRiseTimer = 0;
	night.setSize(WindowSize);
	night.setFillColor(Color(0, 0, 0, 170));

	//Last Scenes instructions
	Font f;
	Text te;
	f.loadFromFile("./res/Fonts/Vogue.ttf");
	string ste2 = "I Cant kill My best Friend";
	te.setString(ste2);
	te.setFillColor(Color::White);
	te.setPosition(0 , window.getSize().y - te.getCharacterSize());
	te.setScale(0.8, 0.8);
	te.setFont(f);

	while (window.isOpen())
	{
		//Calculate Delta And Game Time
		DTclock.restart();
		GameTime = GameClock.getElapsedTime().asSeconds();

		//Drawing Sprites
		for (int i = 0; i < WindowSize.y; i++)
		{
			for (int j = 0; j < DrawSprite.size(); j++)
			{
				if ((int)DrawSprite.pvec[j].getPosition().y == i)
					window.draw(DrawSprite.pvec[j]);
			}
		}
		DrawSprite.clear();

		//To Exit the Game
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		//Control Shadow Display
		if (InCave && hero.shadow == "Shadow")
			hero.ChangeShadow("NoShadow");
		else if (!InCave && Day && hero.shadow == "NoShadow")
			hero.ChangeShadow("Shadow");
		else if (!InCave && !Day && hero.shadow == "Shadow")
			hero.ChangeShadow("NoShadow");

		//Starting The Game
		if (scene.scene0ch)
		{
			scene.scene0(FinalBoss, hero);
		}
		else if (scene.scene1ch)
		{
			scene.scene1(FinalBoss, hero);
			hero.health = 40;
		}
		else if (hero.health > 20 && scene.scene2ch)
		{
			if (!hero.IsWeapon) 
			{
				hero.ChangeWeapon("Saber");
			}
			hero.move();
			hero.hit();
			hero.DealDamage(FinalBoss.sprite, FinalBoss.health); 
			hero.ShowHealthBar();
			hero.ShowStaminaBar();
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
			hero.health = hero.MaxHealth;
			hero.stamina = hero.MaxStamina;
			FinalBoss.health = 500;
			hero.state = "BeingStronger";
			hero.ChangeWeapon("NoWeapon");
			hero.sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
		}
		else if (hero.state == "BeingStronger")
		{
			InCave = 0;
			if (scene.IsBlinking)
			{
				DNclock.restart();
				window.draw(hero.sprite);
				window.draw(night);
				scene.blink();
			}
			else if (!hero.IsAlive)
			{
				hero.die("stand");
				hero.lastKey = "down";
				DrawSprite.add(hero.sprite);
				hero.ShowHealthBar();
				window.draw(night);
			}
			else
			{
				//GamePlay
				if ((int)DNclock.getElapsedTime().asSeconds() >= 10)
				{
					if (Day)
					{
						if (Suni < 170)
						{
							if (SunSetTimer < 0)
							{
								Suni++;
								SunSetTimer = SunSetDelay;
							}
							else
								SunSetTimer -= DeltaTime;
						}
						else
						{
							Day = !Day;
							DNclock.restart();
						}
					}
					else
					{
						if (Suni > 0)
						{
							if (SunRiseTimer < 0)
							{
								Suni--;
								SunRiseTimer = SunRiseDelay;
							}
							else
								SunRiseTimer -= DeltaTime;
						}
						else
						{
							Day = !Day;
							DNclock.restart();
							DayDate++;
							cout << "DayDate: " << DayDate << endl;
						}
					}
				}
				night.setFillColor(Color(0, 0, 0, Suni));
				if (DayDate >= 3)
				{
					//temp
					if (MonstersKill(hero))
					{
						hero.GoTo({WindowSize.x, WindowSize.y / 2}, 3, 300);
						DrawSprite.add(hero.sprite);
						if (hero.arrive)
						{
							hero.ChangeWeapon("LongSword");
							hero.state = "FinalBossFight";
							InCave = 1;
							hero.sprite.setPosition(0, window.getSize().y / 2);
							hero.arrive = 0;
						}
					}
					else
						hero.walking.pause();
					window.draw(night);
				}
				else
				{
					if (!Day)
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
					else
					{
						hero.move();
						hero.hit();
						MonstersKill(hero);
					}
					hero.ShowHealthBar();
					window.draw(night);
				}
			}
		}
		else if (hero.state == "FinalBossFight")
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
				hero.ShowHealthBar();
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
				FinalBoss.ShowHealthBar();
				FinalBoss.die("defeated");
				scene.scene4(FinalBoss, hero);
			}
			else if (scene.scene5ch)
			{
				scene.scene5(FinalBoss, hero);
			}
			else if (!IsWining || (int)WinClock.getElapsedTime().asSeconds() < 10)
			{
				if (FinalBoss.health > 2)
				{
					hero.move();
					hero.hit();
					hero.ShowHealthBar();
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
				else if (FinalBoss.health < 1)
					FinalBoss.health = 2;
				else
				{
					if (!IsWining)
						WinClock.restart(), IsWining = 1;
					hero.move();
					hero.hit();
					hero.ShowHealthBar();
					window.draw(te);
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
			}
			else if (scene.scene6ch)
			{
				scene.scene6(FinalBoss, hero);
			}
		}

		window.display();

		//Control Back Ground Color
		if (InCave)
			window.clear(Color::Black);
		else
			window.clear(Color(0, 200, 0, 255));

		

		DeltaTime = DTclock.getElapsedTime().asSeconds();
	}
}