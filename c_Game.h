#ifndef C_GAME.H
#define C_GAME.H

#include "c_TextureManager.h"

class c_Game
{
private:
    c_TextureManager* textureManager;
protected:
public:
    c_Game ();
    int start (unsigned inScreenWidth, unsigned inScreenHeight);
    //int exit ();
    //int returnError ();
};


int c_Game::start (unsigned inScreenWidth, unsigned inScreenHeight)
{
    textureManager -> init (inScreenWidth, inScreenHeight);

    int error = false;
    while (!error)
    {
        if (error = textureManager -> refreshScreen ())
                break;
    }

    return error;
};

c_Game::c_Game ()
{
    textureManager = new c_TextureManager ();
};

#endif
