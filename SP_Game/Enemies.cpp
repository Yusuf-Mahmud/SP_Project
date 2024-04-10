#include "Enemies.h"

//Enemie Set
void enemies::set(int posx = 0, int posy = 0, int heal = 50, string x = "FinalBoss", string y = "Shadow", string z = "Shield")
{
	Type = x;
	if (x == "FinalBoss")
	{
		SpriteTexture.loadFromFile("./res/Enemies/FinalBoss/" + y + '/' + z + '/' + x + ".png");
		BossHealthFont.loadFromFile("./res/Fonts/score.otf");
		BossHealthText.setFont(BossHealthFont);
		BossHealthText.setOutlineThickness(5);
		BossHealthText.setPosition(window.getSize().x / 2 - 16, 12.7);
		BossHealthText.setFillColor(Color::White);
		BossHealthBarFrame.setSize({(float)heal, 32.f});
		BossHealthBarFrame.setOrigin(heal / 2, 16);
		BossHealthBarFrame.setPosition(window.getSize().x / 2, 32);
		BossHealthBarFrame.setOutlineColor(Color::Blue);
		BossHealthBarFrame.setOutlineThickness(5);
		BossHealthBarFrame.setFillColor(Color::Transparent);
		BossHealthBar.setOrigin(heal / 2, 16);
		BossHealthBar.setPosition(window.getSize().x / 2, 32);
		BossHealthBar.setFillColor(Color::Red);
		HitAnimationHandle = 8;
	}
	else
	{
		SpriteTexture.loadFromFile("./res/Enemies/" + x + ".png");
		HitAnimationHandle = 6;
	}
	sprite.setTexture(SpriteTexture);
	sprite.setTextureRect(IntRect(0, 64 * 10, 64, 64));
	sprite.setOrigin(32, 32);
	sprite.setScale(1.5f, 1.5f);
	sprite.setPosition(posx, posy);
	IsAlive = true;
	health = heal;
}

void enemies::DealDamageTo(int &health)
{
	health -= damage;
}

