#ifndef INTERFACES
#define INTERFACES

#ifndef INTERFACE_BASIC
#define INTERFACE_BASIC 0

class interface_Basic
{
private:
protected:
public:
};

#endif

#ifndef INTERFACE_HASGRAPHICS
#define INTARFACE_HASGRAPHICS

class interface_HasGraphics
{
private:
protected:
    s_Texture texture;
    std::string** files;
    SDL_Surface** surfaces;
    unsigned int numberOfTextures;
public:
    interface_HasGraphics (unsigned int inot);
    virtual int loadTextures ();
    virtual unsigned int getxpos ();
    virtual unsigned int getypos ();
    virtual bool setxpos (int ixpos);
    virtual bool setypos (int iypos);
    virtual unsigned int getPriority ();
    virtual bool setPriority (int ipriority);
    virtual SDL_Surface* getSurface ();
    virtual bool setSurface (SDL_Surface* isurface);
    //virtual s_Texture getTexture ();
};

interface_HasGraphics::interface_HasGraphics (unsigned int inot)
{
    numberOfTextures = inot;
};

unsigned int interface_HasGraphics::getxpos ()
{
    return texture.xpos;
};

unsigned int interface_HasGraphics::getypos ()
{
    return texture.ypos;
};

bool interface_HasGraphics::setxpos (int ixpos)
{
    assert (ixpos >= 0 && ixpos < SCREEN_WIDTH);
    if (ixpos >= 0 && ixpos < SCREEN_WIDTH)
    {
        texture.xpos = ixpos;
        return true;
    }

    return false;
};

bool interface_HasGraphics::setypos (int iypos)
{
    assert (iypos >= 0 && iypos < SCREEN_HEIGHT);
    if (iypos >= 0 && iypos < SCREEN_HEIGHT)
    {
        texture.ypos = iypos;
        return true;
    }

    return false;
};

unsigned int interface_HasGraphics::getPriority ()
{
    return texture.priority;
};

bool interface_HasGraphics::setPriority (int ipriority)
{
    assert (ipriority >= 0);
    if (ipriority >= 0)
    {
        texture.priority = ipriority;
        return true;
    }

    return false;
};

SDL_Surface* interface_HasGraphics::getSurface ()
{
    return texture.surface;
};

bool interface_HasGraphics::setSurface (SDL_Surface* isurface)
{
    assert (isurface);
    if (isurface)
    {
        texture.surface = isurface;
        return true;
    }

    return false;
};

int interface_HasGraphics::loadTextures ()
{
    //std::cout << "loading textures to object..\n";
    for (int i = 0; i < numberOfTextures; i++)
    {
        surfaces[i] = loadImage (*files[i]);
        if (!surfaces[i])
        {
            assert (0);
            return 1;
        }
    }

    texture.surface = surfaces[0];

    //std::cout << "loading textures to object.. done\n";//
    return 0;
};

/*s_Texture interfaceHasGraphics::getTexture ()
{
    return texture;
};*/

#endif

#ifndef INTERFACE_ONMAP
#define INTERFACE_ONMAP

class interface_OnMap
{
private:
    float x;
    float y;
protected:
public:
    interface_OnMap ();
    virtual float getx ();
    virtual float gety ();
    virtual void setx (float ix);
    virtual void sety (float iy);
};

interface_OnMap::interface_OnMap ()
{
    x = 0;
    y = 0;
};

float interface_OnMap::getx ()
{
    return x;
};

float interface_OnMap::gety ()
{
    return y;
};

void interface_OnMap::setx (float ix)
{
    x = ix;
};

void interface_OnMap::sety (float iy)
{
    y = iy;
};

#endif

#ifndef INTERFACE_CLICKABLE
#define INTERFACE_CLICKABLE

class interface_Clickable: virtual public interface_HasGraphics
{
private:
    bool inFocus;
    bool hasBeenClicked;
protected:
public:
    interface_Clickable (unsigned int inot);
    virtual bool getInFocus ();
    virtual bool getHasBeenClicked ();
    virtual void setInFocus (bool ifocus);
    virtual void setHasBeenClicked (bool ickicked);
    virtual void clickMe ();
};

interface_Clickable::interface_Clickable (unsigned int inot): interface_HasGraphics (inot)
{
    inFocus = false;
    hasBeenClicked = false;
};

