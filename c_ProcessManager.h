#ifndef C_PROCESS_MANAGER
#define C_PROCESS_MANAGER

#include <vector>
#include <assert.h>

#include "c_Objects.h"
#include "c_EventManager.h"


class c_ProcessManager
{
private:
    std::vector <c_Object*>* objects;
    int handleEvents (std::vector <c_Event*>* ievents, c_ObjectsTree* iobjects);
    int think (c_ObjectsTree* iobjects);
    int onMLButtonDown (c_ObjectsTree* iobjects, int ix, int iy);
protected:
public:
    int process (std::vector <c_Event*>* ievents, c_ObjectsTree* iobjects);
};

int c_ProcessManager::process (std::vector <c_Event*>* ievents, c_ObjectsTree* iobjects)
{
    assert (ievents); assert (iobjects);
    std::cout << "Processing...\n";

    //objects = iobjects;
    //assert (0);
    int error = false;
    if (error = handleEvents (ievents, iobjects))
    {
        assert (0);
        return error;
    }
    if (error = think (iobjects))
    {
        assert (0);
        return error;
    }

    std::cout << "Processed.\n";
    return 0;
};

int c_ProcessManager::handleEvents (std::vector <c_Event*>* ievents, c_ObjectsTree* iobjects)
{
    std::cout << "Handling events...\n";
    unsigned error = 0;
    while (!ievents -> empty ())
    {
        switch ((ievents -> back ()) -> getKind ())
        {
            case EVENT_MOUSEBUTTON:
                std::cout << "EVENT_MOUSEBUTTON\n";
                switch (((c_MouseButtonEvent*)(ievents -> back ())) -> getButton ())
                {
                    case SDL_BUTTON_LEFT:
                        std::cout << "SDL_BUTTON_LEFT\n";
                        switch (((c_MouseButtonEvent*)(ievents -> back ())) -> getType ())
                        {
                            case SDL_MOUSEBUTTONDOWN:
                                std::cout << "SDL_MOUSEBUTTONDOWN\n";
                                error = onMLButtonDown (iobjects, ((c_MouseButtonEvent*)(ievents -> back ())) -> getX (), ((c_MouseButtonEvent*)(ievents -> back ())) -> getY ());
                                if (error)
                                {
                                    assert (0);
                                    return error;
                                }
                                break;
                        }
                        break;
                }
                break;
        }
    ievents -> pop_back ();
    }

    std::cout << "Handled events.\n";
    return 0;
};

#define SHIP_DOESNT_FOUND 1
int c_ProcessManager::onMLButtonDown (c_ObjectsTree* iobjects, int ix, int iy)
{
    std::cout << "onMLButtonDown'ing...\n";
    assert (ix >= 0); assert (iy >= 0);
    assert (iobjects);

    c_ObjectsContainerIterator* shipsIterator = iobjects -> getObjectsIterator (OBJECT_SHIP);
    c_Object* oship = NULL;

    while (oship = shipsIterator -> getNextObject ())
    {
        assert (oship -> getKind () == OBJECT_SHIP);
        std::cout << "SHIP_DEST_CHANGED\n";
        c_Ship* ship = (c_Ship*) oship;
        std::cout << "SPIP_SPEED_" << ship -> getSpeed () << "\n";
        ship -> setXDest (ix);
        ship -> setYDest (iy);
        ship -> setDestChanged (true);
        shipsIterator -> ~c_ObjectsContainerIterator ();
        return 0;
    }

    assert (0);
    return SHIP_DOESNT_FOUND;
};

int c_ProcessManager::think (c_ObjectsTree* iobjects)
{
    std::cout << "Thinking\n";
    assert (iobjects);

    c_ObjectsTreeIterator* treeIterator = iobjects -> getIterator ();
    c_ObjectsContainer* objectsContainer = treeIterator -> getContainer (OBJECT_OBJECT);
    c_ObjectsContainerIterator* objectsIterator = objectsContainer -> getIterator (iobjects -> getIterator ());
    c_Object* object = NULL;
    int error = false;
    while (object = objectsIterator -> getNextObject ())
    {
        switch (object -> getKind ())
        {
            case OBJECT_SHIP:
                error = ((c_Ship*)(object)) -> think ();
                if (error)
                    return error;
                break;
            case OBJECT_PLANET:
                error = ((c_Planet*)(object)) -> think ();
                if (error)
                    return error;
                break;
        }
    }

    return 0;
};

#endif
