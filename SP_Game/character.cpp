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
}

void character::walkRight()
{
    HeroSize.x = 64;
    HeroSize.y = 64;
    if (AnemationTimer < 0)
    {

        AnimationI++;
        AnimationI %= 9;
        sprite.setOrigin(HeroSize.x / 2.f, HeroSize.y / 2.f);
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkRightIndex, HeroSize.x, HeroSize.y));
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
        sprite.setOrigin(HeroSize.x / 2.f, HeroSize.y / 2.f);
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkLeftIndex, HeroSize.x, HeroSize.y));
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
        sprite.setOrigin(HeroSize.x / 2.f, HeroSize.y / 2.f);
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkUpIndex, HeroSize.x, HeroSize.y));
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
        sprite.setOrigin(HeroSize.x / 2.f, HeroSize.y / 2.f);
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkDownIndex, HeroSize.x, HeroSize.y));
    sprite.move(0, speed * DeltaTime);
    lastKey = "Down";
}

void character::move()
{
    if (lastKey == "Right")
    {

        sprite.setOrigin(Vector2f(32, 32));
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

    // moving hero
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        Walk = true;
        walkRight();

    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        Walk = true;
        walkLeft();

    }
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        Walk = true;
        walkUp();
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        Walk = true;
        walkDown();
    }
    else Walk = false;
}

void character::takeSword()
{
    tHero.loadFromFile("./res/Heros/" + who + "/NoShadow/Saber/" + who + ".png");
    sprite.setTexture(tHero);
    sprite.setScale(scale);
}

void character::hit()
{
    if (HitTimer <= HitDelay) {
        HitI++;
        if (HitI >= 6) {
            HitI = 0;
            isAttacking = false;
        }
        sprite.setOrigin(Vector2f(96, 96));
        sprite.setTextureRect(IntRect(HitI * 192, HitRightIndex, 192, 192));
        HitTimer -= DeltaTime;
    }
}