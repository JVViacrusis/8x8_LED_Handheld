#include "Screen_Alt.h"


////////////////////////////////////////////
//              LAYER CLASS               //
//                 START                  //
////////////////////////////////////////////
class Stacker_Layer
{
    public:
        Stacker_Layer();

        void Init(int init_x, int init_y, int init_vel_x, int init_size);

//        void Move(int x_Move, int y_Move);

        void DrawOnScreen(Screen_Alt Screen);

        int cur_x;
        int cur_y;

        int vel_x;

        int cur_size;
        int draw_Points[3][2];

};

Stacker_Layer::Stacker_Layer(){}

void Stacker_Layer::Init(int init_x, int init_y, int init_vel_x, int init_size)
{
    cur_x = init_x;
    cur_y = init_y;
    vel_x = init_vel_x;
    cur_size = init_size;

    draw_Points[0][0] = 0;
    draw_Points[0][1] = 0;

    draw_Points[1][0] = 0;
    draw_Points[1][1] = 0;

    draw_Points[2][0] = 0;
    draw_Points[2][1] = 0;
    
    if(cur_size >= 2)
    {
        draw_Points[1][0] = 1;
        draw_Points[1][1] = 0;
    }
    if(cur_size >= 3)
    {
        draw_Points[2][0] = 2;
        draw_Points[2][1] = 0;    
    }
}

//void Stacker_Layer::Move(int x_Move, int y_Move)
//{
//    cur_x += vel_x;
//
//    //rebound off walls
//    if(cur_x <= 0 && vel_x < 0)  //if at left wall and going left
//    {
//        vel_x *= -1;
//    }
//    if(cur_x >= 8-cur_size && vel_x > 0)  //if right side of layer at right wall and going right
//    {
//        vel_x *= -1;
//    }
//}

void Stacker_Layer::DrawOnScreen(Screen_Alt Screen)
{
    //draw the current
    for(int i = 0; i < 3; i++)
    {
//        //If within the bounds of the screen
        if(cur_x + draw_Points[i][0] >= 0 && cur_x + draw_Points[i][0] <= 7 && cur_y + draw_Points[i][1] >= 0 && cur_y + draw_Points[i][1] <= 7)
        {
            Screen.EditPixel(cur_x + draw_Points[i][0], cur_y + draw_Points[i][1], 1);
        }    
    }   
}

////////////////////////////////////////////
//              LAYER CLASS               //
//                  END                   //
////////////////////////////////////////////




////////////////////////////////////////////
//             VARIABLE DEFS              //
//                 START                  //
////////////////////////////////////////////
long Stacker_Millis_GameTick_Prev;
int Stacker_Millis_GameTick_Interval;

long Stacker_Millis_ShowScore_Prev;
int Stacker_Millis_ShowScore_Interval;

bool Stacker_PlayingGame;
bool Stacker_LostGame;
bool Stacker_ShowingScore;

int Stacker_FinalScore;
int Stacker_ScoreStppr;

bool Stacker_IsWaiting;
long Stacker_Millis_Wait_Prev;
int Stacker_Millis_Wait_Interval;


Stacker_Layer Stacker_Layers[7];
////////////////////////////////////////////
//             VARIABLE DEFS              //
//                 END                    //
////////////////////////////////////////////




////////////////////////////////////////////
//             FUNCTION DEFS              //
//                 START                  //
////////////////////////////////////////////
void Stacker_GameStart()
{
    Stacker_Millis_GameTick_Prev = millis();
    Stacker_Millis_GameTick_Prev = 50;

    Stacker_Millis_ShowScore_Prev = millis();
    Stacker_Millis_ShowScore_Interval = 0;

    Stacker_PlayingGame = true;
    Stacker_LostGame = false;
    Stacker_ShowingScore = false;

    Stacker_FinalScore = 1;
    Stacker_ScoreStppr = 1;

    Stacker_IsWaiting = false;
    Stacker_Millis_Wait_Prev = millis();
    Stacker_Millis_Wait_Interval = 4000;


    Stacker_Layers[0].Init(3, 7, 1, 3);
    Stacker_Layers[1].Init(3, 1, 0, 1);
    Stacker_Layers[2].Init(3, 2, 0, 2);
    Stacker_Layers[3].Init(3, 3, 0, 3);
    Stacker_Layers[4].Init(3, 4, 0, 3);
    Stacker_Layers[5].Init(3, 5, 0, 3);
    Stacker_Layers[6].Init(3, 6, 0, 3);
}


