#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "CollisionManager.h"

//Button Structure -> Called in below Structs
struct Buttons {
    Font* font;
    Text* text;
    RectangleShape* rect;
    Color* idle;
    Color* touch;
    Color* press;
    bool isIdle;
    bool isTouch;
    bool isPress;
    int size;

    void setButtonDetails(int x, int y, int xT, int yT, int width, int height, string text, Color idle, Color touch, Color press, RenderWindow* window);
    Buttons();
    ~Buttons();
};

//List Structure -> Called in below Structs
struct list {
    void setListDetails(float width, float height, float x, float y, float xT, float yT, int sizeChar, string str[], Color idle, Color press, RenderWindow* window);
    void whenPress(RenderWindow* window, Event& ev, Vector2f mousePos);

    void render(RenderWindow* window);

    string  getText();

    list(int size);
    ~list();

    bool isOpen;
    RectangleShape* elements;
    Text* text;
private:
    string* str;
    Font* font;
    float* width;
    float* height;
    float* x;
    float* y;
    int* size;
    Color* idle;
    Color* press;
    bool isIdle;
    bool isTouch;
    bool isPress;
};

//Resolution Structure
struct Resolution {
    list* List;
    list* List1;
    void setResolutionDetails(RenderWindow* window);
    Resolution(int);
    ~Resolution();

private:
    string* resolutionList;
    string* name;
};

//FPS Structure
struct fps {
    list* List;
    list* List1;
    void setFPSDetails(RenderWindow* window);
    fps(int);
    ~fps();

private:
    string* FPSList;
    string* name;
};

//SFX Structure
struct SFX {
    list* List;
    list* List1;
    void setSFXDetails(RenderWindow*);
    SFX();
    ~SFX();
private:
    string* name;
    string* sfxOptions;
};

//vSync Structure
struct vSync {
    list* List;
    list* List1;
    void setVSyncDetails(RenderWindow* window);

    vSync();
    ~vSync();

private:
    string* name;
    string* vSyncOptions;
};

//Save Structure
struct Save {
    Buttons* button;
    void setSaveDetails(RenderWindow*);
    void whenPress(RenderWindow* window, Vector2f& mousePos, string textRes,
        string textFps, string textSFX, string textVSync);
    void render(RenderWindow* window);
    Save();
    ~Save();
    bool apply;
private:
    string* name;
};

//Active all  above structures
struct menuSettings {
    Resolution* RESOLUTION_SETTINGS;
    fps* FPS_SETTINGS;
    SFX* SFX_SETTINGS;
    vSync* VERTICAL_SYNC_SETTINGS;
    Save* SAVE_SETTINGS;
    RectangleShape* BACK_GROUND; //Gray Rectangle

    void setResolution_Settings(RenderWindow*);
    void setFPS_Settings(RenderWindow*);
    void setSFX_Settings(RenderWindow*);
    void setVSync_Settings(RenderWindow*);
    void setSave_Settings(RenderWindow*);

    void applySettings(RenderWindow* window, Vector2f& mousePos , bool& apply);

    void renderBackGround(RenderWindow* window);
    menuSettings(RenderWindow* window);
    ~menuSettings();
};

#endif
