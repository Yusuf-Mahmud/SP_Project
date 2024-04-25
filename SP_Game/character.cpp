#include "character.h"

void character::chooseHero()
{
    Sprite zanaty, Mogiwara, Lapip;
    Texture tZanaty, tMogiwara, tLapip;
    tMogiwara.loadFromFile("./res/Heros/Mogiwara/Shadow/NoWeapon/Mogiwara.png");
    Mogiwara.setTexture(tMogiwara);
    Mogiwara.setTextureRect(IntRect(0, WalkDownIndex, HeroSize.x, HeroSize.y));
    Mogiwara.setScale(WindowSize.x / 426.7, WindowSize.y / 240);
    Mogiwara.setOrigin(HeroSize.x / 2, HeroSize.y *2 / 3);
    Mogiwara.setPosition(WindowSize.x / 4, WindowSize.y / 4);
    tZanaty.loadFromFile("./res/Heros/zanaty/Shadow/NoWeapon/zanaty.png");
    zanaty.setTexture(tZanaty);
    zanaty.setTextureRect(IntRect(0, WalkDownIndex, HeroSize.x, HeroSize.y));
    zanaty.setScale(WindowSize.x / 426.6, WindowSize.y / 240);
    zanaty.setOrigin(HeroSize.x / 2, HeroSize.y * 2 / 3);
    zanaty.setPosition(WindowSize.x * 3 / 4, WindowSize.y / 4);
    tLapip.loadFromFile("./res/Heros/Lapip/Shadow/NoWeapon/Lapip.png");
    Lapip.setTexture(tLapip);
    Lapip.setTextureRect(IntRect(0, WalkDownIndex, HeroSize.x, HeroSize.y));
    Lapip.setScale(WindowSize.x / 426.7, WindowSize.y / 240);
    Lapip.setOrigin(HeroSize.x / 2, HeroSize.y * 2 / 3);
    Lapip.setPosition(WindowSize.x * 3 / 4, WindowSize.y * 3 / 4);
    Font f;
    f.loadFromFile("./res/Fonts/minecraft_font.ttf");
    Text Mte, Zte, Lte;
    Mte.setFont(f);
    Mte.setString("Mogiwara");
    Vector2f MteSize = Mte.getLocalBounds().getSize();
    Mte.setScale(WindowSize.x / 1280, WindowSize.y / 720);
    Mte.setOrigin(MteSize.x / 2, MteSize.y / 2);
    Mte.setPosition(Mogiwara.getPosition().x, WindowSize.y / 4 + Mogiwara.getGlobalBounds().height / 3 + Mte.getGlobalBounds().height);
    Mte.setFillColor(Color::White);
    Zte.setFont(f);
    Zte.setString("Zanaty");
    Vector2f ZteSize = Zte.getGlobalBounds().getSize();
    Zte.setScale(WindowSize.x / 1280, WindowSize.y / 720);
    Zte.setOrigin(ZteSize.x / 2, ZteSize.y / 2);
    Zte.setPosition(zanaty.getPosition().x, WindowSize.y / 4 + zanaty.getGlobalBounds().height / 3 + Zte.getGlobalBounds().height);
    Zte.setFillColor(Color::White);
    Lte.setFont(f);
    Lte.setString("Lapip");
    Vector2f LteSize = Lte.getLocalBounds().getSize();
    Lte.setScale(WindowSize.x / 1280, WindowSize.y / 720);
    Lte.setOrigin(LteSize.x / 2, LteSize.y / 2);
    Lte.setPosition(Lapip.getPosition().x, WindowSize.y * 3 / 4 + Lapip.getGlobalBounds().height / 3 + Lte.getGlobalBounds().height);
    Lte.setFillColor(Color::White);

    Event ev;
    while (window.isOpen())
    {
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

        }
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f WmousePos = window.mapPixelToCoords(mousePos);
        if (Mogiwara.getGlobalBounds().contains(WmousePos) || Mte.getGlobalBounds().contains(WmousePos))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                who = "Mogiwara";
                break;
            }
        }
        if (zanaty.getGlobalBounds().contains(WmousePos) || Zte.getGlobalBounds().contains(WmousePos))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                who = "zanaty";
                break;
            }
        }
        if (Lapip.getGlobalBounds().contains(WmousePos) || Lte.getGlobalBounds().contains(WmousePos))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                who = "Lapip";
                break;
            }
        }

        window.clear();
        window.draw(zanaty);    
        window.draw(Mogiwara);  
        window.draw(Lapip);
        window.draw(Mte);
        window.draw(Zte);
        window.draw(Lte);
        window.display();
    }
}

