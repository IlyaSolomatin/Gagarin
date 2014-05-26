#ifndef C_TEXTUREMANAGER
#define C_TEXTUREMANAGER

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "myGraphicsFuncs.h"
#include <assert.h>
#include <vector>
#include "c_Objects.h"
//#include <iostream>


class c_TextureManager
{
private:
    unsigned screenWidth;
    unsigned screenHeight;
    SDL_Surface* screen;
    c_ObjectsTree* objects;
    Uint32 lastTics;
    unsigned short fps;
    //s_Texture background;
    //s_Texture ship;
    //int shipCond;

    int loadTextures (c_ObjectsTree* iobjects);
    int clear ();
    int render ();
protected:
public:
    c_TextureManager ();
    int init (unsigned inScreenWidth, unsigned inScreenHeight, c_ObjectsTree* iobjects);
    int refreshScreen (c_ObjectsTree* iobjects);
    int switchShip ();
};

c_TextureManager::c_TextureManager ()
{
    screenWidth = 800; //DEFAULT
    screenHeight = 600; //DEFAULT
    fps = 36; //DEFAULT
    screen = NULL;
    objects = NULL;
    lastTics = SDL_GetTicks ();
};

int c_TextureManager::loadTextures (c_ObjectsTree* iobjects)
{
    assert (iobjects);
    std::cout << "loading textures... \n";



    c_ObjectsTreeIterator* treeIterator = iobjects -> getIterator ();
    c_ObjectsContainer* graphicsContainer = treeIterator -> getContainer (OBJECT_SHIP);
    c_ObjectsContainerIterator* graphicsIterator = graphicsContainer -> getIterator (iobjects -> getIterator ());
    c_Object* ographics = NULL;
    int error = false;
    while (ographics = graphicsIterator -> getNextObject ())
    {
        error = ((c_GraphicsObject*) ographics) -> loadTextures ();
        if (error)
        {
            assert (0);
            return error;
        }
    }

    return 0;

    /*int error = false;
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
            case OBJECT_STAR:
                std::cout << "load OBJECT_STAR\n";
                error = ((c_GraphicsObject*) *object) -> loadTextures ();
                if (error)
                {
                    assert (0);
                    return error;
                }
                break;
            case OBJECT_PLANET:
                std::cout << "load OBJECT_PLANET\n";
                error = ((c_GraphicsObject*) *object) -> loadTextures ();
                if (error)
                {
                    assert (0);
                    return error;
                }
                break;
        }*/
};

int c_TextureManager::init (unsigned inScreenWidth, unsigned inScreenHeight, c_ObjectsTree* iobjects)
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
        lastTics = SDL_GetTicks ();
        std::cout << "Inited\n";
        return 0; //OK
    }
    else
        return 1; //texture manager has been initialized

    return 2;     //smth's wrong
};

int c_TextureManager::render()
{
    std::vector <c_GraphicsObject*> graphics[3];

    //int borders[10];
    //for (int i = 0; i < 10; i++)
    //    borders[i] = 0;

    c_ObjectsTreeIterator* treeIterator = objects -> getIterator ();
    c_ObjectsContainer* graphicsContainer = treeIterator -> getContainer (OBJECT_SHIP);
    c_ObjectsContainerIterator* graphicsIterator = graphicsContainer -> getIterator (objects -> getIterator ());
    c_Object* ographics = NULL;
    int error = false;
    while (ographics = graphicsIterator -> getNextObject ())
        graphics[((c_GraphicsObject*)(ographics)) -> getTexture ().priority].push_back ((c_GraphicsObject*)(ographics));

    /*for (int i = 0; i < objects -> size (); i++)
        switch ((*objects)[i] -> getKind ())
        {
            case (3):
                graphics[((c_GraphicsObject*)((*objects)[i])) -> getTexture ().priority].push_back ((c_GraphicsObject*)((*objects)[i]));
                break;
            case (4):
                graphics[((c_GraphicsObject*)((*objects)[i])) -> getTexture ().priority].push_back ((c_GraphicsObject*)((*objects)[i]));
                break;
            case (OBJECT_STAR):
                graphics[((c_GraphicsObject*)((*objects)[i])) -> getTexture ().priority].push_back ((c_GraphicsObject*)((*objects)[i]));
                break;
            case (OBJECT_PLANET):
                graphics[((c_GraphicsObject*)((*objects)[i])) -> getTexture ().priority].push_back ((c_GraphicsObject*)((*objects)[i]));
                break;
        }*/

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < graphics[i].size (); j++)
        applySurface ((graphics[i][j] -> getTexture ()).xpos, (graphics[i][j] -> getTexture ()).ypos, (graphics[i][j] -> getTexture ()).surface, screen);

    return 0;
};

int c_TextureManager::refreshScreen (c_ObjectsTree* iobjects)
{
    assert (iobjects);
    objects = iobjects;

    render ();

    if (SDL_GetTicks () - lastTics < 1000 / fps)
    {
        printf ("delay %d\n", 1000 / fps - (SDL_GetTicks () - lastTics));
        SDL_Delay (1000 / fps - (SDL_GetTicks () - lastTics));

    }

    if (SDL_Flip (screen) == -1)
        {
            assert (0);
            return 1;
        }

    lastTics = SDL_GetTicks ();
    return 0;
};

#endif
