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

        void DrawOnScreen(Screen_Alt &Screen);

    private:
        int cur_X;  
        int cur_Y;

        int prev_X;
        int prev_Y;

        

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
    cur_X = init_x;
    cur_Y = init_y;

    prev_X = init_x;
    prev_Y = init_y;

    draw_Points[0][0] = 0;
    draw_Points[0][1] = 0;
}


void Dodger::DrawOnScreen(Screen_Alt &Screen)
{
    Screen.EditPixel(prev_X + draw_Points[0][0], prev_Y + draw_Points[0][1], 0);

    Screen.EditPixel(cur_X + draw_Points[0][0], cur_Y + draw_Points[0][1], 1);                     
}
////////////////////////////////////////////
//              DODGER CLASS              //
//                  END                   //
////////////////////////////////////////////





Enemy Enemies[2];
Dodger Dodge_Player;

long long int miliTim_EneMoveD_Prev;
long long int miliTim_EneMoveD_Interval = 500;

void Game_Dodge_Init(Screen_Alt &Screen)
{
    for(int i = 0; i < 6; i++)
    {
        firstClick[i] = 1;
    }
    
    Screen.AllPixelsOff();

    Enemies[0].Init(4, 4);
    Enemies[1].Init(6, 4);

    Dodge_Player.Init(4, 7);

    miliTim_EneMoveD_Prev = millis();
}


void Game_Dodge_Periodic(Screen_Alt &Screen, bool in[6])
{
    if((millis() - miliTim_EneMoveD_Prev) > miliTim_EneMoveD_Interval)
    {
        miliTim_EneMoveD_Prev = millis();
        Enemies[0].Move(0, 1);
    }

    Screen_Alt Enemy_Screen;
    Enemies[0].DrawOnScreen(Enemy_Screen);
    Enemies[1].DrawOnScreen(Enemy_Screen);

    Screen_Alt DodgePlayer_Screen;
    Dodge_Player.DrawOnScreen(DodgePlayer_Screen);
}


enum State Game_Dodge_SwitchCheck(Screen_Alt &Screen, bool in[6])
{
    State ReturnState = GAME_DODGE;

    if(in[3] && in[1] && in[4])
    {
        ReturnState = MENU;
    }
    return ReturnState;
}