void character::set(int posx, int posy, bool x)
{
    tHero.loadFromFile("./res/Heros/" + who + "/NoShadow/NoWeapon/" + who + ".png");
    sprite.setTexture(tHero);
    sprite.setScale(scale);
    sprite.setTextureRect(IntRect(0, 64 * 6, 64, 64));
    if (x) sprite.setOrigin(HeroSize / 2.f);
    else sprite.setOrigin(WalkSize.x / 6, 0);
    sprite.setPosition(posx, posy);
    lastKey = "Right";
    IsAlive = 1;
    Bwalking.loadFromFile("./res/Sounds/OnStoneRun3.mp3");
    walking.setBuffer(Bwalking);
    walking.setPitch(1.2);
    walking.setVolume(10);
    HealthFont.loadFromFile("./res/Fonts/score.otf");
    HealthBar.setSize({ (float)health, 32.f });
    HealthBar.setOrigin(HealthBar.getLocalBounds().getSize() / 2.f);
    HealthBar.setPosition(WindowSize.x / 2,WindowSize.y - HealthBar.getSize().y * 3);
    HealthBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
    HealthBar.setFillColor(Color::Red);
    HealthBarFrame.setSize(HealthBar.getSize());
    HealthBarFrame.setScale(HealthBar.getScale());
    HealthBarFrame.setOutlineThickness(5);
    HealthBarFrame.setOrigin(HealthBar.getOrigin());
    HealthBarFrame.setPosition(HealthBar.getPosition());
    HealthBarFrame.setOutlineColor(Color::Blue);
    HealthBarFrame.setFillColor(Color::Transparent);
    HealthText.setFont(HealthFont);
    HealthText.setOutlineThickness(5);
    HealthText.setFillColor(Color::White);
    MaxHealth = health;
    StaminaFont.loadFromFile("./res/Fonts/score.otf");
    StaminaBar.setSize({ (float)stamina, 32.f });
    StaminaBar.setOrigin(StaminaBar.getLocalBounds().getSize() / 2.f);
    StaminaBar.setPosition(window.getSize().x * 3 / 4, WindowSize.y - StaminaBar.getSize().y);
    StaminaBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
    StaminaBar.setFillColor(Color::Green);
    StaminaBarFrame.setSize(StaminaBar.getSize());
    StaminaBarFrame.setScale(StaminaBar.getScale());
    StaminaBarFrame.setOutlineThickness(5);
    StaminaBarFrame.setOrigin(StaminaBar.getOrigin());
    StaminaBarFrame.setPosition(StaminaBar.getPosition());
    StaminaBarFrame.setOutlineColor(Color::Blue);
    StaminaBarFrame.setFillColor(Color::Transparent);
    StaminaText.setFont(StaminaFont);
    StaminaText.setOutlineThickness(5);
    StaminaText.setFillColor(Color::White);
    MaxStamina = stamina;
    HungerFont.loadFromFile("./res/Fonts/score.otf");
    HungerBar.setSize({ (float)hunger, 32.f });
    HungerBar.setOrigin(HungerBar.getLocalBounds().getSize() / 2.f);
    HungerBar.setPosition(window.getSize().x / 4, WindowSize.y - HungerBar.getSize().y);
    HungerBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
    HungerBar.setFillColor(Color(150, 75, 0, 255));//Brown
    HungerBarFrame.setSize(HungerBar.getSize());
    HungerBarFrame.setScale(HungerBar.getScale());
    HungerBarFrame.setOutlineThickness(5);
    HungerBarFrame.setOrigin(HungerBar.getOrigin());
    HungerBarFrame.setPosition(HungerBar.getPosition());
    HungerBarFrame.setOutlineColor(Color::Blue);
    HungerBarFrame.setFillColor(Color::Transparent);
    HungerText.setFont(HungerFont);
    HungerText.setOutlineThickness(5);
    HungerText.setFillColor(Color::White);
    MaxHunger = hunger;
}

void character::reset()
{
    health = MaxHealth;
    stamina = MaxStamina;
    hunger = MaxHunger;
}

