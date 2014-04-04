#ifndef MY_GRAPHICS_FUNCS
#define MY_GRAPHICS_FUNCS

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <assert.h>
#include <string>


SDL_Surface* loadImage (std::string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load (filename.c_str());
    if (loadedImage)
    {
        optimizedImage = SDL_DisplayFormat (loadedImage);
        if (optimizedImage)
        {
            Uint32 colorkey = SDL_MapRGB (optimizedImage->format, 0, 0xFF, 0xFF);
            SDL_SetColorKey (optimizedImage, SDL_SRCCOLORKEY, colorkey);
        }
        SDL_FreeSurface (loadedImage);
    }

    return optimizedImage;
}

SDL_Surface* Init (int w, int h, int bpp)
{
    SDL_Surface* screen = NULL;

    if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
    {
            assert (0);
        return NULL;
    }

    screen = SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE);
        assert (screen);

    return screen;
}

void applySurface (int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
                                                                                                                    assert (source);
                                                                                                                    assert (destination);

    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface (source, clip, destination, &offset);
}

void checkContact (bool* positions, SDL_Rect A, SDL_Rect B, int velX, int velY)
{
    //Reset position
    for (int i = 0; i< 4; i++)
        positions[i] = false;

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;


    //Calculate the sides of rect A
    leftA = A.x; rightA = A.x + A.w;
    topA = A.y; bottomA = A.y + A.h;
    //Calculate the sides of rect B
    leftB = B.x; rightB = B.x + B.w;
    topB = B.y; bottomB = B.y + B.h;


    if ((rightA == leftB) || ((rightA >= leftB) && (rightA - velX <= leftB)))
        if ((topA >= topB && topA < bottomB) || (bottomA <= bottomB && bottomA > topB) || (topA <= topB && bottomA >= bottomB))
            positions[0] = true;
    if ((topA == bottomB) || ((topA <= bottomB) && (topA - velY >= bottomB)))
        if ((leftA >= leftB && leftA < rightB) || (rightA <= rightB && rightA > leftB) || (leftA <= leftB && rightA >= rightB))
            positions[1] = true;
    if ((leftA == rightB) || ((leftA <= rightB) && (leftA - velX >= rightB)))
        if ((topA >= topB && topA < bottomB) || (bottomA <= bottomB && bottomA > topB) || (topA <= topB && bottomA >= bottomB))
            positions[2] = true;
    if ((bottomA == topB) || ((bottomA >= topB) && (bottomA - velY <= topB)))
        if ((leftA >= leftB && leftA < rightB) || (rightA <= rightB && rightA > leftB) || (leftA <= leftB && rightA >= rightB))
            positions[3] = true;

}

void snapKeystates (Uint8* keystates, bool* snap)
{
    assert (keystates); assert (snap);

    snap[0] = keystates[SDLK_RIGHT];
    snap[1] = keystates[SDLK_SPACE];
    snap[2] = keystates[SDLK_LEFT];
    snap[3] = keystates[SDLK_DOWN];
}

#endif
