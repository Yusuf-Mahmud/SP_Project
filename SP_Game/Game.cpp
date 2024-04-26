#include "Game.h"
#include "DayAndNight.h"

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
	return 0;
}

DayAndNight dn;
GameScenes blink;
void Game::play(character &hero)
{
	//GamePlay
	hero.InCave = 0;
	if (blink.Blinking && !hero.IsAlive)
	{
		dn.night.setSize(WindowSize * 2.0f);
		dn.DNclock.restart();
		dn.night.setFillColor(Color(0, 0, 0, dn.DarkI));
		window.draw(hero.sprite);
		blink.blink();
		window.draw(dn.night);
	}
	else if (!hero.IsAlive)
	{
		hero.die("stand");
		hero.lastKey = "down";
		DrawSprite.add(hero.sprite);
		window.draw(dn.night);
	}
	else
	{
		blink.BlinkReset();

		//If the player Level increase The Upgrade screen will open
		if (hero.IsUpdating)
		{
			hero.SkillUpdate(hero.damage, hero.MaxHealth, hero.MaxStamina, hero.walk, hero.HitSpeed);
			hero.run = hero.walk + (hero.walk * (60.0 / 100));
			hero.StaminaBarSet(hero.MaxStamina);
			hero.HealthBarSet(hero.MaxHealth);
		}
		else
		{
			dn.flow();
			if (dn.DayDate >= 3)
			{
				DrawSprite.add(hero.sprite);
				bool chi = ThereIsMonsters();
				if (!chi)
				{
					hero.GoTo({ WindowSize.x, WindowSize.y / 2 }, 3, 300);
					if (hero.arrive)
					{
						hero.ChangeWeapon("LongSword");
						hero.state = "FinalBossFight";
						hero.InCave = 1;
						hero.sprite.setPosition(0, window.getSize().y / 2);
						hero.arrive = 0;
					}
				}
				else
				{
					hero.walking.pause();
					MonstersKill();
				}
				window.draw(dn.night);
			}
			else
			{
				if (!dn.Day)
				{
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
						if (hero.var == 6 && (hero.weapon == "LongSword" || hero.weapon == "Saber"))
							hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
						else if (hero.var == 0 && (hero.weapon == "Axe" || hero.weapon == "Pickaxe"))
							hero.var = 6, hero.IsAttacking = 0, hero.IsWalking = 1;
					}
				}
				else
				{
					//As The Stop hitting Handling is at the (DealDamage()) Function
					if (hero.var == 6 && (hero.weapon == "LongSword" || hero.weapon == "Saber"))
						hero.var = 0, hero.IsAttacking = 0, hero.IsWalking = 1;
					else if (hero.var == 0 && (hero.weapon == "Axe" || hero.weapon == "Pickaxe"))
						hero.var = 6, hero.IsAttacking = 0, hero.IsWalking = 1;
					if (ThereIsMonsters())
						MonstersKill();
					DrawSprite.add(hero.sprite);
				}
				window.draw(dn.night);
				hero.play();
			}
		}
	}
}