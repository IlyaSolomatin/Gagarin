#ifndef C_GAME
#define C_GAME

#include <vector>
#include <assert.h>

#include "cl_Object.h"
#include "c_TextureManager.h"
#include "c_EventManager.h"
#include "c_ProcessManager.h"

class c_Game
{
private:
    std::vector <c_Object*> objects;
    std::vector <c_Object*>::iterator objectsIterator;
    c_TextureManager* textureManager;
    c_EventManager* eventManager;
    c_ProcessManager* processManager;
    unsigned handleError (unsigned ierror);
protected:
public:
    c_Game ();
    int start (unsigned inScreenWidth, unsigned inScreenHeight);
    //int exit ();
    //int returnError ();
};


int c_Game::start (unsigned inScreenWidth, unsigned inScreenHeight)
{
    std::cout << "started\n";

    objects.push_back ((c_Object*) new c_Background ());
    objects.push_back ((c_Object*) new c_Ship ());

    textureManager -> init (inScreenWidth, inScreenHeight, &objects);

    int error = false;
    int quit = false;
    while ((!error) && (!quit))
    {
        if (error = processManager -> process (eventManager -> getEvents (), &objects))
            quit = handleError (error);
        if (error = textureManager -> refreshScreen (&objects))
            quit = handleError (error);
    }

    assert (0);
    return error;
};

c_Game::c_Game ()
{
    textureManager = new c_TextureManager ();
    eventManager = new c_EventManager ();
};

unsigned c_Game::handleError (unsigned ierror)
{
    return ierror;
};

#endif

