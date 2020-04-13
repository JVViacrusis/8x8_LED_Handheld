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
//             PLATFORM CLASS             //
//                 START                  //
////////////////////////////////////////////
class DJ_Platform   //Hitbox starting point is the left pixel
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
//             PLATFORM CLASS             //
//                  END                   //
////////////////////////////////////////////


////////////////////////////////////////////
//             PLAYER CLASS               //
//                 START                  //
////////////////////////////////////////////
class DJ_Player // Hitbox starting point is the bottom pixel
{
    public:
        DJ_Player();
        void DrawOnScreen(Screen_Alt Screen);   //renders onto the screen

        void Init(int init_x, int init_y, int init_vel_y);  // Initialize pos/vel


        void Collide(DJ_Platform Platforms[3]); //Checks to see if it's colliding with any platforms. If it is, bounce.
        void UpdateVelocities(bool in[6]);    // Applies gravity and player inputs
        void Move();  //  Applies velocities to position

        
    private:
        int cur_x;
        int cur_y;

        int vel_x;
        int vel_y;

        int draw_Points[2][2];
};

DJ_Player::DJ_Player(){}
void DJ_Player::DrawOnScreen(Screen_Alt Screen)
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


void DJ_Player::Collide(DJ_Platform Platforms[3])
{
    for(int i = 0; i < 3; i++)
    {
        if(vel_y >= 1)   //if moving down
        {
            if(cur_y == Platforms[i].GetY())    // If colliding with platform's Y, proceed
            {
                if(cur_x == Platforms[i].GetX() || cur_x == Platforms[i].GetX() + 1)    // If colliding with either X pixels, bounce
                {
                    vel_y = -6;
                }
            }
        }
    }
}


void DJ_Player::Init(int init_x, int init_y, int init_vel_y)
{
    cur_x = init_x;
    cur_y = init_y;

    vel_y = init_vel_y;


    draw_Points[0][0] = 0;
    draw_Points[0][1] = 0;

    draw_Points[1][0] = 0;
    draw_Points[1][1] = -1;
}

void DJ_Player::UpdateVelocities(bool in[6])
{
    //Gravity
        if(vel_y < 1)   //up = negative. down = positive.
        {
            vel_y++;
        }

    //Player Input
    vel_x = 0;
    vel_x -= in[2];
    vel_x += in[3];
}


void DJ_Player::Move()
{
    cur_x += vel_x;
    // screen wrap-around
    if(cur_x > 7)
    {
        cur_x = 0;
    }else if(cur_x < 0)
    {
        cur_x = 7;
    }


    cur_y += (0 < vel_y) - (vel_y < 0);   //only move up by one pixel but keep the momentum
    // cur_y += vel_y;
}
////////////////////////////////////////////
//              PLAYER CLASS              //
//                  END                   //
////////////////////////////////////////////





////////////////////////////////////////////
//             VARIABLE DEFS              //
//                 START                  //
////////////////////////////////////////////
long DJ_Millis_GameTick_Prev;
int DJ_Millis_GameTick_Interval = 50;

DJ_Platform DJ_Platforms[3];
DJ_Player DJ_m_Player;


bool PlayingGame;
////////////////////////////////////////////
//             VARIABLE DEFS              //
//                 END                    //
////////////////////////////////////////////





////////////////////////////////////////////
//             FUNCTION DEFS              //
//                 START                  //
////////////////////////////////////////////
void GameStart()
{
    DJ_Millis_GameTick_Prev = millis();

    DJ_Platforms[0].Init(3, 6);
    DJ_Platforms[1].Init(6, 3);
    DJ_Platforms[2].Init(random(6), 0);

    DJ_m_Player.Init(3, 3, -1);

    PlayingGame = true;
}


////////////////////////////////////////////
//             FUNCTION DEFS              //
//                  END                   //
////////////////////////////////////////////




void Game_DoodleJump_Init(Screen_Alt Screen)
{
    randomSeed(analogRead(A6));
    for(int i = 0; i < 6; i++)
    {
        firstClick[i] = 1;
    }
    Screen.AllPixelsOff();


    GameStart();
}

void Game_DoodleJump_Periodic(Screen_Alt Screen, bool in[6])
{
    if(PlayingGame)
    {
        if(millis() - DJ_Millis_GameTick_Prev > DJ_Millis_GameTick_Interval)
        {
            DJ_Millis_GameTick_Prev = millis();
            Screen.AllPixelsOff();




            //PlayerUpdates
            DJ_m_Player.Collide(DJ_Platforms);
            DJ_m_Player.UpdateVelocities(in);
            DJ_m_Player.Move();



            //Renders
            for(int i = 0; i < sizeof(DJ_Platforms) / sizeof(DJ_Platforms[0]); i++)
            {
                DJ_Platforms[i].DrawOnScreen(Screen);
            }
            DJ_m_Player.DrawOnScreen(Screen);
        }
    }//else if(LostGame)
    
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
