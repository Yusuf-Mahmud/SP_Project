#include "Game.h"
#include "global.h"

//Sprite flow control
SpriteVector DrawSprite;


//Window Control
RenderWindow window(VideoMode(1280, 720), "siltara");
Vector2f WindowSize = { (float)window.getSize().x, (float)window.getSize().y };

//Control DeltaTime
float DeltaTime = 0;
Clock DTclock;

//Count the game time begin from it's run
int GameTime = 0;
Clock GameClock;

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

void Story::Begin()
{
	srand(time(0));//Randoms the (rand()) Function

	Game game;

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


	//Count the need time to avoid the FinalBoss and win
	Clock WinClock;
	int WiningNeedTime = 10; //Time That The Player need to survive while avoiding Siltara's attacks to win
	bool IsWining = 0;

	//Last Scene instructions
	Font f;
	Text te;
	f.loadFromFile("./res/Fonts/minecraft_font.ttf");
	te.setFont(f);
	te.setString("I Cant kill My best Friend");
	te.setFillColor(Color::White);
	te.setOrigin(te.getLocalBounds().getSize() / 2.f);
	te.setPosition(WindowSize.x / 2, window.getSize().y - te.getCharacterSize() * 5);
	te.setScale(WindowSize.x / 1600, WindowSize.y / 900);

	while (window.isOpen())
	{
		//Calculate Delta And Game Time
		DeltaTime = DTclock.restart().asSeconds();
		GameTime = GameClock.getElapsedTime().asSeconds();


		//Temp, Hide the mouse cursor
		window.setMouseCursorVisible(1);

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
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}

		//Control Hero's Shadow Display
		if (hero.InCave && hero.shadow == "Shadow")
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
			hero.play();
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
				hero.ShowHungerBar();
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
			hero.ChangeWeapon("Pickaxe");
			hero.sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
			scene.Blinking = 1;
		}
		else if (hero.state == "BeingStronger")
		{
			game.play(hero);
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
				if (hero.health > 0)
				{
					hero.play();
					hero.DealDamage(FinalBoss.sprite, FinalBoss.health);
					FinalBoss.ChaceAndHit(hero);
					DrawSprite.add(FinalBoss.sprite);
					DrawSprite.add(hero.sprite);
					FinalBoss.ShowHealthBar();
				}
				else
				{
					hero.die("");
					hero.state = "BeingStronger";
				}
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
				if (hero.health > 0)
				{
					if (FinalBoss.health > 2)
					{
						hero.play();
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
						hero.play();
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
				else
				{
					hero.die("");
					hero.state = "BeingStronger";
					hero.reset();
					FinalBoss.reset();
				}
			}
			else if (scene.scene6ch)
			{
				hero.walking.pause();
				scene.scene6(FinalBoss, hero);
			}
		}

		window.display();

		//Temp, Control Back Ground Color
		if (hero.InCave)
			window.clear(Color::Black);
		else if (hero.IsUpdating)
			window.clear(Color(0, 0, 30, 255));
		else
			window.clear(Color(0, 200, 0, 255));
	}
}