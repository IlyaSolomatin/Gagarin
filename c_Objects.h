#ifndef C_OBJECTS
#define C_OBJECTS

#include <math.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

struct s_Texture
{
    SDL_Surface* surface;
    unsigned priority;
    unsigned xpos;
    unsigned ypos;
};

#ifndef OBJECT_OBJECT
#define OBJECT_OBJECT 1

class c_Object
{
private:
protected:
    unsigned kind;
    std::vector <unsigned short> inheritanceList;
public:
    c_Object ();
    unsigned getKind ();
    std::vector <unsigned short>* getInheritanceList ();
    int think ();
};

c_Object::c_Object ()
{
    inheritanceList.push_back (OBJECT_OBJECT);
};

unsigned c_Object::getKind ()
{
    return kind;
};

std::vector <unsigned short>* c_Object::getInheritanceList ()
{
    return &inheritanceList;
};

int c_Object::think ()
{
    return 1;
};

#endif

#ifndef OBJECT_GRAPHICSOBJECT
#define OBJECT_GRAPHICSOBJECT 2
class c_GraphicsObject: public c_Object, public interface_HasGraphics
{
private:
protected:
    s_Texture texture;
    std::string* files[200];
    SDL_Surface* surfaces[200];
    int numberOfTextures;
public:
    c_GraphicsObject ();
    int loadTextures ();
    s_Texture getTexture ();
};

c_GraphicsObject::c_GraphicsObject (): c_Object (), interface_HasGraphics (200)
{
    inheritanceList.push_back (OBJECT_GRAPHICSOBJECT);
};

int c_GraphicsObject::loadTextures ()
{
    std::cout << "loading textures to object..\n";
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

    std::cout << "loading textures to object.. done\n";//
    return 0;
};

s_Texture c_GraphicsObject::getTexture ()
{
    return texture;
};

#endif

#ifndef OBJECT_STAR
#define OBJECT_STAR 7

class c_Star: public c_GraphicsObject
{
private:
    unsigned int mass;
    float x;
    float y;
protected:
public:
    c_Star (unsigned int imass);
    //int setMass (unsigned int imass);
    unsigned int getMass ();
    float getx ();
    float gety ();
};

c_Star::c_Star (unsigned int imass) : c_GraphicsObject ()
{
    inheritanceList.push_back (OBJECT_STAR);
    kind = OBJECT_STAR;
    texture.surface = NULL;
    texture.priority = 1;
    x = 400;
    y = 300;

    texture.xpos = 340; //floor (x) - texture.surface -> w / 2;
    texture.ypos = 240; //floor (y) - texture.surface -> h / 2;
    numberOfTextures = 1;
    files[0] = new std::string ("star.png");

    mass = imass;
};

unsigned int c_Star::getMass ()

{
    return mass;
};

float c_Star::getx ()
{
    return x;
};

float c_Star::gety ()
{
    return y;
};

#endif

#ifndef OBJECT_SYSTEM
#define OBJECT_SYSTEM 6
class c_System: protected c_Object
{
private:
    //string name;
    c_Star* star;
protected:
public:
    c_System (c_Star* istar);
    c_Star* getStar ();
};

c_System::c_System (c_Star* istar) : c_Object ()
{
    inheritanceList.push_back (OBJECT_SYSTEM);
    assert (istar);
    star = istar;
};

c_Star* c_System::getStar ()
{
    return star;
}


#endif // OBJECT_SYSTEM

#ifndef OBJECT_BACKGROUND
#define OBJECT_BACKGROUND 3
class c_Background: public c_GraphicsObject
{
public:
    c_Background ();
};

c_Background::c_Background (): c_GraphicsObject ()
{
    inheritanceList.push_back (OBJECT_BACKGROUND);
    kind = OBJECT_BACKGROUND;
    texture.surface = NULL;
    texture.priority = 0;
    texture.xpos = 0; texture.ypos = 0;
    numberOfTextures = 1;
    files[0] = new std::string("background.jpeg");
};

#endif

#ifndef OBJECT_SHIP
#define OBJECT_SHIP 4
#define LEFT 0
#define RIGHT 1
class c_Ship: public c_GraphicsObject, virtual public interface_MovableRotatable
{
private:
protected:
    //float x, y;
    //float speed;
    //float xspeed, yspeed;
    float xdest, ydest;
    bool destChanged;
    SDL_Surface* leftSurface;
    SDL_Surface* rightSurface;
public:
    c_Ship ();
    int think ();
    //float getSpeed ();
    //float getXSpeed ();
    //float getYSpeed ();
    float getXDest ();
    int setXDest (float ix);
    float getYDest ();
    int setYDest (float iy);
    int setDestChanged (bool i);
};

c_Ship::c_Ship (): c_GraphicsObject (), interface_MovableRotatable ()
{
    inheritanceList.push_back (OBJECT_SHIP);
    kind = OBJECT_SHIP;
    texture.surface = NULL;
    texture.priority = 2;
    texture.xpos = 0; texture.ypos = 0;
    //x = 0; y = 0;
    setSpeed (5);
    //xspeed = 0; yspeed = 0;
    xdest = 0; ydest = 0;
    destChanged = false;

    numberOfTextures = 200;
    //files[LEFT] = new std::string ("human_ship_120.bmp");
    //files[RIGHT] = new std::string ("human_ship_020.bmp");
    for (int i = 0; i < numberOfTextures; i++)
    {
        files[i] = new std::string ("human_ship");
        *files[i] += '\\';
        *files[i] += ("human_ship_");
        *files[i] += (i+1)/100 + '0';
        *files[i] += ((i+1)%100)/10 + '0';
        *files[i] += (i+1)%10 + '0';
        *files[i] += ".bmp";

        std::cout << *files[i];
    }
};

