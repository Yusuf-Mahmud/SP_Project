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

void character::set(int posx, int posy)
{
    tHero.loadFromFile("./res/Heros/" + who + "/NoShadow/NoWeapon/" + who + ".png");
    sprite.setTexture(tHero);
    sprite.setScale(scale);
    sprite.setTextureRect(IntRect(0, 64 * 6, 64, 64));
    sprite.setOrigin(32, 32);
    sprite.setPosition(posx, posy);
    lastKey = "Right";
    IsAlive = 1;
    Bwalking.loadFromFile("./res/Sounds/OnStoneRun3.mp3");
    walking.setBuffer(Bwalking);
    walking.setPitch(1.2);
    walking.setVolume(10);
    HealthFont.loadFromFile("./res/Fonts/score.otf");
    HealthText.setFont(HealthFont);
    HealthText.setOutlineThickness(5);
    HealthText.setPosition(window.getSize().x / 2 - 16, WindowSize.y - 12.7 * 4);
    HealthText.setFillColor(Color::White);
    HealthBarFrame.setSize({ (float)health, 32.f });
    HealthBarFrame.setOrigin(health / 2, 16);
    HealthBarFrame.setPosition(window.getSize().x / 2, WindowSize.y - 32);
    HealthBarFrame.setOutlineColor(Color::Blue);
    HealthBarFrame.setOutlineThickness(5);
    HealthBarFrame.setFillColor(Color::Transparent);
    HealthBar.setOrigin(health / 2, 16);
    HealthBar.setPosition(window.getSize().x / 2, WindowSize.y - 32);
    HealthBar.setFillColor(Color::Red);
    MaxHealth = health;
    StaminaFont.loadFromFile("./res/Fonts/score.otf");
    StaminaText.setFont(StaminaFont);
    StaminaText.setOutlineThickness(5);
    StaminaText.setPosition(window.getSize().x * 3 / 4 - 16, WindowSize.y - 12.7 * 4);
    StaminaText.setFillColor(Color::White);
    StaminaBarFrame.setSize({ (float)stamina, 32.f });
    StaminaBarFrame.setOrigin(stamina / 2, 16);
    StaminaBarFrame.setPosition(window.getSize().x * 3 / 4, WindowSize.y - 32);
    StaminaBarFrame.setOutlineColor(Color::Blue);
    StaminaBarFrame.setOutlineThickness(5);
    StaminaBarFrame.setFillColor(Color::Transparent);
    StaminaBar.setOrigin(stamina / 2, 16);
    StaminaBar.setPosition(window.getSize().x * 3 / 4, WindowSize.y - 32);
    StaminaBar.setFillColor(Color::Green);
    MaxStamina = stamina;
}

void character::HealthBarSet(int x)
{
    HealthFont.loadFromFile("./res/Fonts/score.otf");
    HealthText.setFont(HealthFont);
    HealthText.setOutlineThickness(5);
    HealthText.setPosition(window.getSize().x / 2 - 16, WindowSize.y - 12.7 * 4);
    HealthText.setFillColor(Color::White);
    HealthBarFrame.setSize({ (float)x, 32.f });
    HealthBarFrame.setOrigin(x / 2, 16);
    HealthBarFrame.setPosition(window.getSize().x / 2, WindowSize.y - 32);
    HealthBarFrame.setOutlineColor(Color::Blue);
    HealthBarFrame.setOutlineThickness(5);
    HealthBarFrame.setFillColor(Color::Transparent);
    HealthBar.setOrigin(x / 2, 16);
    HealthBar.setPosition(window.getSize().x / 2, WindowSize.y - 32);
    HealthBar.setFillColor(Color::Red);
    MaxHealth = x;
}

void character::StaminaBarSet(int x)
{
    StaminaFont.loadFromFile("./res/Fonts/score.otf");
    StaminaText.setFont(StaminaFont);
    StaminaText.setOutlineThickness(5);
    StaminaText.setPosition(window.getSize().x * 3 / 4 - 16, WindowSize.y - 12.7 * 4);
    StaminaText.setFillColor(Color::White);
    StaminaBarFrame.setSize({ (float)x, 32.f });
    StaminaBarFrame.setOrigin(x / 2, 16);
    StaminaBarFrame.setPosition(window.getSize().x * 3 / 4, WindowSize.y - 32);
    StaminaBarFrame.setOutlineColor(Color::Blue);
    StaminaBarFrame.setOutlineThickness(5);
    StaminaBarFrame.setFillColor(Color::Transparent);
    StaminaBar.setOrigin(x / 2, 16);
    StaminaBar.setPosition(window.getSize().x * 3 / 4, WindowSize.y - 32);
    StaminaBar.setFillColor(Color::Green);
    MaxStamina = x;
}

