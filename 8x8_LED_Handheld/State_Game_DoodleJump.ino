//DONT NEED THIS BUT IT STOPS ERROR`S
#include "Screen_Alt.h"





void Game_DoodleJump_Init(Screen_Alt &Screen)
{
    for(int i = 0; i < 6; i++)
    {
        firstClick[i] = 1;
    }

    byte newScreen[8] = 
    {
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00001111,
        B00001001,
        B00001001,
        B00001111,
    };
    Screen.EditFullScreen(newScreen);
}


void Game_DoodleJump_Periodic(Screen_Alt &Screen, bool in[6])
{

}


enum State Game_DoodleJump_SwitchCheck(Screen_Alt &Screen, bool in[6])
{
    State ReturnState = GAME_DOODLEJUMP;

    if(in[3] && in[1] && in[4])
    {
        ReturnState = MENU;
    }

    return ReturnState;
}






/* Elements
        1x2 Character
        3x1 platforms

        physics
            gravity (acceleration)
            upwards velocity
        

        drawing
            100x1
*/