////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
void Stacker_ShowScore(Screen_Alt Screen)
{
    //will display a pixel for every 5 points
    int Stacker_DisplayScore = Stacker_FinalScore / 5;
    
    if(millis() - Stacker_Millis_ShowScore_Prev > Stacker_Millis_ShowScore_Interval)
    {
        if(!Stacker_IsWaiting)
        {
            Stacker_Millis_ShowScore_Prev = millis();
            Stacker_Millis_ShowScore_Interval = 500 - (50 * (Stacker_DisplayScore - Stacker_ScoreStppr));
            Stacker_Millis_ShowScore_Interval = Stacker_Millis_ShowScore_Interval > 60 ? Stacker_Millis_ShowScore_Interval : 60;

            int x = (Stacker_ScoreStppr - 1) % 8;
            int y = ((Stacker_ScoreStppr - 1) / 8) % 8;
            Screen.EditPixel(x, y, 1);

            Stacker_ScoreStppr++;
        }

        if(Stacker_ScoreStppr >= Stacker_DisplayScore && !Stacker_IsWaiting)
        {
            //start witing for a short time
            Stacker_IsWaiting = true;
            Stacker_Millis_Wait_Prev = millis();
        }else if(Stacker_IsWaiting && millis() - Stacker_Millis_Wait_Prev > Stacker_Millis_Wait_Interval)
        {
            Stacker_ShowingScore = false;
        }
    }
    
}
////////////////////////////////////////////
//             FUNCTION DEFS              //
//                  END                   //
////////////////////////////////////////////




///////////////////INIT/////////////////////
void Game_Stacker_Init(Screen_Alt Screen)
{
    randomSeed(analogRead(A6));
    for(int i = 0; i < 6; i++)
    {
        firstClick[i] = 1;
    }
    Screen.AllPixelsOff();

    Stacker_GameStart();
}


/////////////////PERIODIC///////////////////
void Game_Stacker_Periodic(Screen_Alt Screen, bool in[6])
{
    if(Stacker_PlayingGame)
    {
        if(millis() - Stacker_Millis_GameTick_Prev > Stacker_Millis_GameTick_Interval)
        {
            Stacker_Millis_GameTick_Prev = millis();
            Screen.AllPixelsOff();

            //GAME CODE HERE


            Stacker_LostGame = false; //Stacker_LostGame = true when game is lost
            Stacker_ShowingScore = Dodge_LostGame;
            Stacker_PlayingGame = !Dodge_LostGame;

            //render (only render if playing game)
            if(Stacker_PlayingGame)
            {
                for(int i = 0; i < sizeof(Stacker_Layers) / sizeof(Stacker_Layers[0]); i++)
                {
                    Stacker_Layers[i].DrawOnScreen(Screen);
                }
            }
        }
    }else if(Stacker_LostGame)
    {
        if(Stacker_ShowingScore)
        {
            Stacker_ShowScore(Screen);
        }
        else
        {
            Stacker_GameStart();
        }
    }
}



//////////////STATE HANDLING////////////////
enum State Game_Stacker_SwitchCheck(Screen_Alt Screen, bool in[6])
{
    State ReturnState = GAME_STACKER;

    if(in[3] && in[1] && in[4])
    {
        ReturnState = MENU;
    }
    return ReturnState;
}