void character::ShowHealthBar()
{
    HealthBar.setSize({ (float)health, 32.f });
    HealthText.setString(to_string(health));
    window.draw(HealthBar);
    window.draw(HealthBarFrame);
    window.draw(HealthText);
}

void character::ShowStaminaBar()
{
    StaminaBar.setSize({ (float)stamina, 32.f });
    StaminaText.setString(to_string(stamina));
    window.draw(StaminaBar);
    window.draw(StaminaBarFrame);
    window.draw(StaminaText);
}

void character::walkRight(bool x)
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
    if (x) sprite.move(speed * DeltaTime, 0);
    lastKey = "Right";
}

void character::walkLeft(bool x)
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
    if (x) sprite.move(-speed * DeltaTime, 0);
    lastKey = "Left";
}

void character::walkUp(bool x)
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
    if (x) sprite.move(0, -speed * DeltaTime);
    lastKey = "Up";
}

void character::walkDown(bool x)
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
    if (x) sprite.move(0, speed * DeltaTime);
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
    AnemationDelay = 10 / speed;
    if (IsWalking && mu == 0)
    {
        walking.play();
        walking.setLoop(1);
        mu = 1;
    }
    else if (!IsWalking && mu == 1)
    {
        walking.pause();
        mu = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        if (Keyboard::isKeyPressed(Keyboard::LShift) && stamina > 0)
        {
            speed = run;
            if (StaminaConsumtionTime < 0)
            {
                stamina--;
                StaminaConsumtionTime = StaminaConsumtionDelay;
            }
            else
                StaminaConsumtionTime -= DeltaTime;
        }
        else
            speed = walk;
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkRight(1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::A))
    {
        if (Keyboard::isKeyPressed(Keyboard::LShift) && stamina > 0)
        {
            speed = run;
            if (StaminaConsumtionTime < 0)
            {
                stamina--;
                StaminaConsumtionTime = StaminaConsumtionDelay;
            }
            else
                StaminaConsumtionTime -= DeltaTime;
        }
        else
            speed = walk;
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkLeft(1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::W))
    {
        if (Keyboard::isKeyPressed(Keyboard::LShift) && stamina > 0)
        {
            speed = run;
            if (StaminaConsumtionTime < 0)
            {
                stamina--;
                StaminaConsumtionTime = StaminaConsumtionDelay;
            }
            else
                StaminaConsumtionTime -= DeltaTime;
        }
        else
            speed = walk;
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkUp(1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        if (Keyboard::isKeyPressed(Keyboard::LShift) && stamina > 0)
        {
            speed = run;
            if (StaminaConsumtionTime < 0)
            {
                stamina--;
                StaminaConsumtionTime = StaminaConsumtionDelay;
            }
            else
                StaminaConsumtionTime -= DeltaTime;
        }
        else
            speed = walk;
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkDown(1);
    }
    else
        IsWalking = 0;

    //Stamina Restore
    if (!Keyboard::isKeyPressed(Keyboard::LShift) && stamina < MaxStamina)
    {
        if (StaminaRestoreTime < 0)
        {
            stamina++;
            StaminaRestoreTime = StaminaRestoreDelay;
        }
        else
            StaminaRestoreTime -= DeltaTime;
    }
    ShowHealthBar();
    ShowStaminaBar();
}

void character::die(string x)
{
    walking.pause();
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

void character::ChangeWeapon(string x)
{
    weapon = x;
    if (x == "NoWeapon")
        IsWeapon = 0;
    else
        IsWeapon = 1;
    tHero.loadFromFile("./res/Heros/" + who + "/" + shadow + "/" + weapon + "/" + who + ".png");
    sprite.setTexture(tHero);
    sprite.setScale(scale);
}

void character::ChangeShadow(string s)
{
    shadow = s;
    tHero.loadFromFile("./res/Heros/" + who + "/" + shadow + "/" + weapon + "/" + who + ".png");
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
            HeroSize = { 192, 192 };
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
            HeroSize = { 192, 192 };
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
void character::GoTo(Vector2f x, int y, int s)
{
    Vector2f ChaseDestance = (x - (sprite.getPosition()));
    if (sqrt(ChaseDestance.x * ChaseDestance.x + ChaseDestance.y * ChaseDestance.y) > y)
    {
        arrive = 0;
        if (!mu2)
        {
            walking.play();
            walking.setLoop(1);
            mu2 = 1;
        }
        if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
            walkRight(0);
        if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
            walkDown(0);
        if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
            walkLeft(0);
        if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
            walkUp(0);
        sprite.move(normalize(ChaseDestance) * (float)s * DeltaTime);
    }
    else
        arrive = 1, walking.pause(), mu2 = 0;
}