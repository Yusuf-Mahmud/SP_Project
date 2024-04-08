#include "mainCharactersVar.h"


Event event;
struct hero
{

    int score = 0;
    int lifePoints = 8;
    Sprite sprite;

    int HeroLength = 64;
    int HeroWidth = 64;
    const float scale = 1.5;
    Vector2f initPosition = Vector2f(50, 50);
    string lastKey;
    float move = 200;
    int AnimationI = 0;
    Texture tHeroSword;


    // hero initialization
    const int initIndex = 6 * 64;
    void setHero(Texture& player);




    // set a clock for animation speed
    Clock cl;
    const float clockLimit = 0.05;

    // walking to right
    int indexWalkToRight = 64 * 11;


    void walkRight();


    // walking to left
    const int indexWalkToLeft = 9 * 64;


    void walkLeft();


    // walking up
    const int walkUpIndex = 8 * 64;

    void walkUp();


    // walking down
    const int walkDownIndex = 10 * 64;

    const int HitRightIndex = 30 * 64;
    const int HitLeftIndex = 24 * 64;
    const int HitUpIndex = 21 * 64;
    const int HitDownIndex = 27 * 64;

    void walkDown();


    void Move();


    void takeSword();


    int hitCount = 1;
    void hit(Clock clock);


};

//hero setMainChar();

int main()
{
    heroAnimations();

}

void chooseHero()
{


    RectangleShape zanaty, ramadan;
    zanaty.setSize(Vector2f(100, 100));
    ramadan.setSize(Vector2f(100, 100));
    zanaty.setPosition(Vector2f(windowSize.x / 2 - 100, windowSize.y / 2));
    ramadan.setPosition(Vector2f(windowSize.x / 2 + 100, windowSize.y / 2));
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

        window.clear(Color::White);
        window.draw(zanaty);
        window.draw(ramadan);
        window.display();

    }


}
//hero setMainChar() {

//}

void heroAnimations()
{
    window.setFramerateLimit(60);


    hero hero1;

    Clock clock;

    RectangleShape r;
    r.setSize(Vector2f(20, 20));
    r.setPosition(500, 500);
    r.setFillColor(Color::Black);

    hero h;
    Texture texture;
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


    while (window.isOpen())
    {
        clock.restart();
        //dt = clock.getElapsedTime().asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::KeyPressed and event.key.code == Mouse::Left) {
                isAttacking = true;
                HitI = 0;
            }
        }

        hero1.Move();


        if (hero1.sprite.getGlobalBounds().intersects(r.getGlobalBounds())) {
            weapon = "sword";
            isWeapon = true;
            r.setPosition(10000, 10000);
            hero1.takeSword();
        }

        // hit
        if (isAttacking) {
            hero1.hit(clock);
        }
        // update

        window.clear(Color::White);
        window.draw(r);
        window.draw(hero1.sprite);
        window.display();

        dt = clock.getElapsedTime().asSeconds();
    }

}

void hero::setHero(Texture& player)
{
    sprite.setTexture(player);
    sprite.setPosition(initPosition);
    sprite.setScale(scale, scale);
    sprite.setTextureRect(IntRect(0, initIndex, HeroWidth, HeroLength));
    //sprite.setOrigin(HeroWidth / 2.f, HeroLength / 2.f);
    lastKey = "Right";
    move = 200;
}

void hero::walkRight()
{

    HeroWidth = 64;
    HeroLength = 64;
    const int walkToRightIndexesNumber = 9;

    if (AnemationTimer < 0)
    {

        AnimationI++;
        AnimationI %= 9;
        sprite.setOrigin(HeroWidth / 2.f, HeroLength / 2.f);
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= dt;
    }

    sprite.setTextureRect(IntRect(AnimationI * HeroWidth, indexWalkToRight, HeroWidth, HeroLength));
    sprite.move(move * dt, 0);
    lastKey = "Right";
}

void hero::walkLeft()
{
    HeroWidth = 64;
    HeroLength = 64;
    if (AnemationTimer < 0)
    {

        AnimationI++;
        AnimationI %= 9;
        sprite.setOrigin(HeroWidth / 2.f, HeroLength / 2.f);
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= dt;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroWidth, indexWalkToLeft, HeroWidth, HeroLength));
    sprite.move(-move * dt, 0);
    lastKey = "Left";
}

void hero::walkUp()
{
    HeroWidth = 64;
    HeroLength = 64;


    if (AnemationTimer < 0)
    {

        AnimationI++;
        AnimationI %= 9;
        sprite.setOrigin(HeroWidth / 2.f, HeroLength / 2.f);
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= dt;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroWidth, walkUpIndex, HeroWidth, HeroLength));
    sprite.move(0, -move * dt);
    lastKey = "Up";
}

void hero::walkDown()
{
    HeroWidth = 64;
    HeroLength = 64;
    if (AnemationTimer < 0)
    {

        AnimationI++;
        AnimationI %= 9;
        sprite.setOrigin(HeroWidth / 2.f, HeroLength / 2.f);
        AnemationTimer = AnemationDelay;
    }
    else {
        AnemationTimer -= dt;
    }
    sprite.setTextureRect(IntRect(AnimationI * HeroWidth, walkDownIndex, HeroWidth, HeroLength));
    sprite.move(0, move * dt);
    lastKey = "Down";
}

void hero::Move()
{
    if (lastKey == "Right")
    {
            
            sprite.setOrigin(Vector2f(32, 32));
            sprite.setTextureRect(IntRect(0, indexWalkToRight, HeroWidth, HeroLength));
        

    }

    else if (lastKey == "Left")
    {
        sprite.setTextureRect(IntRect(0, indexWalkToLeft, HeroWidth, HeroLength));
    }
    else if (lastKey == "Up")
    {
        sprite.setTextureRect(IntRect(0, walkUpIndex, HeroWidth, HeroLength));
    }
    else if (lastKey == "Down")
    {
        sprite.setTextureRect(IntRect(0, walkDownIndex, HeroWidth, HeroLength));
    }

    // moving hero
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        Walk = true;
        walkRight();

    }
    else if (Keyboard::isKeyPressed(Keyboard::A))
    {
        Walk = true;
        walkLeft();

    }
    else if (Keyboard::isKeyPressed(Keyboard::W))
    {
        Walk = true;
        walkUp();
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        Walk = true;
        walkDown();
    }
    else Walk = false;
}

void hero::takeSword()
{
    tHeroSword.loadFromFile("photos/hero/zanatySord.png");
    initPosition = sprite.getPosition();
    setHero(tHeroSword);
}

void hero::hit(Clock clock)
{
    
    
            if (HitTimer <= HitDelay) {
                HitI++;
                if (HitI >= 6) {
                    HitI = 0;
                    isAttacking = false;
                }
                sprite.setOrigin(Vector2f(96, 96));
                sprite.setTextureRect(IntRect(HitI * 192, HitRightIndex, 192, 192));
                HitTimer -= dt;
            }
            
           
         

        }
    
 
