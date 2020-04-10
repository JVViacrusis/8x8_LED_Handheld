//DONT NEED THIS BUT IT STOPS ERRORS
#include "Screen_Alt.h"

////////////////////////////////////////////
//            RAINDROP CLASS              //
//                 START                  //
////////////////////////////////////////////

        class Raindrop
        {
            public:
                Raindrop();

                void Init(int init_x, int init_y);

                void Fall();

                void DrawOnScreen(Screen_Alt Screen);

            private:
                signed int cur_x;
                signed int cur_y;

                signed int prev_x;
                signed int prev_y;

                //  draw_Points[point #][point_x, point_y]
                //  relative to home position (x, y)
                signed int draw_Points[2][2];


        };


        Raindrop::Raindrop(){}

        void Raindrop::Init(signed int init_x, signed int init_y)
        {
            cur_x = init_x;
            cur_y = init_y;

            prev_x = init_x;
            prev_y = init_y;

            draw_Points[0][0] = 0;
            draw_Points[0][1] = 0;

            // draw_Points[1][0] = 0;
            // draw_Points[1][1] = -1;

            // draw_Points[2][0] = 0;
            // draw_Points[2][1] = -2;
        }


        void Raindrop::Fall()
        {
            prev_y = cur_y;
            prev_x = cur_x;

            cur_y += 1;

            if(cur_y == 10)
            {
                cur_y = random(-8, 0);
                // cur_x = random(0, 7);
                // cur_x = random(0, 14);
            }            
        }

        
        void Raindrop::DrawOnScreen(Screen_Alt Screen)
        {
            //erase the previous location of each pixel if it's within the screen
            for (int i = 0; i < sizeof(draw_Points) / sizeof(draw_Points[0]); i++)
            {
                //If within the bounds of the screen
                if(prev_x + draw_Points[i][0] >= 0 && prev_x + draw_Points[i][0] <= 7 && prev_y + draw_Points[i][1] >= 0 && prev_y + draw_Points[i][1] <= 7)    
                {
                    Screen.EditPixel(prev_x + draw_Points[i][0], prev_y + draw_Points[i][1], 0);
                }
            }

            //draw the current/new location of each pixel if it's within the screen
            for(int i = 0; i < sizeof(draw_Points) / sizeof(draw_Points[0]); i++)
            {
                //If within the bounds of the screen
                if(cur_x + draw_Points[i][0] >= 0 && cur_x + draw_Points[i][0] <= 7 && cur_y + draw_Points[i][1] >= 0 && cur_y + draw_Points[i][1] <= 7)
                {
                    Screen.EditPixel(cur_x + draw_Points[i][0], cur_y + draw_Points[i][1], 1);
                }    
            }
        };

////////////////////////////////////////////
//            RAINDROP CLASS              //
//                  END                   //
////////////////////////////////////////////










Raindrop raindrops[8];

long long int miliTim_Fall_Prev;
long long int miliTim_Fall_Interval = 20;


void Animation_Rain_Init(Screen_Alt Screen)
{
    

    randomSeed(analogRead(13));

    for (int i = 0; i < 6; i++)
    {
        firstClick[i] = 1;
    }

    Screen.AllPixelsOff();

    raindrops[0].Init(0, 0);
    raindrops[1].Init(1, 0);
    raindrops[2].Init(2, 0);
    raindrops[3].Init(3, 0);
    raindrops[4].Init(4, 0);
    raindrops[5].Init(5, 0);
    raindrops[6].Init(6, 0);
    raindrops[7].Init(7, 0);
    
    for(int i=0; i<2; i++)
    {
        raindrops[i].DrawOnScreen(Screen);
    }  

    miliTim_Fall_Prev = millis();
}

void Animation_Rain_Periodic(Screen_Alt Screen, bool in[6])
{
    if((millis() - miliTim_Fall_Prev) > miliTim_Fall_Interval)
    {
        miliTim_Fall_Prev = millis();
        for (int i=0; i<sizeof(raindrops)/sizeof(raindrops[0]); i++)
        {
            raindrops[i].Fall();
            raindrops[i].DrawOnScreen(Screen);
        }    
    }
}


enum State Animation_Rain_SwitchCheck(Screen_Alt Screen, bool in[6])
{
    State ReturnState = ANIMATION_RAIN;

    if(in[3] && in[1] && in[4])
    {
        ReturnState = MENU;
    }

    return ReturnState;
}
