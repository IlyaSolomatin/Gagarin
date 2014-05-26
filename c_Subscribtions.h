#ifndef SUBSCRIBTIONS
#define SUBSCRIBTIONS

#ifndef SUBSCRIBTION
#define SUBSCRIBTION

class c_Subscribtion
{
private:
    unsigned int triggeringEventType;
    c_Event* event;
protected:
    void (*eventFunction) (c_Event* ievent);
public:
    c_Subscribtion (void (*ieventFunction) (c_Event* ievent));
    void setTriggeringEventType (unsigned int itype);
    unsigned int getTriggeringEventType ();
    c_Event* getEvent ();
    void resetSubscribtion ();
    void setEvent (c_Event* ievent);
    virtual bool trigger (c_Event* ievent);
    virtual void handleEvent ();
};

c_Subscribtion::c_Subscribtion (void (*ieventFunction) (c_Event* ievent))
{
    triggeringEventType = 0;
    assert (ieventFunction);
    eventFunction = ieventFunction;
    event = NULL;
};

void c_Subscribtion::setTriggeringEventType (unsigned int itype)
{
    triggeringEventType = itype;
};

unsigned int c_Subscribtion::getTriggeringEventType ()
{
    return triggeringEventType;
};

c_Event* c_Subscribtion::getEvent ()
{
    return event;
};

void c_Subscribtion::setEvent (c_Event* ievent)
{
    assert (ievent);
    event = ievent;
};

void c_Subscribtion::resetSubscribtion ()
{
    event = NULL;
};

bool c_Subscribtion::trigger (c_Event* ievent)
{
    assert (ievent);
    return false;
};

void c_Subscribtion::handleEvent ()
{
    assert (getEvent ());
};

#endif // SUBSCRIBTION

#ifndef SUBSCRIBTION_MOUSEBUTTON
#define SUBSCRIBTION_MOUSEBUTTON

class c_Subscribtion_MouseButton: virtual public c_Subscribtion
{
public:
    c_Subscribtion_MouseButton (void (*ieventFunction) (c_Event* ievent));
    virtual bool trigger (c_Event* ievent);
    virtual void handleEvent ();
};

c_Subscribtion_MouseButton::c_Subscribtion_MouseButton (void (*ieventFunction) (c_Event* ievent)): c_Subscribtion (ieventFunction)
{
    setTriggeringEventType (MOUSEBUTTON_EVENT);
};

bool c_Subscribtion_MouseButton::trigger (c_Event* ievent)
{
    assert (ievent);
    c_MouseButtonEvent* mbevent = (c_MouseButtonEvent*) ievent;
    SDL_MouseButtonEvent* sdlmbevent = (SDL_MouseButtonEvent*)(mbevent -> getParams ());
    if (sdlmbevent -> type == SDL_MOUSEBUTTONDOWN && sdlmbevent -> button == SDL_BUTTON_LEFT)
        return true;

    return false;
};

void c_Subscribtion_MouseButton::handleEvent ()
{
    (*eventFunction) (getEvent ());
    resetSubscribtion ();
};

#endif

#endif
