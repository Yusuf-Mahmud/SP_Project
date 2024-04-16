#include "GameScenes.h"
#include "global.h"

//Sprite flow control
SpriteVector DrawSprite;

//Monster Spawn Controls 
int SpawnDelay = 10; //Delay is random So (Max = SpawnDelay + Min - 1) & (Min = 3)
int ls = 3; // (Min)

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
					Monsters[i].set(rand() % window.getSize().x + 1, rand() % window.getSize().y + 1, 50, "Skelaton", "", "", 1);
				else
					Monsters[i].set(rand() % window.getSize().x + 1, rand() % window.getSize().y + 1, 50, "Zombie", "", "", 1);
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
void MonstersKill()
{
	for (int i = 0; i < MaxMonsterSpawn; i++)
	{
		if (enemiesch[i] == 1)
		{
			if (Monsters[i].IsAlive)
			{
				Monsters[i].die("");
				DrawSprite.add(Monsters[i].sprite);
			}
			else
			{
				cout << "Erase " << i << endl;
				enemiesch[i] = 0;
			}
		}
	}
}
bool ThereIsMonsters()
{
	for (int j = 0; j < MaxMonsterSpawn; j++)
	{
		if (enemiesch[j] == 1)
			return 1;
	}
	cout << "No Mosters" << endl;
	return 0;
}


//Window Control
RenderWindow window(VideoMode(1600, 900), "siltara");
Vector2f WindowSize = { (float)window.getSize().x, (float)window.getSize().y };

//Game Time Control
float DeltaTime = 0;
int GameTime = 0;

