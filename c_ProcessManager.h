#ifndef C_PROCESS_MANAGER
#define C_PROCESS_MANAGER

#include <vector>
#include <assert.h>

#include "cl_Object.h"
#include "c_EventManager.h"


class c_ProcessManager
{
private:
    std::vector <c_Object*>* objects;
    int handleEvents (std::vector <c_Event*>* ievents, std::vector <c_Object*>* iobjects);
    int think (std::vector <c_Object*>* iobjects);
    int onMLButtonDown (std::vector <c_Object*>* iobjects, int ix, int iy);
protected:
public:
    int process (std::vector <c_Event*>* ievents, std::vector <c_Object*>* iobjects);
};

int c_ProcessManager::process (std::vector <c_Event*>* ievents, std::vector <c_Object*>* iobjects)
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

int c_ProcessManager::handleEvents (std::vector <c_Event*>* ievents, std::vector <c_Object*>* iobjects)
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
int c_ProcessManager::onMLButtonDown (std::vector <c_Object*>* iobjects, int ix, int iy)
{
    std::cout << "onMLButtonDown'ing...\n";
    assert (ix >= 0); assert (iy >= 0);
    assert (iobjects);

    for (int i = 0; i < iobjects -> size (); i++)
        if (((*iobjects)[i]) -> getKind () == OBJECT_SHIP)
        {
            c_Ship* ship = (c_Ship*)((*iobjects)[i]);
            ship -> setXDest (ix);
            ship -> setYDest (iy);
            ship -> setDestChanged (true);
            return 0;
        }

    assert (0);
    return SHIP_DOESNT_FOUND;
};

int c_ProcessManager::think (std::vector <c_Object*>* iobjects)
{
    std::cout << "Thinking\n";
    assert (iobjects);

    int error = false;
    for (int i = 0; i < iobjects -> size (); i++)
    {
        switch (((*iobjects)[i]) -> getKind ())
        {
            case OBJECT_SHIP:
                error = ((c_Ship*)((*iobjects)[i])) -> think ();
                if (error)
                    return error;
                break;
        }
    }

    return 0;
};

#endif
