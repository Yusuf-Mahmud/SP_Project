#include "GameScenes.h"
#include "global.h"

//Window Control
RenderWindow window(VideoMode(1680, 800), "SP_Game");

//Game Time Control
float DeltaTime = 0;
int GameTime = 0;

//Temp Hero
rects hero;

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

void Game::Begin()
{
	srand(time(0));

	enemies FinalBoss, Monster;
	FinalBoss.HitDistance = 100;
	FinalBoss.HitSpeed = 0.07;
	FinalBoss.damage = 10;
	FinalBoss.health = 50;
	FinalBoss.set(500, 400, 500, "FinalBoss", "Shadow", "Shield"); //set(StartPosX, StartPosY, Health, Type, Shadow?, Shield?)
	Monster.set(0, 0, 0, "", "", ""); //Empty strings as "SpawnAndChase" functoin generates them

	hero.size = { 50, 50 };
	hero.health = 50;
	hero.set();

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

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
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
			hero.move();
			if (FinalBoss.IsAlive && FinalBoss.health > 0)
			{
				FinalBoss.ChaceAndHit(hero);
				FinalBoss.FinalBossDraw(hero);
				if (FinalBoss.health < 0)
					FinalBoss.health = 0;
				FinalBoss.BossHealthBar.setSize({ (float)FinalBoss.health, 32.f });
				FinalBoss.BossHealthText.setString(to_string(FinalBoss.health));
				window.draw(FinalBoss.BossHealthBar);
				window.draw(FinalBoss.BossHealthBarFrame);
				window.draw(FinalBoss.BossHealthText);
			}
		}
		else if (scene.scene2ch)
		{
			// To look at the hero when he defeat him
			if (hero.health <= 0)
				hero.health = 2;
			Vector2f ChaseDestance = FinalBoss.VectorDistanceBetween(hero.rect);
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
			scene.scene2(FinalBoss, hero);
		}
		else if (hero.state == "sleep")
		{
			FinalBoss.health = 500;
			if (hero.TestDelay < 0)
			{
				hero.state = "BeingStronger";
				hero.rect.setPosition(window.getSize().x / 2, window.getSize().y / 2);
				hero.TestDelay = 4;
			}
			else
				hero.TestDelay -= DeltaTime;
		}
		else if (hero.state == "BeingStronger")
		{
			if (scene.IsBlinking)
			{
				window.draw(hero.rect);
				scene.blink();
			}
			else
			{
				//GamePlay
				if (hero.kills >= 5)
				{
					if (Monster.MonstersKill(hero))
					{
						destance = {(hero.rect.getPosition().x - ((float)window.getSize().x)),(hero.rect.getPosition().y - ((float)window.getSize().y / 2)) };
						if (sqrt(destance.x * destance.x + destance.y * destance.y) > 3)
						{
							hero.rect.move(-1.f * normalize(destance) * 500.f * DeltaTime);
							window.draw(hero.rect);
						}
						else
						{
							if (hero.TestDelay < 0)
							{
								hero.state = "FinalBossFight";
								hero.rect.setPosition(0, window.getSize().y / 2);
								hero.TestDelay = 4;
							}
							else
								hero.TestDelay -= DeltaTime;
						}
					}
				}
				else
				{
					hero.move();
					Monster.SpawnAndChace(hero);
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
				if (FinalBoss.IsAlive && FinalBoss.health > 0)
				{
					FinalBoss.ChaceAndHit(hero);
					FinalBoss.FinalBossDraw(hero);
					FinalBoss.BossHealthBar.setSize({ (float)FinalBoss.health, 32.f });
					FinalBoss.BossHealthText.setString(to_string(FinalBoss.health));
					window.draw(FinalBoss.BossHealthBar);
					window.draw(FinalBoss.BossHealthBarFrame);
					window.draw(FinalBoss.BossHealthText);
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
				FinalBoss.BossHealthBar.setSize({ (float)FinalBoss.health, 32.f });
				FinalBoss.BossHealthText.setString(to_string(FinalBoss.health));
				window.draw(FinalBoss.BossHealthBar);
				window.draw(FinalBoss.BossHealthBarFrame);
				window.draw(FinalBoss.BossHealthText);
				FinalBoss.die("defeated");
				scene.scene4(FinalBoss, hero);
			}
		}
		/*else if (FinalBoss.IsAlive)
		{
			FinalBoss.die();
			window.draw(FinalBoss.BossHealthBar);
			window.draw(FinalBoss.BossHealthBarFrame);
			window.draw(FinalBoss.BossHealthText);
			window.draw(FinalBoss.sprite);
			window.draw(hero.rect);
		}
		else if (!FinalBoss.IsAlive)
		{
			window.draw(hero.rect);
		}*/
		window.display();
		window.clear();

		

		DeltaTime = DTclock.getElapsedTime().asSeconds();
	}
}