void character::HealthBarSet(int x)
{
    HealthBar.setSize({ (float)x, 32.f });
    HealthBar.setOrigin(HealthBar.getLocalBounds().getSize() / 2.f);
    HealthBar.setPosition(WindowSize.x / 2, WindowSize.y - HealthBar.getSize().y * 3);
    HealthBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
    HealthBar.setFillColor(Color::Red);
    HealthBarFrame.setSize(HealthBar.getSize());
    HealthBarFrame.setScale(HealthBar.getScale());
    HealthBarFrame.setOutlineThickness(5);
    HealthBarFrame.setOrigin(HealthBar.getOrigin());
    HealthBarFrame.setPosition(HealthBar.getPosition());
    HealthBarFrame.setOutlineColor(Color::Blue);
    HealthBarFrame.setFillColor(Color::Transparent);
    HealthText.setFont(HealthFont);
    HealthText.setOutlineThickness(5);
    HealthText.setFillColor(Color::White);
    MaxHealth = x;
}

void character::StaminaBarSet(int x)
{
    StaminaFont.loadFromFile("./res/Fonts/score.otf");
    StaminaBar.setSize({ (float)x, 32.f });
    StaminaBar.setOrigin(StaminaBar.getLocalBounds().getSize() / 2.f);
    StaminaBar.setPosition(window.getSize().x * 3 / 4, WindowSize.y - StaminaBar.getSize().y);
    StaminaBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
    StaminaBar.setFillColor(Color::Green);
    StaminaBarFrame.setSize(StaminaBar.getSize());
    StaminaBarFrame.setScale(StaminaBar.getScale());
    StaminaBarFrame.setOutlineThickness(5);
    StaminaBarFrame.setOrigin(StaminaBar.getOrigin());
    StaminaBarFrame.setPosition(StaminaBar.getPosition());
    StaminaBarFrame.setOutlineColor(Color::Blue);
    StaminaBarFrame.setFillColor(Color::Transparent);
    StaminaText.setFont(StaminaFont);
    StaminaText.setOutlineThickness(5);
    StaminaText.setFillColor(Color::White);
    MaxStamina = x;
}

void character::SpeedIncreaseBy(int x)
{
    walk += x;
}

void character::ShowHealthBar()
{
    HealthBar.setSize({ (float)health, HealthBar.getSize().y });
    HealthBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
    HealthText.setString(to_string(health));
    HealthText.setScale(HealthBar.getScale());
    HealthText.setOrigin((HealthText.getLocalBounds().width) / 2.f, (HealthText.getLocalBounds().height) / 2.f);
    HealthText.setPosition(HealthBar.getPosition().x + (HealthText.getOutlineThickness() - 3.8),
                           HealthBar.getPosition().y - HealthText.getOutlineThickness() +
                           (HealthText.getOutlineThickness() - (2.2 + HealthBar.getScale().x * 2)) * 2);
    window.draw(HealthBarFrame);
    window.draw(HealthBar);
    window.draw(HealthText);
}

void character::ShowStaminaBar()
{
    StaminaBar.setSize({ (float)stamina, StaminaBar.getSize().y });
    StaminaBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
    StaminaText.setString(to_string(stamina));
    StaminaText.setScale(StaminaBar.getScale());
    StaminaText.setOrigin((StaminaText.getLocalBounds().width) / 2.f, (StaminaText.getLocalBounds().height) / 2.f);
    StaminaText.setPosition(StaminaBar.getPosition().x + (StaminaText.getOutlineThickness() - 3.8),
                           StaminaBar.getPosition().y - StaminaText.getOutlineThickness() +
                           (StaminaText.getOutlineThickness() - (2.2 + StaminaBar.getScale().x * 2)) * 2);
    window.draw(StaminaBar);
    window.draw(StaminaBarFrame);
    window.draw(StaminaText);
}

void character::ShowHungerBar()
{
    HungerBar.setSize({ (float)hunger, HungerBar.getSize().y });
    HungerBar.setScale(WindowSize.x / 1280.f, WindowSize.y / 720.f);
    HungerText.setString(to_string(hunger));
    HungerText.setScale(HungerBar.getScale());
    HungerText.setOrigin((HungerText.getLocalBounds().width) / 2.f, (HungerText.getLocalBounds().height) / 2.f);
    HungerText.setPosition(HungerBar.getPosition().x + (HungerText.getOutlineThickness() - 3.8),
        HungerBar.getPosition().y - HungerText.getOutlineThickness() +
        (HungerText.getOutlineThickness() - (2.2 + HungerBar.getScale().x * 2)) * 2);
    window.draw(HungerBar);
    window.draw(HungerBarFrame);
    window.draw(HungerText);
}