//Press Control
float PressTimer = 0, PressDelay = 0.19;


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
	srand(time(0));//Randoms the (rand()) Function

	//Initializing FinalBoss
	enemies FinalBoss;
	FinalBoss.set(500, 400, 100, "FinalBoss", "NoShadow", "NoShield", 1);
	FinalBoss.HitDistance = 100;
	FinalBoss.HitSpeed = 0.07;// As the number decrease the hit speed increase
	FinalBoss.damage = 10;

	//Initializing Hero
	character hero;
	hero.chooseHero();
	hero.set(0, 0, 1);

	//Set Game Scenes
	GameScenes scene;
	scene.GameScenesSet(FinalBoss, hero);

	//Control DeltaTime
	Clock DTclock;

	//Count the game time begin from it's run
	Clock GameClock;

	//Count the need time to avoid the FinalBoss and win
	int WiningNeedTime = 10; //Time That The Player need to survive while avoiding Siltara's attacks to win
	Clock WinClock;
	bool IsWining = 0;

	//Day and Night Control
	int darknes = 170;//As the number increase the night darknes increase
	int DNTime = 10; //Control the Day And Night Duration as Seconds
	float SunSetDelay = 0.015, SunRiseDelay = 0.015;//The Time SunSet And SunRise Take
	//Day and Night Constants
	bool Day = 0, InCave = 1; int DayDate = 0;
	float SunSetTimer = 0, SunRiseTimer = 0;
	Clock DNclock;
	RectangleShape night;
	night.setSize(WindowSize);
	night.setFillColor(Color(0, 0, 0, darknes));

	//Last Scene instructions
	Font f;
	Text te;
	f.loadFromFile("./res/Fonts/Vogue.ttf");
	te.setFont(f);
	te.setString("I Cant kill My best Friend");
	te.setFillColor(Color::White);
	te.setOrigin(te.getLocalBounds().getSize() / 2.f);
	te.setPosition(WindowSize.x / 2, window.getSize().y - te.getCharacterSize() * 5);
	te.setScale(WindowSize.x / 1600, WindowSize.y / 900);

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

		//Control Hero's Shadow Display
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
		else if (hero.health > 15 && scene.scene2ch)
		{
			if (!hero.IsWeapon)
			{
				hero.ChangeWeapon("Saber");
			}
			hero.move();
			hero.hit();
			hero.DealDamage(FinalBoss.sprite, FinalBoss.health);
			FinalBoss.ChaceAndHit(hero);
			DrawSprite.add(FinalBoss.sprite);
			DrawSprite.add(hero.sprite);
			FinalBoss.ShowHealthBar();
		}
		else if (scene.scene2ch)
		{
			FinalBoss.LookAt(hero.sprite);
			if (hero.health <= 0)
				hero.health = 2;
			hero.die("defeated");
			if (hero.IsStanding)
			{
				FinalBoss.FinalBossDraw(hero);
				hero.ShowHealthBar();
				hero.ShowStaminaBar();
				FinalBoss.ShowHealthBar();
			}
			else
				scene.scene2(FinalBoss, hero);
		}
		else if (hero.state == "Defeated")
		{
			hero.HealthBarSet(500);
			hero.health = hero.MaxHealth;
			hero.stamina = hero.MaxStamina;
			FinalBoss.health = FinalBoss.MaxHealth;
			hero.state = "BeingStronger";
			hero.ChangeWeapon("WarAxe");
			hero.sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
			scene.Blinking = 1;
		}
		else if (hero.state == "BeingStronger")
		{
			InCave = 0;
			if (scene.Blinking)
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
				window.draw(night);
			}
			else
			{
				//GamePlay

				//Day and Night Apearance
				if ((int)DNclock.getElapsedTime().asSeconds() >= DNTime)
				{
					if (Day)
					{
						if (darknes < 170)
						{
							if (SunSetTimer < 0)
							{
								darknes++;
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
						if (darknes > 0)
						{
							if (SunRiseTimer < 0)
							{
								darknes--;
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
				night.setFillColor(Color(0, 0, 0, darknes));

				//Temp Testing
				if (DayDate >= 3)
				{
					DrawSprite.add(hero.sprite);
					bool chi = ThereIsMonsters();
					if (!chi)
					{
						hero.GoTo({ WindowSize.x, WindowSize.y / 2 }, 3, 300);
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
					{
						hero.walking.pause();
						MonstersKill();
					}
					window.draw(night);
				}
				else
				{
					if (!Day)
					{
						hero.move();
						hero.hit();
						SpawnAndChace(hero);
						if (ThereIsMonsters)
						{
							for (int i = 0; i < MaxMonsterSpawn; i++)
							{
								if (enemiesch[i] == 1)
									hero.DealDamage(Monsters[i].sprite, Monsters[i].health);
							}
						}
						else
						{
							//As The Stop hitting Handling is at the (DealDamage()) Function
							if (hero.var == 6)
								hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
						}
					}
					else
					{
						hero.move();
						hero.hit();
						//As The Stop hitting Handling is at the (DealDamage()) Function
						if (hero.var == 6)
							hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
						if (ThereIsMonsters())
							MonstersKill();
						DrawSprite.add(hero.sprite);
					}
					window.draw(night);
				}
			}
		}
		else if (hero.state == "FinalBossFight")
		{
			if (scene.scene3ch)
			{
				FinalBoss.sprite.setOrigin(FinalBoss.WalkSize / 2.f);
				FinalBoss.sprite.setPosition(WindowSize.x * 3 / 4, WindowSize.y / 2);
				FinalBoss.sprite.setTextureRect(IntRect(0, FinalBoss.WalkLeftIndex, FinalBoss.WalkSize.x, FinalBoss.WalkSize.y));
				scene.scene3(FinalBoss, hero);
			}
			else if (FinalBoss.health > 15 && scene.scene4ch)
			{
				hero.move();
				hero.hit();
				hero.DealDamage(FinalBoss.sprite, FinalBoss.health);
				FinalBoss.ChaceAndHit(hero);
				DrawSprite.add(FinalBoss.sprite);
				DrawSprite.add(hero.sprite);
				FinalBoss.ShowHealthBar();
			}
			else if (scene.scene4ch)
			{
				if (FinalBoss.health <= 0)
					FinalBoss.health = 2;
				FinalBoss.ShowHealthBar();
				if (FinalBoss.IsStanding)
				{
					FinalBoss.die("defeated");
					FinalBoss.FinalBossDraw(hero);
				}
				else
					scene.scene4(FinalBoss, hero);
			}
			else if (scene.scene5ch)
			{
				scene.scene5(FinalBoss, hero);
			}
			else if (!IsWining || (int)WinClock.getElapsedTime().asSeconds() < WiningNeedTime)
			{
				if (FinalBoss.health > 2)
				{
					hero.move();
					hero.hit();
					hero.DealDamage(FinalBoss.sprite, FinalBoss.health);
					FinalBoss.ChaceAndHit(hero);
					DrawSprite.add(FinalBoss.sprite);
					DrawSprite.add(hero.sprite);
					FinalBoss.ShowHealthBar();
				}
				else if (FinalBoss.health < 1)
					FinalBoss.health = 2;
				else
				{
					if (!IsWining)
						WinClock.restart(), IsWining = 1;
					hero.move();
					hero.hit();
					//As The Stop hitting Handling is at the (DealDamage()) Function
					if (hero.var == 6)
						hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
					window.draw(te);
					FinalBoss.ChaceAndHit(hero);
					DrawSprite.add(FinalBoss.sprite);
					DrawSprite.add(hero.sprite);
					FinalBoss.ShowHealthBar();
				}
			}
			else if (scene.scene6ch)
			{
				hero.walking.pause();
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