#include "Screen_Alt.h"


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
                //PUT RENDER CODE EHRE
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
