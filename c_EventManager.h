#ifndef C_EVENTMANAGER
#define C_EVENTMANAGER


#include <assert.h>
#include <vector>
#include "SDL/SDL.h"


#define NUMBER_OF_KINDS 1

class c_Event
{
private:
protected:
    unsigned kind;
public:
    unsigned getKind ();
};

/*int c_Event::setKind (unsigned ikind)
{
    if (ikind && ikind <= NUMBER_OF_KINDS)
    {
        kind = ikind;
        return 0;
    }

    return 1;  // error
};*/

unsigned c_Event::getKind ()
{
    return kind;
};


#define EVENT_MOUSEBUTTON 1
class c_MouseButtonEvent : c_Event
{
private:
    unsigned type;
    unsigned button;
    unsigned state;
    unsigned x, y;
protected:
public:
    c_MouseButtonEvent (SDL_MouseButtonEvent ibutton);
    unsigned getButton ();
    unsigned getType ();
    unsigned getX ();
    unsigned getY ();
};

c_MouseButtonEvent::c_MouseButtonEvent (SDL_MouseButtonEvent ibutton)
{
    kind = EVENT_MOUSEBUTTON;
    type = ibutton.type;
    button = ibutton.button;
    state = ibutton.state;
    x = ibutton.x; y = ibutton.y;
};

unsigned c_MouseButtonEvent::getButton ()
{
    return button;
}

unsigned c_MouseButtonEvent::getType ()
{
    return type;
}
unsigned c_MouseButtonEvent::getX ()
{
    return x;
}

unsigned c_MouseButtonEvent::getY ()
{
    return y;
}


class c_EventManager
{
private:
    SDL_Event event;
    std::vector <c_Event*> events;
    std::vector <c_Event*>::iterator eventsIterator;
protected:
public:
    std::vector <c_Event*>* getEvents ();
    bool wasMousePressed ();

};

std::vector <c_Event*>* c_EventManager::getEvents ()
{
    std::cout << "Getting events...\n";
    while (!events.empty ())
    {
        free (events.back());
        events.pop_back ();
    }

    while (SDL_PollEvent (&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                std::cout << "SDL_MOUSEBUTTONDOWN\n";
                events.push_back ((c_Event*) new c_MouseButtonEvent (event.button));
                break;
        }
    }

    std::cout << "Got events.\n";

    return &events;
};

bool c_EventManager::wasMousePressed ()
{
    while (SDL_PollEvent (&event))
        if (event.type == SDL_MOUSEBUTTONDOWN)
            return true;

    return false;
};

#endif
