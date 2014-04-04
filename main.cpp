#include "c_Game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


int main (int argc, char* args[])
{
    c_Game* game = new c_Game ();

    if (!game -> start (SCREEN_WIDTH, SCREEN_HEIGHT))
       // game -> exit ();
       return 0;
    else
        return  1; //game -> returnError ();

    return 0;
}
