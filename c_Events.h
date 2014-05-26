#ifndef EVENTS
#define EVENTS

#ifndef EVENT
#define EVENT

class c_Event
{
private:
    unsigned int type;
protected:
    void* params;
public:
    c_Event ();
    unsigned int getType ();
    void setType (unsigned int itype);
    virtual void* getParams ();
    virtual void setParams ();
};

c_Event::c_Event ()
{
};

unsigned int c_Event::getType ()
{
    return type;
};

void c_Event::setType (unsigned int itype)
{
    type = itype;
};

void* c_Event::getParams ()
{
    return params;
};

void c_Event::setParams ()
{
};

#endif

#ifndef MOUSEBUTTON_EVENT
#define MOUSEBUTTON_EVENT 1

class c_MouseButtonEvent: public c_Event
{
private:
    SDL_MouseButtonEvent mbeparams;
protected:
public:
    c_MouseButtonEvent (SDL_MouseButtonEvent imbeparams);
    virtual void setParams ();
};

c_MouseButtonEvent::c_MouseButtonEvent (SDL_MouseButtonEvent imbeparams): c_Event ()
{
    setType (MOUSEBUTTON_EVENT);

    mbeparams.type = imbeparams.type;
    mbeparams.button = imbeparams.button;
    mbeparams.state = imbeparams.state;
    mbeparams.x = imbeparams.x;
    mbeparams.y = mbeparams.y;

    this -> setParams ();
};

void c_MouseButtonEvent::setParams ()
{
    params = &mbeparams;
};

#endif // MOUSEBUTTON_EVENT

#endif
