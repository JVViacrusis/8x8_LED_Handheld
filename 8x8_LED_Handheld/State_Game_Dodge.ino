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

                            bool IsOutOfBounds();
                            
                        private:
                            int cur_x;
                            int cur_y;

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

                        cur_x = init_x;
                        cur_y = init_y;

                        draw_Points[0][0] = 0;
                        draw_Points[0][1] = 0;

                        draw_Points[1][0] = 1;
                        draw_Points[1][1] = 0;
                    }

                    void Enemy::Move(int x_Move, int y_Move)
                    {
                        cur_x += x_Move;
                        cur_y += y_Move;

                        // if(cur_Y > 7)
                        // {
                        //     cur_Y = init_Y;
                        // }
                    }

                    void Enemy::DrawOnScreen(Screen_Alt Screen)
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
                    };

                    bool Enemy::IsOutOfBounds()
                    {
                        return cur_y >= 8;
                    }
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

    vel_x = 0;
    vel_y = 0;

    draw_Points[0][0] = 0;
    draw_Points[0][1] = 0;
}


void Dodger::DrawOnScreen(Screen_Alt Screen)
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


void Dodger::UpdateVelocities(bool in[6])
{
    //Player Input
    vel_x = 0;
    vel_x -= in[2];
    vel_x += in[3];

    vel_y = 0;
    vel_y -= in[0];
    vel_y += in[1];
}

void Dodger::Move()
{
    cur_x += vel_x;

    //horizontal screen wrap-around
    if(cur_x > 7)
    {
        cur_x = 0;
    }else if(cur_x < 0)
    {
        cur_x = 7;
    }

    if(vel_y < 0 && cur_y == 0) //if going up and at ceiling
    {
        vel_y = 0;  //dont move that way
    }
    if(vel_y > 0 && cur_y == 7) //if going down and at floor 
    {
        vel_y =0; // dont move that way
    }
    cur_y += vel_y;
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
int Dodge_Millis_GameTick_Interval;

Enemy Dodge_Enemies[3];
Dodger Dodge_Player;

long Dodge_Millis_EnemyMove_Prev;
int Dodge_Millis_EnemyMove_Interval;

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
    Dodge_Millis_GameTick_Interval = 50;
    
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

    Dodge_Enemies[0].Init(6, 5);
    Dodge_Enemies[1].Init(2, 1);
    Dodge_Enemies[2].Init(5, -3);

    Dodge_Player.Init(3, 7);

    Dodge_Millis_EnemyMove_Prev = millis();
    Dodge_Millis_EnemyMove_Interval = 200;
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
        if(millis() - Dodge_Millis_EnemyMove_Prev > Dodge_Millis_EnemyMove_Interval)
        {
            Dodge_Millis_EnemyMove_Prev = millis();

            for(int i = 0; i < (sizeof(Dodge_Enemies) / sizeof(Dodge_Enemies[0])); i++)
            {
                Dodge_Enemies[i].Move(0, 1);
            }
        }

        //enemy out of bounds respawn check
        for(int i = 0; i < (sizeof(Dodge_Enemies) / sizeof(Dodge_Enemies[0])); i++)
        {
            if(Dodge_Enemies[i].IsOutOfBounds())  //if out of bounds
            {
                Dodge_Enemies[i].Init(random(7), -4); //respawn enemy at top at random x pos

                Dodge_FinalScore++;

                if(Dodge_FinalScore % 15 == 0)  //every 15 points, speed up enemies by an amount depending on current score
                {
                   if(Dodge_FinalScore <= 60)
                   {
                     Dodge_Millis_EnemyMove_Interval -= 25;
                   }
                   else if(Dodge_FinalScore <= 280)
                   {
                     Dodge_Millis_EnemyMove_Interval -= 5;
                   }else if(Dodge_FinalScore >= 281)
                   {
                     Dodge_Millis_EnemyMove_Interval -= 1;
                   }
                }
                
                Dodge_Millis_EnemyMove_Interval = constrain(Dodge_Millis_EnemyMove_Interval, 0, 9999);
            }
        }
        

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