void character::walkRight(bool x)
{
    HeroSize = WalkSize;
    if (AnemationTimer < 0)
    {
        AnimationI++;
        AnimationI %= NumOfWalkFrames;
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkRightIndex, HeroSize.x, HeroSize.y));
    sprite.setOrigin(HeroSize / 2.f);
    if (x) sprite.move(speed * DeltaTime, 0);
    lastKey = "Right";
}

void character::walkLeft(bool x)
{
    HeroSize = WalkSize;
    if (AnemationTimer < 0)
    {
        AnimationI++;
        AnimationI %= NumOfWalkFrames;
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkLeftIndex, HeroSize.x, HeroSize.y));
    sprite.setOrigin(HeroSize / 2.f);
    if (x) sprite.move(-speed * DeltaTime, 0);
    lastKey = "Left";
}

void character::walkUp(bool x)
{
    HeroSize = WalkSize;
    if (AnemationTimer < 0)
    {
        AnimationI++;
        AnimationI %= NumOfWalkFrames;
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkUpIndex, HeroSize.x, HeroSize.y));
    sprite.setOrigin(HeroSize / 2.f);
    if (x) sprite.move(0, -speed * DeltaTime);
    lastKey = "Up";
}

void character::walkDown(bool x)
{
    HeroSize = WalkSize;
    if (AnemationTimer < 0)
    {
        AnimationI++;
        AnimationI %= NumOfWalkFrames;
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= DeltaTime;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroSize.x, WalkDownIndex, HeroSize.x, HeroSize.y));
    sprite.setOrigin(HeroSize / 2.f);
    if (x) sprite.move(0, speed * DeltaTime);
    lastKey = "Down";
}

bool mu = 0;
void character::move()
{
    if (!IsAttacking && !IsWalking)
    {
        HeroSize = WalkSize;
        sprite.setOrigin(HeroSize / 2.f);
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
    if (Keyboard::isKeyPressed(Keyboard::Right))
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
            HungerConsumeTime -= 5 * DeltaTime;
        }
        else
            speed = walk;
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkRight(1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left))
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
            HungerConsumeTime -= 5 * DeltaTime;
        }
        else
            speed = walk;
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkLeft(1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Up))
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
            HungerConsumeTime -= 5 * DeltaTime;
        }
        else
            speed = walk;
        HitI = 0;
        IsAttacking = 0;
        IsWalking = 1;
        walkUp(1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down))
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
            HungerConsumeTime -= 5 * DeltaTime;
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
    if (hunger > 0)
    {
        if (HungerConsumeTime < 0)
        {
            hunger--;
            HungerConsumeTime = HungerConsumeDelay;
        }
        else
            HungerConsumeTime -= DeltaTime;
    }
    else
    {
        if (HealthConsumtionTime < 0)
        {
            health -= 10;
            HealthConsumtionTime = HealthConsumtionDelay;
        }
        else
            HealthConsumtionTime -= DeltaTime;
    }
}

