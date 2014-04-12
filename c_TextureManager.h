#ifndef C_TEXTUREMANAGER
#define C_TEXTUREMANAGER

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "myGraphicsFuncs.h"
#include <assert.h>
#include <vector>
#include "cl_Object.h"
//#include <iostream>


class c_TextureManager
{
private:
    unsigned screenWidth;
    unsigned screenHeight;
    SDL_Surface* screen;
    std::vector <c_Object*>* objects;
    //s_Texture background;
    //s_Texture ship;
    //int shipCond;

    int loadTextures (std::vector <c_Object*>* iobjects);
    int clear ();
    int render ();
protected:
public:
    c_TextureManager ();
    int init (unsigned inScreenWidth, unsigned inScreenHeight, std::vector <c_Object*>* iobjects);
    int refreshScreen (std::vector <c_Object*>* iobjects);
    int switchShip ();
};

c_TextureManager::c_TextureManager ()
{
    screenWidth = 800; //DEFAULT
    screenHeight = 600; //DEFAULT
    screen = NULL;
    objects = NULL;
};

int c_TextureManager::loadTextures (std::vector <c_Object*>* iobjects)
{
    assert (iobjects);
    std::cout << "loading textures... \n";
    int error = false;
    for (std::vector <c_Object*>::iterator object = iobjects -> begin (); object < iobjects -> end (); object++)
        switch (((c_Object*) *object) -> getKind ())
        {
            case 3:
                //assert (0);
                std::cout << "load 3\n";
                error = ((c_GraphicsObject*) *object) -> loadTextures ();
                if (error)
                {
                    assert (0);
                    return error;
                }
                break;
            case 4:
                std::cout << "load 4\n";
                error = ((c_GraphicsObject*) *object) -> loadTextures ();
                if (error)
                {
                    assert (0);
                    return error;
                }
                break;
        }

        return 0;
};

int c_TextureManager::init (unsigned inScreenWidth, unsigned inScreenHeight, std::vector <c_Object*>* iobjects)
{
    assert (iobjects);
    assert (!screen);
    if (!screen)
    {
        screen = NULL;
        if (SDL_Init( SDL_INIT_EVERYTHING ) != -1)
            screen = SDL_SetVideoMode (inScreenWidth, inScreenHeight, 32, SDL_SWSURFACE);
        assert (screen);
        std::cout << "SDL inited\n";

        int error = 0;
        if (error = loadTextures (iobjects))
        {
            assert (!error);
            return error;
        }

        std::cout << "Inited\n";
        return 0; //OK
    }
    else
        return 1; //texture manager has been initialized

    return 2;     //smth's wrong
};

int c_TextureManager::render()
{
    std::vector <c_GraphicsObject*> graphics[2];

    //int borders[10];
    //for (int i = 0; i < 10; i++)
    //    borders[i] = 0;

    for (int i = 0; i < objects -> size (); i++)
        switch ((*objects)[i] -> getKind ())
        {
            case (3):
                graphics[((c_GraphicsObject*)((*objects)[i])) -> getTexture ().priority].push_back ((c_GraphicsObject*)((*objects)[i]));
                break;
            case (4):
                graphics[((c_GraphicsObject*)((*objects)[i])) -> getTexture ().priority].push_back ((c_GraphicsObject*)((*objects)[i]));
                break;
        }

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < graphics[i].size (); j++)
        applySurface ((graphics[i][j] -> getTexture ()).xpos, (graphics[i][j] -> getTexture ()).ypos, (graphics[i][j] -> getTexture ()).surface, screen);

    return 0;
};

int c_TextureManager::refreshScreen (std::vector <c_Object*>* iobjects)
{
    assert (iobjects);
    objects = iobjects;

    render ();

    if (SDL_Flip (screen) == -1)
        {
            assert (0);
            return 1;
        }
    SDL_Delay (75);
    return 0;
};

#endif
