//DONT NEED THIS BUT IT STOPS ERRORS
#include "Screen_Alt.h"

////////////////////////////////////////////
//              ENEMY CLASS               //
//                 START                  //
////////////////////////////////////////////
                    class Enemy
                    {
                        public:
                            Enemy();

                            void Init(int init_x, int init_y);

                            void Move(int x_Move, int y_Move);

                            void DrawOnScreen(Screen_Alt Screen);

                        private:
                            int cur_X;
                            int cur_Y;

                            int prev_X;
                            int prev_Y;

                            //  draw_Points[point #][point_x, point_y]
                            //  relative to home position (x, y)
                            int draw_Points[2][2];

                            // long long testing[1];

   
                    };

                    Enemy::Enemy(){}

                    void Enemy::Init(int init_x, int init_y)
                    {   
                        // init_X = init_x;
                        // init_Y = init_y;

                        cur_X = init_x;
                        cur_Y = init_y;

                        prev_X = init_x;
                        prev_Y = init_y;

                        draw_Points[0][0] = 0;
                        draw_Points[0][1] = 0;

                        draw_Points[1][0] = 1;
                        draw_Points[1][1] = 0;
                    }

                    void Enemy::Move(int x_Move, int y_Move)
                    {
                        prev_X = cur_X;
                        prev_Y = cur_Y;

                        cur_X += x_Move;
                        cur_Y += y_Move;

                        // if(cur_Y > 7)
                        // {
                        //     cur_Y = init_Y;
                        // }
                    }

                    void Enemy::DrawOnScreen(Screen_Alt Screen)
                    {
                        Screen.EditPixel(prev_X + draw_Points[0][0], prev_Y + draw_Points[0][1], 0);
                        Screen.EditPixel(prev_X + draw_Points[1][0], prev_Y + draw_Points[1][1], 0);

                        Screen.EditPixel(cur_X + draw_Points[0][0], cur_Y + draw_Points[0][1], 1);
                        Screen.EditPixel(cur_X + draw_Points[1][0], cur_Y + draw_Points[1][1], 1);                        
                    };
////////////////////////////////////////////
//              ENEMY CLASS               //
//                  END                   //
////////////////////////////////////////////






////////////////////////////////////////////
//              DODGER CLASS              //
//                 START                  //
////////////////////////////////////////////
class Dodger
{
    public:
        Dodger();
        
        void Init(int init_x, int init_y);

        void DrawOnScreen(Screen_Alt Screen);

        void UpdateVelocities(bool in[6]);
        void Move();

    private:
        int cur_x;  
        int cur_y;

        int prev_x;
        int prev_y;

        int vel_x;
        int vel_y;

        

//        long long test[175];
//        byte testing[8];
//        long long test[200];
        
        
        

        //  draw_Points[point #][point_x, point_y]
        //  relative to home position (x, y)
        int draw_Points[1][2];



};


Dodger::Dodger(){}

void Dodger::Init(int init_x, int init_y)
{
    cur_x = init_x;
    cur_y = init_y;

    prev_x = init_x;
    prev_y = init_y;

    vel_x = 0;
    vel_y = 0;

    draw_Points[0][0] = 0;
    draw_Points[0][1] = 0;
}


void Dodger::DrawOnScreen(Screen_Alt Screen)
{
    Screen.EditPixel(prev_x + draw_Points[0][0], prev_y + draw_Points[0][1], 0);

    Screen.EditPixel(cur_x + draw_Points[0][0], cur_y + draw_Points[0][1], 1);                     
}


void Dodger::UpdateVelocities(bool in[6])
{
    //Player Input
    vel_x = 0;
    vel_x -= in[2];
    vel_x += in[3];
}

void Dodger::Move()
{
    cur_x += vel_x;
}
////////////////////////////////////////////
//              DODGER CLASS              //
//                  END                   //
////////////////////////////////////////////






////////////////////////////////////////////
//             VARIABLE DEFS              //
//                 START                  //
////////////////////////////////////////////

long Dodge_Millis_GameTick_Prev;
int Dodge_Millis_GameTick_Interval = 65;

Enemy Dodge_Enemies[3];
Dodger Dodge_Player;

long Dodge_Millis_ShowScore_Prev;
int Dodge_Millis_ShowScore_Interval;

bool Dodge_PlayingGame;
bool Dodge_LostGame;
bool Dodge_ShowingScore;

int Dodge_FinalScore;
int Dodge_ScoreStppr;

