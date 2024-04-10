#include "character.h"

void character::chooseHero()
{
    RectangleShape zanaty, ramadan;
    zanaty.setSize(Vector2f(100, 100));
    ramadan.setSize(Vector2f(100, 100));
    zanaty.setPosition(Vector2f(WindowSize.x / 2 - 100, WindowSize.y / 2));
    ramadan.setPosition(Vector2f(WindowSize.x / 2 + 100, WindowSize.y / 2));
    zanaty.setFillColor(Color::Yellow);
    ramadan.setFillColor(Color::Magenta);
    Event ev;
    while (window.isOpen())
    {
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
            {
                window.close();
            }

        }
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f WmousePos = window.mapPixelToCoords(mousePos);
        if (ramadan.getGlobalBounds().contains(WmousePos))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                who = "zanaty";
                break;

            }
        }
        if (zanaty.getGlobalBounds().contains(WmousePos))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                who = "Mogiwara";
                break;
            }
        }

        window.clear();
        window.draw(zanaty);
        window.draw(ramadan);
        window.display();
    }
}

void character::set(int posx, int posy, int heal)
{
    tHero.loadFromFile("./res/Heros/" + who + "/NoShadow/NoWeapon/" + who + ".png");
    sprite.setTexture(tHero);
    sprite.setScale(scale);
    sprite.setTextureRect(IntRect(0, 64 * 6, 64, 64));
    sprite.setOrigin(32, 32);
    sprite.setPosition(posx, posy);
    lastKey = "Right";
    speed = 200;
    health = heal;
    IsAlive = 1;
    Bwalk.loadFromFile("./res/Sounds/OnStoneRun3.mp3");
    walk.setBuffer(Bwalk);
    walk.setPitch(1.2);
    walk.setVolume(10);
}

void character::walkRight()
{
    HeroSize.x = 64;
    HeroSize.y = 64;
    if (AnemationTimer < 0)
    {

        AnimationI++;
        AnimationI %= 9;
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkRightIndex, HeroSize.x, HeroSize.y));
    sprite.setOrigin(HeroSize.x / 2.f, HeroSize.y / 2.f);
    sprite.move(speed * DeltaTime, 0);
    lastKey = "Right";
}

void character::walkLeft()
{
    HeroSize.x = 64;
    HeroSize.y = 64;
    if (AnemationTimer < 0)
    {

        AnimationI++;
        AnimationI %= 9;
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkLeftIndex, HeroSize.x, HeroSize.y));
    sprite.setOrigin(HeroSize.x / 2.f, HeroSize.y / 2.f);
    sprite.move(-speed * DeltaTime, 0);
    lastKey = "Left";
}

void character::walkUp()
{
    HeroSize.x = 64;
    HeroSize.y = 64;

    if (AnemationTimer < 0)
    {

        AnimationI++;
        AnimationI %= 9;
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkUpIndex, HeroSize.x, HeroSize.y));
    sprite.setOrigin(HeroSize.x / 2.f, HeroSize.y / 2.f);
    sprite.move(0, -speed * DeltaTime);
    lastKey = "Up";
}

void character::walkDown()
{
    HeroSize.x = 64;
    HeroSize.y = 64;
    if (AnemationTimer < 0)
    {

        AnimationI++;
        AnimationI %= 9;
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkDownIndex, HeroSize.x, HeroSize.y));
    sprite.setOrigin(HeroSize.x / 2.f, HeroSize.y / 2.f);
    sprite.move(0, speed * DeltaTime);
    lastKey = "Down";
}

bool mu = 0;
void character::move()
{
    if (!IsAttacking && !IsWalking)
    {
        HeroSize = { 64, 64 };
        sprite.setOrigin(32, 32);
        if (lastKey == "Right")
        {
            sprite.setTextureRect(IntRect(0, WalkRightIndex, HeroSize.x, HeroSize.y));
        }
        else if (lastKey == "Left")
        {
            sprite.setTextureRect(IntRect(0, WalkLeftIndex, HeroSize.x, HeroSize.y));
        }
        else if (lastKey == "Up")
        {
            sprite.setTextureRect(IntRect(0, WalkUpIndex, HeroSize.x, HeroSize.y));
        }
        else if (lastKey == "Down")
        {
            sprite.setTextureRect(IntRect(0, WalkDownIndex, HeroSize.x, HeroSize.y));
        }
    }
    // moving hero
    if (IsWalking && mu == 0)
    {
        walk.play();
        walk.setLoop(1);
        mu = 1;
    }
    else if (!IsWalking && mu == 1)
    {
        walk.pause();
        mu = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkRight();
    }
    else if (Keyboard::isKeyPressed(Keyboard::A))
    {
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkLeft();
    }
    else if (Keyboard::isKeyPressed(Keyboard::W))
    {
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkUp();
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkDown();
    }
    else
        IsWalking = 0;
}