//Animation
void enemies::move(string x)
{
	if (x == "right")
	{
		if (AnimationTimer < 0)
		{
			Animationi++;
			Animationi %= 9;
			sprite.setTextureRect(IntRect(64 * Animationi, 64 * 11, 64, 64));
			sprite.setOrigin(32, 32);
			AnimationTimer = AnimationDelay;
		}
		else
		{
			AnimationTimer -= DeltaTime;
		}
	}
	else if (x == "down")
	{
		if (AnimationTimer < 0)
		{
			Animationi++;
			Animationi %= 9;
			sprite.setTextureRect(IntRect(64 * Animationi, 64 * 10, 64, 64));
			sprite.setOrigin(32, 32);
			AnimationTimer = AnimationDelay;
		}
		else
		{
			AnimationTimer -= DeltaTime;
		}
	}
	else if (x == "left")
	{
		if (AnimationTimer < 0)
		{
			Animationi++;
			Animationi %= 9;
			sprite.setTextureRect(IntRect(64 * Animationi, 64 * 9, 64, 64));
			sprite.setOrigin(32, 32);
			AnimationTimer = AnimationDelay;
		}
		else
		{
			AnimationTimer -= DeltaTime;
		}
	}
	else if (x == "up")
	{
		if (AnimationTimer < 0)
		{
			Animationi++;
			Animationi %= 9;
			sprite.setTextureRect(IntRect(64 * Animationi, 64 * 8, 64, 64));
			sprite.setOrigin(32, 32);
			AnimationTimer = AnimationDelay;
		}
		else
		{
			AnimationTimer -= DeltaTime;
		}
	}
}
void enemies::die(string x)
{
	if (x == "defeated")
	{
		if (IsStanding)
		{
			if (DeathTimer < 0)
			{
				Deathi++;
				Deathi %= 4;
				sprite.setTextureRect(IntRect(64 * Deathi, 64 * 20, 64, 64));
				sprite.setOrigin(32, 32);
				DeathTimer = DeathDelay;
				if (Deathi == 3)
					IsStanding = false, Deathi = 0;
			}
			else
			{
				DeathTimer -= DeltaTime;
			}
		}
	}
	else if (x == "stand")
	{
		if (!IsStanding)
		{
			if (DeathTimer < 0)
			{
				Deathi--;
				sprite.setTextureRect(IntRect(64 * Deathi, 64 * 20, 64, 64));
				sprite.setOrigin(32, 32);
				DeathTimer = DeathDelay;
				if (Deathi == 0)
					IsStanding = true, IsAlive = true;
			}
			else
			{
				DeathTimer -= DeltaTime;
			}
		}
	}
	else
	{
		if (DeathTimer < 0)
		{
			Deathi++;
			Deathi %= 6;
			sprite.setTextureRect(IntRect(64 * Deathi, 64 * 20, 64, 64));
			sprite.setOrigin(32, 32);
			DeathTimer = DeathDelay;
			if (Deathi == 5)
				IsAlive = false;
		}
		else
		{
			DeathTimer -= DeltaTime;
		}
	}
}
void enemies::hit(string x, int& h)
{
	if (x == "up")
	{
		if (HitTimer < 0)
		{
			Hiti++;
			Hiti %= HitAnimationHandle;
			sprite.setTextureRect(IntRect(192 * Hiti, 64 * 21, 192, 192));
			sprite.setOrigin(95, 95);
			HitTimer = HitSpeed;
			if (Hiti == HitAnimationHandle - 1)
			{
				DealDamageTo(h);
			}
		}
		else
		{
			HitTimer -= DeltaTime;
		}
		}
	else if (x == "down")
	{
		if (HitTimer < 0)
		{
			Hiti++;
			Hiti %= HitAnimationHandle;
			sprite.setTextureRect(IntRect(192 * Hiti, 64 * 27, 192, 192));
			sprite.setOrigin(95, 95);
			HitTimer = HitSpeed;
			if (Hiti == HitAnimationHandle - 1)
			{
				DealDamageTo(h);
			}
		}
		else
		{
			HitTimer -= DeltaTime;
		}
		}
	else if (x == "left")
	{
		if (HitTimer < 0)
		{
			Hiti++;
			Hiti %= HitAnimationHandle;
			sprite.setTextureRect(IntRect(192 * Hiti, 64 * 24, 192, 192));
			sprite.setOrigin(95, 95);
			HitTimer = HitSpeed;
			if (Hiti == HitAnimationHandle - 1)
			{
				DealDamageTo(h);
			}
		}
		else
		{
			HitTimer -= DeltaTime;
		}
		}
	else if (x == "right")
	{
		if (HitTimer < 0)
		{
			Hiti++;
			Hiti %= HitAnimationHandle;
			sprite.setTextureRect(IntRect(192 * Hiti, 64 * 30, 192, 192));
			sprite.setOrigin(95, 95);
			HitTimer = HitSpeed;
			if (Hiti == HitAnimationHandle - 1)
			{
				DealDamageTo(h);
			}
		}
		else
		{
			HitTimer -= DeltaTime;
		}
		}
}

//Go To some sprite
void enemies::GoTo(Sprite x)
{
	ChaseDestance = (x.getPosition() - (sprite.getPosition()));
	if (sqrt(ChaseDestance.x * ChaseDestance.x + ChaseDestance.y * ChaseDestance.y) > 3)
	{
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			move("right");
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			move("down");
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			move("left");
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			move("up");
		sprite.move(normalize(ChaseDestance) * speed * DeltaTime);
	}
}

//Chasing Function
void enemies::ChaceAndHit(character &x)
{
	ChaseDestance = (x.sprite.getPosition() - (sprite.getPosition()));
	if (sqrt(ChaseDestance.x * ChaseDestance.x + ChaseDestance.y * ChaseDestance.y) > HitDistance)
	{
		Hiti = 0;
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			move("right");
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			move("down");
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			move("left");
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			move("up");
		sprite.move(normalize(ChaseDestance) * speed * DeltaTime);
	}
	else
	{
		Animationi = 0;
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			hit("right", x.health);
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			hit("down", x.health);
		if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
			hit("left", x.health);
		if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
			hit("up", x.health);
	}
}

void enemies::FinalBossDraw(character x)
{
	if (x.sprite.getPosition().y > sprite.getPosition().y)
		DrawSprite.add(sprite);
	DrawSprite.add(x.sprite);
	if (x.sprite.getPosition().y <= sprite.getPosition().y)
		DrawSprite.add(sprite);
}

void enemies::ShowHealthBar()
{
	BossHealthBar.setSize({ (float)health, 32.f });
	BossHealthText.setString(to_string(health));
	window.draw(BossHealthBar);
	window.draw(BossHealthBarFrame);
	window.draw(BossHealthText);
}