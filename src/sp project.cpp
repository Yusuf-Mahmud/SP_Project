#include "var.h";

struct hero
{

    int score = 0;
    int lifePoints = 8;
    Sprite sprite;

    int hight = 64;
    int width = 64;
    const float scale = 1.5;
    Vector2f initPosition = Vector2f(50, 50);
    string lastKey;
    float move = 200;
    
    Texture tHeroSord;
    

    // hero initialization
    const int initIndex = 6 * 64;
    void setHero(Texture& player)
    {
        sprite.setTexture(player);
        sprite.setPosition(initPosition);
        sprite.setScale(scale, scale);
        sprite.setTextureRect(IntRect(0, initIndex, width, hight));
        lastKey = "Right";
        move = 200;

    }
    // set a clock for animation speed
    Clock cl;
    const float clockLimit = 0.05;

    // walking to right
    int indexWalkToRight = 64 * 11;
    int walkToRightCount = 0;

    void walkRight(float dt)
    {
        width = 64;
        hight = 64;
        const int walkToRightIndexesNumber = 9;

        if (cl.getElapsedTime().asSeconds() >= clockLimit)
        {
            walkToRightCount++;
            walkToRightCount %= walkToRightIndexesNumber;
            cl.restart();
        }

        sprite.setTextureRect(IntRect(walkToRightCount * width, indexWalkToRight, width, hight));
        sprite.move(move * dt, 0);
        lastKey = "Right";
    }

    // walking to left
    const int indexWalkToLeft = 9 * 64;
    int walkToLeftCount = 8;

    void walkLeft(float dt)
    {
        width = 64;
        hight = 64;
        if (cl.getElapsedTime().asSeconds() >= clockLimit)
        {
            walkToLeftCount--;
            if (walkToLeftCount < 0) walkToLeftCount = 8;
            cl.restart();
        }
        sprite.setTextureRect(IntRect(walkToLeftCount * width, indexWalkToLeft, width, hight));

        sprite.move(-move * dt, 0);
        lastKey = "Left";
    }

    // walking up
    const int walkUpIndex = 8 * 64;
    int walkUpCount = 0;
    void walkUp(float dt)
    {
        width = 64;
        hight = 64;

        if (cl.getElapsedTime().asSeconds() >= clockLimit)
        {
            walkUpCount++;
            walkUpCount %= 9;
            cl.restart();
        }
        sprite.setTextureRect(IntRect(walkUpCount * width, walkUpIndex, width, hight));
        sprite.move(0, -move * dt);
        lastKey = "Up";
    }

    // walking down
    const int walkDownIndex = 10 * 64;
    int walkDownCount = 0;
    void walkDown(float dt)
    {
        width = 64;
        hight = 64;
        if (cl.getElapsedTime().asSeconds() >= clockLimit)
        {
            walkDownCount++;
            walkDownCount %= 9;
            cl.restart();
        }
        sprite.setTextureRect(IntRect(walkDownCount * width, walkDownIndex, width, hight));
        sprite.move(0, move * dt);
        lastKey = "Down";
    }

    int hitIndex;
    int hitCount = 0;
    void hitToRight() {
        width = 64;
        hight = 64;
        hitIndex = 20 * 64 + (3 * 192);
        if (cl.getElapsedTime().asSeconds() >= clockLimit)
        {
            hitCount++;
            hitCount %= 6;
            cl.restart();
        }
        sprite.setTextureRect(IntRect(hitCount * 192, hitIndex, width, hight));
        lastKey = "Right";

    }

};

int main()
{
    gamePlay();

}

void chooseHero()
{
    Texture tRamadan, tZanaty;
    tRamadan.loadFromFile("photos/hero/ramadan.jpeg");
    tZanaty.loadFromFile("photos/hero/zanaty.jpeg");

    Sprite ramadan, zanaty;
    ramadan.setTexture(tRamadan);
    zanaty.setTexture(tZanaty);

    ramadan.setScale(2, 4.8);
    zanaty.setScale(3.5, 4.8);

    zanaty.setPosition(windowWidth / 2 - 100, 0);
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
                mainHero = "Ramadan";
                break;

            }
        }
        if (zanaty.getGlobalBounds().contains(WmousePos))
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                mainHero = "Zanaty";
                break;
            }
        }
        window.clear(Color::Green);
        window.draw(zanaty);
        window.draw(ramadan);
        window.display();
    }

}

void gamePlay()
{
    window.setFramerateLimit(60);

    Texture texture;
    hero hero1;

    Clock clock;
    float dt;

    RectangleShape r;
    r.setSize(Vector2f(20, 20));
    r.setPosition(500, 500);

    chooseHero();
    if (mainHero == "Zanaty")
    {
        texture.loadFromFile("photos/hero/zanatyHero.png");
    }
    else if (mainHero == "Ramadan")
    {
        texture.loadFromFile("photos/hero/ramadanHero.png");
    }
    hero1.setHero(texture);

    Event event;
    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        dt = clock.restart().asSeconds();


        // return to the main frame when key released
        if (hero1.lastKey == "Right")
        {
            hero1.sprite.setTextureRect(IntRect(0, hero1.indexWalkToRight, hero1.width, hero1.hight));
        }
        else if (hero1.lastKey == "Left")
        {
            hero1.sprite.setTextureRect(IntRect(0, hero1.indexWalkToLeft, hero1.width, hero1.hight));
        }
        else if (hero1.lastKey == "Up")
        {
            hero1.sprite.setTextureRect(IntRect(0, hero1.walkUpIndex, hero1.width, hero1.hight));
        }
        else if (hero1.lastKey == "Down")
        {
            hero1.sprite.setTextureRect(IntRect(0, hero1.walkDownIndex, hero1.width, hero1.hight));
        }

        // moving hero
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            hero1.walkRight(dt);

        }
        else if (Keyboard::isKeyPressed(Keyboard::A))
        {
            hero1.walkLeft(dt);

        }
        else if (Keyboard::isKeyPressed(Keyboard::W))
        {
            hero1.walkUp(dt);
        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
            hero1.walkDown(dt);
        }

        if (hero1.sprite.getGlobalBounds().intersects(r.getGlobalBounds())) {
            weapon = "sword";
            r.setPosition(10000, 10000);
            hero1.tHeroSord.loadFromFile("photos/hero/zanatySord.png");
            hero1.initPosition = hero1.sprite.getPosition();
            hero1.setHero(hero1.tHeroSord);
        }

        // hit
        if (Mouse::isButtonPressed(Mouse::Left) and hero1.lastKey == "Right" and weapon == "sword") {
            hero1.hitToRight();
        }

        // update

        window.clear();
        window.draw(r);
        window.draw(hero1.sprite);
        window.display();
    }

}

