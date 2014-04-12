#ifndef C_OBJECT
#define C_OBJECT

#include "myGraphicsFuncs.h"
//#include "c_TextureManager.h"
#include <math.h>
#include <assert.h>
#include <iostream>

struct s_Texture
{
    SDL_Surface* surface;
    unsigned priority;
    unsigned xpos;
    unsigned ypos;
};

#define OBJECT_OBJECT 1
class c_Object
{
private:
protected:
    unsigned kind;
public:
    unsigned getKind ();
    int think ();
};

unsigned c_Object::getKind ()
{
    return kind;
};

int c_Object::think ()
{
    return 1;
};


#define OBJECT_GRAPHICSOBJECT 2
class c_GraphicsObject: protected c_Object
{
private:
protected:
    s_Texture texture;
    std::string* files[10];
    SDL_Surface* surfaces[10];
    int n;
public:
    int loadTextures ();
    s_Texture getTexture ();
};

int c_GraphicsObject::loadTextures ()
{
    std::cout << "loading textures to object..\n";
    for (int i = 0; i < n; i++)
    {
        surfaces[i] = loadImage (*files[i]);
        if (!surfaces[i])
        {
            assert (0);
            return 1;
        }
    }

    texture.surface = surfaces[0];

    std::cout << "loading textures to object.. done\n";//
    return 0;
};

s_Texture c_GraphicsObject::getTexture ()
{
    return texture;
};


#define OBJECT_BACKGROUND 3
class c_Background: protected c_GraphicsObject
{
public:
    c_Background ();
};

c_Background::c_Background ()
{
    kind = OBJECT_BACKGROUND;
    texture.surface = NULL;
    texture.priority = 0;
    texture.xpos = 0; texture.ypos = 0;
    n = 1;
    files[0] = new std::string("background.jpeg");
};


#define OBJECT_SHIP 4
#define LEFT 0
#define RIGHT 1
class c_Ship: protected c_GraphicsObject
{
private:
protected:
    float x, y;
    float speed;
    float xspeed, yspeed;
    float xdest, ydest;
    bool destChanged;
    SDL_Surface* leftSurface;
    SDL_Surface* rightSurface;
public:
    c_Ship ();
    int think ();
    float getXSpeed ();
    float getYSpeed ();
    float getXDest ();
    int setXDest (float ix);
    float getYDest ();
    int setYDest (float iy);
    int setDestChanged (bool i);
};

c_Ship::c_Ship ()
{
    kind = OBJECT_SHIP;
    texture.surface = NULL;
    texture.priority = 1;
    texture.xpos = 0; texture.ypos = 0;
    x = 0; y = 0;
    speed = 20;
    xspeed = 0; yspeed = 0;
    xdest = 0; ydest = 0;
    destChanged = false;

    n = 2;
    files[LEFT] = new std::string ("shipLeft.png");
    files[RIGHT] = new std::string ("shipRight.png");
};

int c_Ship::think ()
{
    std::cout << "Ship thinking...\n";
    if (destChanged)
    {
        xspeed = speed * (xdest - x) / sqrt ((xdest - x)*(xdest - x) + (ydest - y)*(ydest - y));
        yspeed = speed * (ydest - y) / sqrt ((xdest - x)*(xdest - x) + (ydest - y)*(ydest - y));

        if (xspeed > 0)
            texture.surface = surfaces[RIGHT];
        if (xspeed < 0)
            texture.surface = surfaces[LEFT];

        destChanged = false;
    }

    x += xspeed;
    y += yspeed;

    texture.xpos = floor (x);
    texture.ypos = floor (y);

    return 0;
};

float c_Ship::getXSpeed ()
{
    return xspeed;
};
float c_Ship::getYSpeed ()
{
    return yspeed;
};
float c_Ship::getXDest ()
{
    return xdest;
};
int c_Ship::setXDest (float ix)
{
    xdest = ix;

    return 0;
};
float c_Ship::getYDest ()
{
    return ydest;
};
int c_Ship::setYDest (float iy)
{
    ydest = iy;

    return 0;
};
int c_Ship::setDestChanged (bool i)
{
    destChanged = i;

    return 0;
};

#endif