bool interface_Clickable::getInFocus ()
{
    return inFocus;
};

bool interface_Clickable::getHasBeenClicked ()
{
    return hasBeenClicked;
};

void interface_Clickable::setInFocus (bool ifocus)
{
    inFocus = ifocus;
};

void interface_Clickable::setHasBeenClicked (bool iclicked)
{
    hasBeenClicked = iclicked;
};

void interface_Clickable::clickMe ()
{
    setHasBeenClicked (true);
    setInFocus (true);
};

#endif

#ifndef INTERFACE_MOVABLE
#define INTERFACE_MOVABLE
class interface_Movable: virtual public interface_OnMap
{
private:
    float speed;
    float speedx;
    float speedy;
    //float angle;
    bool freeToMove;
protected:
public:
    interface_Movable ();
    virtual float getSpeed ();
    virtual float getSpeedx ();
    virtual float getSpeedy ();
    //virtual float getAngle ();
    virtual bool getFreeToMove ();
    virtual void setSpeed (float ispeed);
    virtual bool setSpeedx (float ispeedx);
    virtual bool setSpeedy (float ispeedy);
    //virtual void setAngle (float iangle);
    virtual void setFreeToMove (bool ifree);
    virtual bool moveMe ();
    virtual void stopMe ();
};

interface_Movable::interface_Movable (): interface_OnMap ()
{
    speed = 0;
    speedx = 0;
    speedy = 0;
    //angle = 0;
    freeToMove = true;
};

float interface_Movable::getSpeed ()
{
    return speed;
};

float interface_Movable::getSpeedx ()
{
    return speedx;
};

float interface_Movable::getSpeedy ()
{
    return speedy;
};

/*float interface_Movable::getAngle ()
{
    return angle;
};*/

bool interface_Movable::getFreeToMove ()
{
    return freeToMove;
};

void interface_Movable::setSpeed (float ispeed)
{
    speed = ispeed;
    //speedx = speed * cos (angle);
    //speedy = -speed * sin (angle);
};

bool interface_Movable::setSpeedx (float ispeedx)
{
    speedx = ispeedx;
    if (sqrt (speedx*speedx + speedy*speedy) > speed)
        return false;
    //speed = sqrt (speedx*speedx + speedy*speedy);
    /*angle = atan (-speedy/speedx);
    if (speedx < 0)
        angle += PI;*/

    return true;
};

bool interface_Movable::setSpeedy (float ispeedy)
{
    speedy = ispeedy;
    if (sqrt (speedx*speedx + speedy*speedy) > speed)
        return false;
    //speed = sqrt (speedx*speedx + speedy*speedy);
    /*angle = atan (-speedy/speedx);
    if (speedx < 0)
        angle += PI;*/

    return true;
};

/*void interface_Movable::setAngle (float iangle)
{
    angle = iangle;
    speedx = speed * cos (angle);
    speedy = - speed * sin (angle);
};*/

void interface_Movable::setFreeToMove (bool ifree)
{
    freeToMove = ifree;
};

bool interface_Movable::moveMe ()
{
    if (!freeToMove)
        return false;

    setx (getx () + getSpeedx ());
    sety (gety () + getSpeedy ());

    if (getx () < 50) {setx (50); stopMe ();}
    if (gety () < 50) {sety (50); stopMe ();}
    if (getx () > 750) {setx (750); stopMe ();}
    if (gety () > 550) {sety (550); stopMe ();}

    return true;
};

void interface_Movable::stopMe ()
{
    setSpeedx (0);
    setSpeedy (0);
};

#endif