void character::die(string x)
{
    walk.pause();
    if (x == "defeated")
    {
        if (IsStanding)
        {
            if (DeathTimer < 0)
            {
                DeathI++;
                DeathI %= 4;
                sprite.setTextureRect(IntRect(64 * DeathI, 64 * 20, 64, 64));
                sprite.setOrigin(32, 32);
                DeathTimer = DeathDelay;
                if (DeathI == 3)
                    IsStanding = false;
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
                DeathI--;
                sprite.setTextureRect(IntRect(64 * DeathI, 64 * 20, 64, 64));
                sprite.setOrigin(32, 32);
                DeathTimer = DeathDelay;
                if (DeathI == 0)
                    IsStanding = true, IsAlive = true;
            }
            else
            {
                DeathTimer -= DeltaTime;
            }
        }
    }
    else if (IsAlive)
    {
        if (DeathTimer < 0)
        {
            DeathI++;
            DeathI %= 6;
            sprite.setTextureRect(IntRect(64 * DeathI, 64 * 20, 64, 64));
            sprite.setOrigin(32, 32);
            DeathTimer = DeathDelay;
            if (DeathI == 5)
                IsAlive = false;
        }
        else
        {
            DeathTimer -= DeltaTime;
        }
    }
}

void character::takeSword()
{
    tHero.loadFromFile("./res/Heros/" + who + "/NoShadow/Saber/" + who + ".png");
    sprite.setTexture(tHero);
    sprite.setScale(scale);
}

void character::hit()
{
    if (Mouse::isButtonPressed(Mouse::Left))
        IsAttacking = 1;
    if (IsWeapon && IsAttacking && !IsWalking)
    {
        AnimationI = 0;
        if (lastKey == "Right")
        {
            HeroSize = { 192, 192 };
            if (HitTimer < 0)
            {
                HitI++;
                var = HitI;
                HitI %= 6;
                sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitRightIndex, HeroSize.x, HeroSize.y));
                sprite.setOrigin(95, 95);
                HitTimer = HitSpeed;
            }
            else {
                HitTimer -= DeltaTime;
            }
            lastKey = "Right";
        }
        if (lastKey == "Left")
        {
            HeroSize.x = 192;
            HeroSize.y = 192;
            if (HitTimer < 0)
            {
                HitI++;
                var = HitI;
                HitI %= 6;
                sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitLeftIndex, HeroSize.x, HeroSize.y));
                sprite.setOrigin(95, 95);
                HitTimer = HitSpeed;
            }
            else {
                HitTimer -= DeltaTime;
            }
            lastKey = "Left";
        }
        if (lastKey == "Up")
        {
            HeroSize.x = 192;
            HeroSize.y = 192;
            if (HitTimer < 0)
            {
                HitI++;
                var = HitI;
                HitI %= 6;
                sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitUpIndex, HeroSize.x, HeroSize.y));
                sprite.setOrigin(95, 95);
                HitTimer = HitSpeed;
            }
            else {
                HitTimer -= DeltaTime;
            }
            lastKey = "Up";
        }
        if (lastKey == "Down")
        {
            HeroSize.x = 192;
            HeroSize.y = 192;
            if (HitTimer < 0)
            {
                HitI++;
                var = HitI;
                HitI %= 6;
                sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitDownIndex, HeroSize.x, HeroSize.y));
                sprite.setOrigin(95, 95);
                HitTimer = HitSpeed;
            }
            else {
                HitTimer -= DeltaTime;
            }
            lastKey = "Down";
        }
    }
}

void character::DealDamage(Sprite &s, int& h)
{
    Vector2f d = VectorDistanceBetween(sprite, s);
    if (IsWeapon && IsAttacking && !IsWalking)
    {
        if (lastKey == "Right")
        {
            if (var == 6)
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x < d.y && abs(d.x) > abs(d.y))
                    h -= damage;
            }
        }
        if (lastKey == "Left")
        {
            
            if (var == 6)
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x > d.y && abs(d.x) > abs(d.y))
                    h -= damage;
            }
        }
        if (lastKey == "Up")
        {
            if (var == 6)
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x < d.y && abs(d.x) < abs(d.y))
                    h -= damage;
            }
        }
        if (lastKey == "Down")
        {
            if (var == 6)
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x > d.y && abs(d.x) < abs(d.y))
                    h -= damage;
            }
        }
    }
}

//Go To some sprite
bool mu2 = 0;
void character::GoTo(Vector2f x)
{
    Vector2f ChaseDestance = (x - (sprite.getPosition()));
    if (sqrt(ChaseDestance.x * ChaseDestance.x + ChaseDestance.y * ChaseDestance.y) > 3)
    {
        if (!mu2)
        {
            walk.play();
            walk.setLoop(1);
            mu2 = 1;
        }
        if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
            walkRight();
        if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
            walkDown();
        if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
            walkLeft();
        if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
            walkUp();
        sprite.move(normalize(ChaseDestance) * speed * DeltaTime);
    }
    else
        walk.pause();
}