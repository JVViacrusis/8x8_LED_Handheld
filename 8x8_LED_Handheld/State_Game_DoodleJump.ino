//DONT NEED THIS BUT IT STOPS ERRORS
#include "Screen_Alt.h"



//TO DO LIST
/*
            - Game Flow Infastructure
                - bool DJ_PlayingGame
                - bool CanClick
                - bool ShowingScore
                - bool LostGame
                - bool PlayingLoseAnimation
                - bool DJ_GameStart //can also use for restart



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

        int CheckOutBounds(); //Checks if it is out of a specified bounds. If it is, re-initialize to the top of the game screen and add score
    
        int GetX(); //Get's current X position
        int GetY(); //Get's current Y position
        
        void SimCamUp();  // Simulates the camera going up by moving the platform down

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

int DJ_Platform::CheckOutBounds()
{
    if(cur_y > 7)
    {
        Init(int(random(6)), -1);
        return 1;
    }else
    {
        return 0;
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


void DJ_Platform::SimCamUp()
{
    cur_y++;
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

        bool CheckOutBounds(Screen_Alt Screen); //Check's to see if the player has fallen out of bounds. If it has, return true in order to lose game

        void Collide(DJ_Platform Platforms[3]); //Checks to see if it's colliding with any platforms. If it is, bounce.
        void UpdateVelocities(bool in[6]);    // Applies gravity and player inputs
        void Move();  //  Applies velocities to position

        int GetY();    // Get current Y position

        void SimCamUp(); // Simulate camera going up by moving player down
        
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


bool DJ_Player::CheckOutBounds(Screen_Alt Screen)
{
    if(cur_y > 9)
    {
        Screen.AllPixelsOff();
        return true;
    }else
    {
        return false;
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


int DJ_Player::GetY()
{
    return cur_y;
}


void DJ_Player::SimCamUp()
{
    cur_y++;
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
int DJ_Millis_GameTick_Interval = 65;

long DJ_Millis_ShowScore_Prev;
int DJ_Millis_ShowScore_Interval;

DJ_Platform DJ_Platforms[3];
DJ_Player DJ_m_Player;

bool DJ_PlayingGame;
bool DJ_LostGame;
bool DJ_ShowingScore;

int DJ_FinalScore;
int DJ_ScoreStppr;

bool DJ_IsWaiting;
long DJ_Millis_Wait_Prev;
int DJ_Millis_Wait_Interval = 4000;
////////////////////////////////////////////
//             VARIABLE DEFS              //
//                 END                    //
////////////////////////////////////////////





////////////////////////////////////////////
//             FUNCTION DEFS              //
//                 START                  //
////////////////////////////////////////////
void DJ_GameStart()
{
    DJ_Millis_GameTick_Prev = millis();
    
    DJ_Millis_ShowScore_Prev = millis();
    DJ_Millis_ShowScore_Interval = 0;

    DJ_Platforms[0].Init(3, 6);
    DJ_Platforms[1].Init(6, 3);
    DJ_Platforms[2].Init(random(6), 0);

    DJ_m_Player.Init(3, 3, -1);

    DJ_PlayingGame = true;
    DJ_LostGame = false;
    DJ_ShowingScore = false;

    DJ_FinalScore = 1;
    DJ_ScoreStppr = 1;

    DJ_IsWaiting = false;
    DJ_Millis_Wait_Prev = millis();
    DJ_Millis_Wait_Interval = 4000;
}


/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////


void DJ_ShowScore(Screen_Alt Screen)
{
    DJ_FinalScore = 70;
//if interval
        //reset interval
        //update interval time to correspond with score. (interval = 1000 - 100 * score with minimum of 100)
        //turn_pixel_on(scoreStppr);
        //ScoreStppr++;
        //if scoreStppr > finalScore
            //simon_ShowingScore = false;

    if(millis() - DJ_Millis_ShowScore_Prev > DJ_Millis_ShowScore_Interval)
    {
        if(!DJ_IsWaiting)
        {
            DJ_Millis_ShowScore_Prev = millis();
            DJ_Millis_ShowScore_Interval = 500 - (50 * (DJ_FinalScore - DJ_ScoreStppr));
            DJ_Millis_ShowScore_Interval = DJ_Millis_ShowScore_Interval > 60 ? DJ_Millis_ShowScore_Interval : 60;

            int x = (DJ_ScoreStppr - 1) % 8;
            int y = ((DJ_ScoreStppr - 1) / 8) % 8;
            Screen.EditPixel(x, y, 1);

            DJ_ScoreStppr++;
        }

        if(DJ_ScoreStppr == DJ_FinalScore && !DJ_IsWaiting)
        {
            //start witing for a short time
            DJ_IsWaiting = true;
            DJ_Millis_Wait_Prev = millis();
        }else if(DJ_IsWaiting && millis() - DJ_Millis_Wait_Prev > DJ_Millis_Wait_Interval)
        {
            DJ_ShowingScore = false;
        }
    }
    
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


    DJ_GameStart();
}

void Game_DoodleJump_Periodic(Screen_Alt Screen, bool in[6])
{
    if(DJ_PlayingGame)
    {
        if(millis() - DJ_Millis_GameTick_Prev > DJ_Millis_GameTick_Interval)
        {
            DJ_Millis_GameTick_Prev = millis();
            Screen.AllPixelsOff();

            //Player updates
            DJ_m_Player.Collide(DJ_Platforms);
            DJ_m_Player.UpdateVelocities(in);
            DJ_m_Player.Move();
            DJ_LostGame = DJ_m_Player.CheckOutBounds(Screen);
            DJ_ShowingScore = DJ_LostGame;
            DJ_PlayingGame = !DJ_LostGame;
            if(DJ_PlayingGame)  //Dont do these things if the player has fallen out of bounds
            {
                //Check camera follow
                if(DJ_m_Player.GetY() < 1)
                {
                    for(int i = 0; i < sizeof(DJ_Platforms) / sizeof(DJ_Platforms[0]); i++)
                    {
                        DJ_Platforms[i].SimCamUp();
                    }   
                    DJ_m_Player.SimCamUp();
                }

                // Platform Updates
                for(int i = 0; i < sizeof(DJ_Platforms) / sizeof(DJ_Platforms[0]); i++)
                {
                    DJ_FinalScore += DJ_Platforms[i].CheckOutBounds();
                }   

                //Renders
                for(int i = 0; i < sizeof(DJ_Platforms) / sizeof(DJ_Platforms[0]); i++)
                {
                    DJ_Platforms[i].DrawOnScreen(Screen);
                }
                DJ_m_Player.DrawOnScreen(Screen);
            }
        }
    }else if(DJ_LostGame)
    {
        if(DJ_ShowingScore)
        {
            DJ_ShowScore(Screen);
        }
        else
        {
            DJ_GameStart();
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
