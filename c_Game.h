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
    //std::vector <c_Object*> objects;
    //std::vector <c_Object*>::iterator objectsIterator;
    c_ObjectsTree* objects;
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

    //c_ObjectsTreeIterator* TreeIterator = objects -> getIterator ();
    objects -> addObject (new c_Background ());
    objects -> addObject (new c_Ship ());
    c_Object* star1 = (new c_Star (1));
    objects -> addObject (star1);
    c_System* system1 = ((new c_System ((c_Star*) star1)));
    //objects -> addObject (system1);
    objects -> addObject (new c_Planet (200, 1, 1, 0.005, (c_System*)system1, 0));
    objects -> addObject (new c_Planet (100, 2, 2, 0.030, (c_System*)system1, 0));

    textureManager -> init (inScreenWidth, inScreenHeight, objects);

    int error = false;
    int quit = false;
    while ((!error) && (!quit))
    {
        if (error = processManager -> process (eventManager -> getEvents (), objects))
            quit = handleError (error);
        if (error = textureManager -> refreshScreen (objects))
            quit = handleError (error);
    }

    assert (0);
    return error;
};

c_Game::c_Game ()
{
    objects = new c_ObjectsTree ();
    textureManager = new c_TextureManager ();
    eventManager = new c_EventManager ();
};

unsigned c_Game::handleError (unsigned ierror)
{
    return ierror;
};

#endif
