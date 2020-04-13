//DONT NEED THIS BUT IT STOPS ERRORS
#include "Screen_Alt.h"



//TO DO LIST
/*
            - Game Flow Infastructure
                - bool PlayingGame
                - bool CanClick
                - bool ShowingScore
                - bool LostGame
                - bool PlayingLoseAnimation
                - bool GameStart //can also use for restart



            - Game Tick Speed / Timer
            - Player
                - pos
                - velocity
            - Platform //calculate the number needed because if they are spawning at set intervals you should need a finite amount
            - Camera ? (maybe just shift everyone's Y down by 1 if player reaches a certain Y)
            - 
*/




//DEV NOTES
/*

*/


////////////////////////////////////////////
//             FUNCTION DEFS              //
//                 START                  //
////////////////////////////////////////////





/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////





////////////////////////////////////////////
//             FUNCTION DEFS              //
//                  END                   //
////////////////////////////////////////////



////////////////////////////////////////////
//             PLAYER CLASS               //
//                 START                  //
////////////////////////////////////////////
class DJ_Player
{
    public:
        DJ_Player();

        void Init(int init_x, int init_y);  // Initialize pos/vel

        void ApplyGravity();    // Applies velocity to position and adds to gravity

        void Collide(); //Checks to see if it's colliding with any platforms. If it is, bounce.  //(DJ_Platform[x])
        
        void Move(bool in[6]);  //  Applies operator input to x velocity

        void DrawOnScreen(Screen_Alt Screen);   //renders onto the screen

    private:
        int cur_x;
        int cur_y;

        int vel_x;
        int vel_y;

        int draw_Points[2][2];
};
////////////////////////////////////////////
//              PLAYER CLASS              //
//                  END                   //
////////////////////////////////////////////


////////////////////////////////////////////
//             PLATFORM CLASS             //
//                 START                  //
////////////////////////////////////////////
class DJ_Platform
{
    public:
        DJ_Platform();

        void Init(int init_x, int init_y); // Initialize pos
        void DrawOnScreen(Screen_Alt Screen);   // Draws on screen

        void CheckBounds(); //Checks if it is out of a specified bounds. If it is, re-initialize to the top of the game screen
    
        int GetX(); //Get's current X position
        int GetY(); //Get's current Y position

        

    private:
        int cur_x;
        int cur_y;

        int draw_Points[2][2];
};

DJ_Platform::DJ_Platform(){}
void DJ_Platform::DrawOnScreen(Screen_Alt Screen)
{
    //draw the current
    for(int i = 0; i < sizeof(draw_Points) / sizeof(draw_Points[0]); i++)
    {
        //If within the bounds of the screen
        if(cur_x + draw_Points[i][0] >= 0 && cur_x + draw_Points[i][0] <= 7 && cur_y + draw_Points[i][1] >= 0 && cur_y + draw_Points[i][1] <= 7)
        {
            Screen.EditPixel(cur_x + draw_Points[i][0], cur_y + draw_Points[i][1], 1);
        }    
    }
}

void DJ_Platform::Init(int init_x, int init_y)
{
    cur_x = init_x;
    cur_y = init_y;


    draw_Points[0][0] = 0;
    draw_Points[0][1] = 0;

    draw_Points[1][0] = 1;
    draw_Points[1][1] = 0;
}

void DJ_Platform::CheckBounds()
{
    if(cur_y > 7)
    {
        Init(int(random(6), 0), 0);
    }
}

int DJ_Platform::GetX()
{
    return cur_x;
}

int DJ_Platform::GetY()
{
    return cur_y;
}
////////////////////////////////////////////
//              PLAYER CLASS              //
//                  END                   //
////////////////////////////////////////////



long DJ_Millis_GameTick_Prev;
int DJ_Millis_GameTick_Interval = 100;

DJ_Platform Platforms[2];

void Game_DoodleJump_Init(Screen_Alt Screen)
{
    for(int i = 0; i < 6; i++)
    {
        firstClick[i] = 1;
    }
    Screen.AllPixelsOff();

    DJ_Millis_GameTick_Prev = millis();

    Platforms[0].Init(3, 6);
    Platforms[1].Init(6, 3);
}

void Game_DoodleJump_Periodic(Screen_Alt Screen, bool in[6])
{
    if(millis() - DJ_Millis_GameTick_Prev > DJ_Millis_GameTick_Interval)
    {
        DJ_Millis_GameTick_Prev = millis();
        Screen.AllPixelsOff();




        for(int i = 0; i < sizeof(Platforms) / sizeof(Platforms[0]); i++)
        {
            Platforms[i].DrawOnScreen(Screen);
        }
    }
}


enum State Game_DoodleJump_SwitchCheck(Screen_Alt Screen, bool in[6])
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