void character::die(string x)
{
    walking.pause();
    HeroSize = DieSize;
    if (x == "defeated")
    {
        if (IsStanding)
        {
            if (DeathTimer < 0)
            {
                DeathI++;
                DeathI %= 4;
                sprite.setTextureRect(IntRect(HeroSize.x * DeathI, DieIndex, HeroSize.x, HeroSize.y));
                sprite.setOrigin(HeroSize / 2.f);
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
                sprite.setTextureRect(IntRect(HeroSize.x * DeathI, DieIndex, HeroSize.x, HeroSize.y));
                sprite.setOrigin(HeroSize / 2.f);
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
            sprite.setTextureRect(IntRect(HeroSize.x * DeathI, DieIndex, HeroSize.x, HeroSize.y));
            sprite.setOrigin(HeroSize / 2.f);
            DeathTimer = DeathDelay;
            if (DeathI == 5)
                IsAlive = false, IsStanding = 0;
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
    if (Keyboard::isKeyPressed(Keyboard::X))
        IsAttacking = 1;
    if (IsWeapon && IsAttacking && !IsWalking)
    {
        AnimationI = 0;
        if (weapon == "Axe" || weapon == "Pickaxe")
        {
            if (HitI == 0)
                HitI = 6;
            HeroSize = { 128, 128 };
            //Hiting Right Start Frame
            int HitRightIndex = 21 * WalkSize.y + 3 * HeroSize.y;
            //Hiting Left Start Frame
            int HitLeftIndex = 21 * WalkSize.y + 1 * HeroSize.y;
            //Hiting Up Start Frame
            int HitUpIndex = 21 * WalkSize.y + 0 * HeroSize.y;
            //Hiting Down Start Frame
            int HitDownIndex = 21 * WalkSize.y + 2 * HeroSize.y;
            if (lastKey == "Right")
            {
                if (HitTimer < 0)
                {
                    HitI--;
                    var = HitI;
                    sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitRightIndex, HeroSize.x, HeroSize.y));
                    sprite.setOrigin(HeroSize.x / 2, HeroSize.y / 2);
                    HitTimer = HitSpeed;
                }
                else {
                    HitTimer -= DeltaTime;
                }
                lastKey = "Right";
            }
            if (lastKey == "Left")
            {
                if (HitTimer < 0)
                {
                    HitI--;
                    var = HitI;
                    sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitLeftIndex, HeroSize.x, HeroSize.y));
                    sprite.setOrigin(HeroSize.x / 2, HeroSize.y / 2);
                    HitTimer = HitSpeed;
                }
                else {
                    HitTimer -= DeltaTime;
                }
                lastKey = "Left";
            }
            if (lastKey == "Up")
            {
                if (HitTimer < 0)
                {
                    HitI--;
                    var = HitI;
                    sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitUpIndex, HeroSize.x, HeroSize.y));
                    sprite.setOrigin(HeroSize.x / 2, HeroSize.y / 2);
                    HitTimer = HitSpeed;
                }
                else {
                    HitTimer -= DeltaTime;
                }
                lastKey = "Up";
            }
            if (lastKey == "Down")
            {
                if (HitTimer < 0)
                {
                    HitI--;
                    var = HitI;
                    sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitDownIndex, HeroSize.x, HeroSize.y));
                    sprite.setOrigin(HeroSize.x / 2, HeroSize.y / 2);
                    HitTimer = HitSpeed;
                }
                else {
                    HitTimer -= DeltaTime;
                }
                lastKey = "Down";
            }

        }
        else
        {
            if (HitI == 6)
                HitI = 0;
            HeroSize = HitSize;
            //Hiting Right Start Frame
            int HitRightIndex = 21 * WalkSize.y + 3 * HeroSize.y;
            //Hiting Left Start Frame
            int HitLeftIndex = 21 * WalkSize.y + 1 * HeroSize.y;
            //Hiting Up Start Frame
            int HitUpIndex = 21 * WalkSize.y + 0 * HeroSize.y;
            //Hiting Down Start Frame
            int HitDownIndex = 21 * WalkSize.y + 2 * HeroSize.y;
            if (lastKey == "Right")
            {
                if (HitTimer < 0)
                {
                    HitI++;
                    var = HitI;
                    HitI %= NumOfHitFrames;
                    sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitRightIndex, HeroSize.x, HeroSize.y));
                    sprite.setOrigin(HeroSize.x / 2, HeroSize.y / 2);
                    HitTimer = HitSpeed;
                }
                else {
                    HitTimer -= DeltaTime;
                }
                lastKey = "Right";
            }
            if (lastKey == "Left")
            {
                if (HitTimer < 0)
                {
                    HitI++;
                    var = HitI;
                    HitI %= NumOfHitFrames;
                    sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitLeftIndex, HeroSize.x, HeroSize.y));
                    sprite.setOrigin(HeroSize.x / 2, HeroSize.y / 2);
                    HitTimer = HitSpeed;
                }
                else {
                    HitTimer -= DeltaTime;
                }
                lastKey = "Left";
            }
            if (lastKey == "Up")
            {
                if (HitTimer < 0)
                {
                    HitI++;
                    var = HitI;
                    HitI %= NumOfHitFrames;
                    sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitUpIndex, HeroSize.x, HeroSize.y));
                    sprite.setOrigin(HeroSize.x / 2, HeroSize.y / 2);
                    HitTimer = HitSpeed;
                }
                else {
                    HitTimer -= DeltaTime;
                }
                lastKey = "Up";
            }
            if (lastKey == "Down")
            {
                if (HitTimer < 0)
                {
                    HitI++;
                    var = HitI;
                    HitI %= NumOfHitFrames;
                    sprite.setTextureRect(IntRect(HitI * HeroSize.x, HitDownIndex, HeroSize.x, HeroSize.y));
                    sprite.setOrigin(HeroSize.x / 2, HeroSize.y / 2);
                    HitTimer = HitSpeed;
                }
                else {
                    HitTimer -= DeltaTime;
                }
                lastKey = "Down";
            }
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
            if (var == 6 && (weapon == "LongSword" || weapon == "Saber"))
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x < d.y && abs(d.x) > abs(d.y))
                    h -= damage;
                var = 0, IsAttacking = 0, IsWalking = 1;
            }
            else if (var == 0 && (weapon == "Axe" || weapon == "Pickaxe"))
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x < d.y && abs(d.x) > abs(d.y))
                    h -= damage;
                var = 6, IsAttacking = 0, IsWalking = 1;
            }
        }
        if (lastKey == "Left")
        {
            
            if (var == 6 && (weapon == "LongSword" || weapon == "Saber"))
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x > d.y && abs(d.x) > abs(d.y))
                    h -= damage;
                var = 0, IsAttacking = 0, IsWalking = 1;
            }
            else if (var == 0 && (weapon == "Axe" || weapon == "Pickaxe"))
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x > d.y && abs(d.x) > abs(d.y))
                    h -= damage;
                var = 6, IsAttacking = 0, IsWalking = 1;
            }
        }
        if (lastKey == "Up")
        {
            if (var == 6 && (weapon == "LongSword" || weapon == "Saber"))
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x < d.y && abs(d.x) < abs(d.y))
                    h -= damage;
                var = 0, IsAttacking = 0, IsWalking = 1;
            }
            else if (var == 0 && (weapon == "Axe" || weapon == "Pickaxe"))
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x < d.y && abs(d.x) < abs(d.y))
                    h -= damage;
                var = 6, IsAttacking = 0, IsWalking = 1;
            }
        }
        if (lastKey == "Down")
        {
            if (var == 6 && (weapon == "LongSword" || weapon == "Saber"))
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x > d.y && abs(d.x) < abs(d.y))
                    h -= damage;
                var = 0, IsAttacking = 0, IsWalking = 1;
            }
            else if (var == 0 && (weapon == "Axe" || weapon == "Pickaxe"))
            {
                if (DistanceBetween(s, sprite) <= HitDistance && d.x > d.y && abs(d.x) < abs(d.y))
                    h -= damage;
                var = 6, IsAttacking = 0, IsWalking = 1;
                cout << var << endl;
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

void character::LookAt(Sprite x)
{
    Vector2f ChaseDestance = VectorDistanceBetween(x, sprite);
    if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.x) > abs(ChaseDestance.y))
    {
        sprite.setTextureRect(IntRect(0, 64 * 11, 64, 64));
        sprite.setOrigin(32, 32);
    }
    if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.y) > abs(ChaseDestance.x))
    {
        sprite.setTextureRect(IntRect(0, 64 * 10, 64, 64));
        sprite.setOrigin(32, 32);
    }
    if (ChaseDestance.y > ChaseDestance.x && abs(ChaseDestance.x) > abs(ChaseDestance.y))
    {
        sprite.setTextureRect(IntRect(0, 64 * 9, 64, 64));
        sprite.setOrigin(32, 32);
    }
    if (ChaseDestance.x > ChaseDestance.y && abs(ChaseDestance.y) > abs(ChaseDestance.x))
    {
        sprite.setTextureRect(IntRect(0, 64 * 8, 64, 64));
        sprite.setOrigin(32, 32);
    }
}

bool dcCh = true;
void character::dodge()
{
    if (Keyboard::isKeyPressed(Keyboard::C) && dcCh && stamina >= DodgeStminaConsumtion)
    {
        if (lastKey == "Right")
        {
            sprite.setPosition(sprite.getPosition().x + DodgeTeleportDis, sprite.getPosition().y);
            stamina -= DodgeStminaConsumtion;
        }
        else if (lastKey == "Left")
        {
            sprite.setPosition(sprite.getPosition().x - DodgeTeleportDis, sprite.getPosition().y);
            stamina -= DodgeStminaConsumtion;
        }
        else if (lastKey == "Up")
        {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - DodgeTeleportDis);
            stamina -= DodgeStminaConsumtion;
        }
        else if (lastKey == "Down")
        {
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + DodgeTeleportDis);
            stamina -= DodgeStminaConsumtion;
        }
        dcCh = 0;
    }
    else if (!Keyboard::isKeyPressed(Keyboard::C))
    {
        dcCh = 1;
    }
}

void character::play()
{
    move();
    hit();
    dodge();
    ShowHealthBar();
    ShowStaminaBar();
    ShowHungerBar();
}