bool Dodge_IsWaiting;
long Dodge_Millis_Wait_Prev;
int Dodge_Millis_Wait_Interval = 4000;

////////////////////////////////////////////
//             VARIABLE DEFS              //
//                 END                    //
////////////////////////////////////////////




////////////////////////////////////////////
//             FUNCTION DEFS              //
//                 START                  //
////////////////////////////////////////////
void Dodge_GameStart()
{
    Dodge_Millis_GameTick_Prev = millis();
    
    Dodge_Millis_ShowScore_Prev = millis();
    Dodge_Millis_ShowScore_Interval = 0;

    Dodge_PlayingGame = true;
    Dodge_LostGame = false;
    Dodge_ShowingScore = false;

    Dodge_FinalScore = 1;
    Dodge_ScoreStppr = 1;

    Dodge_IsWaiting = false;
    Dodge_Millis_Wait_Prev = millis();
    Dodge_Millis_Wait_Interval = 4000;

    Dodge_Enemies[0].Init(0, 0);
    Dodge_Enemies[1].Init(6, 0);
    Dodge_Enemies[2].Init(3, 3);

    Dodge_Player.Init(4, 7);
}

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

void Dodge_ShowScore(Screen_Alt Screen)
{
    //line for debugging remove when you want to display real score
    Dodge_FinalScore = 45;

    if(millis() - Dodge_Millis_ShowScore_Prev > Dodge_Millis_ShowScore_Interval)
    {
        if(!Dodge_IsWaiting)
        {
            Dodge_Millis_ShowScore_Prev = millis();
            Dodge_Millis_ShowScore_Interval = 500 - (50 * (Dodge_FinalScore - Dodge_ScoreStppr));
            Dodge_Millis_ShowScore_Interval = Dodge_Millis_ShowScore_Interval > 60 ? Dodge_Millis_ShowScore_Interval : 60;

            int x = (Dodge_ScoreStppr - 1) % 8;
            int y = ((Dodge_ScoreStppr - 1) / 8) % 8;
            Screen.EditPixel(x, y, 1);

            Dodge_ScoreStppr++;
        }

        if(Dodge_ScoreStppr == Dodge_FinalScore && !Dodge_IsWaiting)
        {
            //start witing for a short time
            Dodge_IsWaiting = true;
            Dodge_Millis_Wait_Prev = millis();
        }else if(Dodge_IsWaiting && millis() - Dodge_Millis_Wait_Prev > Dodge_Millis_Wait_Interval)
        {
            Dodge_ShowingScore = false;
        }
    }
    
}
////////////////////////////////////////////
//             FUNCTION DEFS              //
//                  END                   //
////////////////////////////////////////////


///////////////////INIT/////////////////////
void Game_Dodge_Init(Screen_Alt Screen)
{
    randomSeed(analogRead(A6));
    for(int i = 0; i < 6; i++)
    {
        firstClick[i] = 1;
    }
    Screen.AllPixelsOff();

    Dodge_GameStart();
}


/////////////////PERIODIC///////////////////
void Game_Dodge_Periodic(Screen_Alt Screen, bool in[6])
{
   if(Dodge_PlayingGame)
   {
     if(millis() - Dodge_Millis_GameTick_Prev > Dodge_Millis_GameTick_Interval)
     {
        Dodge_Millis_GameTick_Prev = millis();
        Screen.AllPixelsOff();

        
        //player movement
        Dodge_Player.UpdateVelocities(in);
        Dodge_Player.Move();

        //enemy movement

        //check player<->enemy collisions for game loss conditons
        Dodge_LostGame = false; //Dodge_LostGame = condition when lost;
        Dodge_ShowingScore = Dodge_LostGame;
        Dodge_PlayingGame = !Dodge_LostGame;

        //renders
        for(int i = 0; i < (sizeof(Dodge_Enemies) / sizeof(Dodge_Enemies[0])); i++)
        {
            Dodge_Enemies[i].DrawOnScreen(Screen);
        }
        Dodge_Player.DrawOnScreen(Screen);
     }
   }else if(Dodge_LostGame)
    {
        if(Dodge_ShowingScore)
        {
            Dodge_ShowScore(Screen);
        }
        else
        {
            Dodge_GameStart();
        }
    }
}


//////////////STATE HANDLING////////////////
enum State Game_Dodge_SwitchCheck(Screen_Alt Screen, bool in[6])
{
    State ReturnState = GAME_DODGE;

    if(in[3] && in[1] && in[4])
    {
        ReturnState = MENU;
    }
    return ReturnState;
}