#ifndef INTERFACE_ROTATABLE
#define INTERFACE_ROTATABLE
class interface_Rotatable
{
private:
    float anglef;
    int anglei;
    bool free;
protected:
public:
    interface_Rotatable ();
    virtual bool setAnglef (float iangle);
    virtual float getAnglef ();
    virtual bool setAnglei (int anglei);
    virtual int getAnglei ();
    virtual float rotateMe (float iangle);
    virtual bool isFree ();
};

 interface_Rotatable::interface_Rotatable ()
{
    anglef = 1;
    anglei = 0;
    free = true;
};

 bool interface_Rotatable::setAnglef (float iangle)
{
    bool returnFlag = false;
    anglef = iangle;
    anglei = floor (anglef);

    while (anglef < 0)
    {
        returnFlag = true;
        anglef += 2 * PI;
    }
    while (anglef >= 2*PI)
    {
        returnFlag = true;
        anglef -= 2 * PI;
    }

    return returnFlag;
};

 float interface_Rotatable::getAnglef ()
{
    assert (anglef >= 0);
    assert (anglef < 2* PI);
    return anglef;
};

 bool interface_Rotatable::setAnglei (int iangle)
{
    bool returnFlag = false;
    //anglef += iangle - anglei;
    anglei = iangle;

    while (anglei < 0)
    {
        returnFlag = true;
        anglei += 360;
    }
    if (anglei >= 360)
    {
        returnFlag = true;
        anglei = anglei % 360;
    }

    return returnFlag;
};

 int interface_Rotatable::getAnglei ()
{
    return anglei;
};

 float interface_Rotatable::rotateMe (float iangle)
{
    if (isFree ())
    {
        setAnglef (getAnglef () + iangle);
        anglei = floor (anglef);

        while (anglei < 0)
            anglei += 360;
        if (anglei >= 360)
            anglei = anglei % 360;
    }

    return anglef;
};

bool interface_Rotatable::isFree ()
{
    return free;
};

#endif

#ifndef INTERFACE_MOVABLEROTATABLE
#define INTERFACE_MOVABLEROTATABLE
class interface_MovableRotatable: virtual public interface_Movable, virtual public interface_Rotatable
{
private:
protected:
public:
    interface_MovableRotatable ();
    virtual void moveTo (float ix, float iy);

};

interface_MovableRotatable::interface_MovableRotatable (): interface_Movable (), interface_Rotatable ()
{
};

void interface_MovableRotatable::moveTo (float ix, float iy)
{
    setAnglef (atan (- (iy - gety ()) / (ix - getx())));
    if (ix < getx ())
        rotateMe (PI);
    setSpeedx (getSpeed () * cos(getAnglef ()));
    setSpeedy (-getSpeed () * sin(getAnglef ()));
};

#endif

#ifndef INTERFACE_MAYGENERATEEVENTS
#define INTERFACE_MAYGENERATEEVENTS
class interface_MayGenerateEvents: virtual interface_Basic
{
private:
    std::vector <c_Event*> generatedEvents;
protected:
public:
    void pushEvent (c_Event* ievent);
    c_Event* popeEvent ();
};

void pushEvent (c_Event* ievent)
{
    assert (ievent);
    if (ievent)
    {
        generatedEvents.push_back (ievent);
        return;
    }

    return;
};

c_Event* popEvent ()
{
    c_Event* ievent = generatedEvents.back ();
    assert (ievent);
    generatedEvents.pop_back ();
    return ievent;
};

#endif

#ifndef INTERFACE_SUBSCRIBABLE
#define INTERFACE_SUBSCRIBABLE

class interface_Subscribable: public interface_Basic
{
private:
    std::vector <c_Subscribtion*> subscribtions;
    //void* triggerFunction;
protected:
public:
    interface_Subscribable ();
    c_Subscribtion* addSubscribtion (c_Subscribtion* isubscribtion);
    void handleEvents ();
    //virtual bool trigger (void* ifunction, void* iparams);
    //virtual void setTriggerFunction (void* ifunction);
};

interface_Subscribable::interface_Subscribable (): interface_Basic ()
{
};

/*void interface_Subscribable::setTriggerFunction (void* ifunction)
{
    assert (ifunction)
    triggerFunction = ifunction;
};*/

c_Subscribtion* interface_Subscribable::addSubscribtion (c_Subscribtion* isubscribtion)
{
    assert (isubscribtion);
    if (isubscribtion)
    {
        subscribtions.push_back (isubscribtion);
        return subscribtions.back ();
    }

    return NULL;
};

void interface_Subscribable::handleEvents ()
{
    for (int i = 0; i < subscribtions.size (); i++)
    {
        if (subscribtions[i] -> getEvent ())
            subscribtions[i] -> handleEvent ();
    }
}

#endif // INTERFACE_SUBSCRIBABLE

#endif
