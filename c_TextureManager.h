#ifndef C_TEXTUREMANAGER.H
#define C_TEXTUREMANAGER.H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "myGraphicsFuncs.h"
#include <assert.h>

struct s_Texture
{
    SDL_Surface* surface;
    unsigned priority;
    unsigned xpos;
    unsigned ypos;
};

class c_TextureManager
{
private:
    unsigned screenWidth;
    unsigned screenHeight;
    SDL_Surface* screen;
    s_Texture background;
    s_Texture ship;

    int loadTextures ();
    int clear ();
    int render ();
protected:
public:
    c_TextureManager ();
    int init (unsigned inScreenWidth, unsigned inScreenHeight);
    int refreshScreen ();
};

c_TextureManager::c_TextureManager ()
{
    screenWidth = 800; //DEFAULT
    screenHeight = 600; //DEFAULT
    screen = NULL;
    background.surface = NULL;
    background.priority = 0;
    background.xpos = 0; background.ypos = 0;
    ship.surface = NULL;
    ship.priority = 1;
    ship.xpos = 300; ship.ypos = 250;
};

int c_TextureManager::loadTextures ()
{
    background.surface = loadImage ("background.jpeg");
    assert (background.surface);
    ship.surface = loadImage ("ship.png");
    assert (ship.surface);

    if (background.surface && ship.surface)
        return 0; //OK
    else
        return 1; //not loaded

    return 2;    //smth is wrong
};

int c_TextureManager::init (unsigned inScreenWidth, unsigned inScreenHeight)
{
    assert (!screen);
    if (!screen)
    {
        screen = NULL;
        if (SDL_Init( SDL_INIT_EVERYTHING ) != -1)
            screen = SDL_SetVideoMode (inScreenWidth, inScreenHeight, 32, SDL_SWSURFACE);
        assert (screen);

        int error = 0;
        if (error = loadTextures ())
        {
            assert (!error);
            return error;
        }
        return 0; //OK
    }
    else
        return 1; //texture manager has been initialized

    return 2;     //smth's wrong
};

int c_TextureManager::render()
{
    applySurface (0, 0, background.surface, screen);
    applySurface (ship.xpos, ship.ypos, ship.surface, screen);

    return 0;
};

int c_TextureManager::refreshScreen ()
{
    this -> render ();
     if (SDL_Flip (screen) == -1)
        {
            assert (0);
            return 1;
        }
    //SDL_Delay (1000);
    return 0;
};

#endif