int c_Ship::think ()
{
    std::cout << "Ship thinking...\n";

    if (destChanged)
    {
        //xspeed = speed * (xdest - x) / sqrt ((xdest - x)*(xdest - x) + (ydest - y)*(ydest - y));
        //yspeed = speed * (ydest - y) / sqrt ((xdest - x)*(xdest - x) + (ydest - y)*(ydest - y));

        moveTo (xdest, ydest);

        /*if (xspeed > 0)
            texture.surface = surfaces[RIGHT];
        if (xspeed < 0)
            texture.surface = surfaces[LEFT];*/

    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!" << int ((getAnglef ()) / (PI / 200.0));

    texture.surface = surfaces[int ((getAnglef ()) / (2*PI / 200.0))];

        destChanged = false;
    }

    moveMe ();

    if (getSpeedx () > 0)
        {
            if (getx () >= xdest)
            {
                stopMe ();
            }
        }
        else
            if (getSpeedx () < 0)
            {
                if (getx () <= xdest)
                {
                    stopMe ();
                }
            }
            else
            {
                if (getSpeedy () > 0)
                {

                    if (gety () >= ydest)
                    {
                        stopMe ();
                    }
                }
                if (getSpeedy () < 0)
                {
                    if (gety () <= ydest)
                    {
                        stopMe ();
                    }
                }
            }

    //x += xspeed;
    //y += yspeed;

    texture.xpos = floor (getx ()) - texture.surface -> w / 2;
    texture.ypos = floor (gety ()) - texture.surface -> h / 2;

    //std::cout << "*********************************************texture.xpos = " << xdest << "\n";
    //std::cout << "*********************************************texture.xpos = " << ydest << "\n";

    return 0;
};

/*float c_Ship::getSpeed ()
{
    return speed;
};

float c_Ship::getXSpeed ()
{
    return xspeed;
};
float c_Ship::getYSpeed ()
{
    return yspeed;
};
*/
float c_Ship::getXDest ()
{
    return xdest;
};

int c_Ship::setXDest (float ix)
{
    xdest = ix;

    return 0;
};
float c_Ship::getYDest ()
{
    return ydest;
};
int c_Ship::setYDest (float iy)
{
    ydest = iy;

    return 0;
};
int c_Ship::setDestChanged (bool i)
{
    destChanged = i;

    return 0;
};

#endif

#ifndef OBJECT_PLANET
#define OBJECT_PLANET 5

#define GRAVITT_CONST 0.00006674 //10^6 km^3/ (10^21 kg * c^2)

class c_Planet: public c_GraphicsObject
{
private:
    unsigned int orbit; // 10^6 km
    c_System* homeSystem;
    unsigned short race;
    float x, y;
    float speed;
    float angularSpeed;
    float xspeed, yspeed;
    float angle;
    unsigned int mass; //10^21 kg

protected:
public:
    c_Planet (int iorbit, unsigned int imass, float iangle, float iangularSpped, c_System* ihomeSystem, unsigned short irace);
    int think ();
    c_System* getHomeSystem ();
    unsigned short getRace ();
};

c_Planet::c_Planet (int iorbit, unsigned int imass, float iangle, float iangularSpped, c_System* ihomeSystem, unsigned short irace): c_GraphicsObject ()
{
    inheritanceList.push_back (OBJECT_PLANET);
    orbit = iorbit;
    mass = imass;
    homeSystem = ihomeSystem;
    race = irace;
    kind = OBJECT_PLANET;
    texture.surface = NULL;
    texture.priority = 1;
    texture.xpos = 0; texture.ypos = 0;
    //x = ((homeSystem -> getStar () -> getTexture ()).xpos + (homeSystem -> getStar () -> getTexture()).surface -> w / 2 + orbit * cos (angle) - (this -> getTexture ()).surface -> w / 2);
    //y = ((homeSystem -> getStar () -> getTexture ()).ypos + (homeSystem -> getStar () -> getTexture()).surface -> h / 2 - orbit * cos (angle) - (this -> getTexture ()).surface -> h / 2);
    x = 400;
    y = 300;
    angularSpeed = iangularSpped;//sqrt (GRAVITY_CONST * homeSystem -> star -> mass / (orbit*orbit*orbit)); //1/s
    speed = angularSpeed * orbit; // 10^6 km/s
    angle = iangle;
    xspeed = 0; yspeed = 0;

    numberOfTextures = 1;
    files[0] = new std::string ("planet.png");
};

c_System* c_Planet::getHomeSystem ()
{
    return homeSystem;
};

unsigned short c_Planet::getRace ()
{
    return race;
};

int c_Planet::think ()
{
    angle += angularSpeed;
    if (angle > 2 * 3.14159265358)
        angle = angle - angle * floor (angle / (2 * 3.14159265358));

    //x = (homeSystem -> getStar () -> getTexture ()).xpos + (homeSystem -> getStar () -> getTexture()).surface -> w / 2 + orbit * cos (angle) - (this -> getTexture ()).surface -> w / 2;
    //y = (homeSystem -> getStar () -> getTexture ()).ypos + (homeSystem -> getStar () -> getTexture()).surface -> h / 2 + orbit * sin (angle) - (this -> getTexture ()).surface -> h / 2;

    x = homeSystem -> getStar () -> getx () + orbit * cos (angle);
    y = homeSystem -> getStar () -> gety () + orbit * sin (angle);

    texture.xpos = floor (x) - texture.surface -> w / 2;
    texture.ypos = floor (y) - texture.surface -> h / 2;

    return 0;

};

#endif

#endif
