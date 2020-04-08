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

                void DrawOnScreen();

            private:
                int cur_x;
                int cur_y;

                int prev_x;
                int prev_y;

                //  draw_Points[point #][point_x, point_y]
                //  relative to home position (x, y)
                int draw_Points[1][2];


        };


        Raindrop::Raindrop(){}

        void Raindrop::Init(int init_x, int init_y)
        {
            cur_x = init_x;
            cur_y = init_y;

            prev_x = init_x;
            prev_y = init_y;

            draw_Points[0][0] = 0;
            draw_Points[0][1] = 0;
        }


        void Raindrop::Fall()
        {
            prev_y = cur_y;

            cur_y += 1;
        }

        
        void Raindrop::DrawOnScreen(Screen_Alt Screen)
        {

            //erase the previous location's rendering
            Screen.EditPixel(prev_x + draw_Points[0][0], prev_y + draw_Points[0][1], 0);

            //draw the new location's rendering
            Screen.EditPixel(cur_x + draw_Points[0][0], cur_y + draw_Points[0][1], 1);
        }



////////////////////////////////////////////
//            RAINDROP CLASS              //
//                  END                   //
////////////////////////////////////////////










Raindrop raindrops[1];


long long int miliTim_Fall_Prev;
long long int miliTim_Fall_Interval = 500;




void Animation_Rain_Init(Screen_Alt &Screen)
{
    randomSeed(analogRead(13));

    for (int i = 0; i < 6; i++)
    {
        firstClick[i] = 1;
    }

    Screen.AllPixelsOff();

    raindrops[0].Init(4, 0);

    miliTim_Fall_Prev = millis();
}

void Animation_Rain_Periodic(Screen_Alt &Screen, bool in[6])
{
    if((millis() - miliTim_Fall_Prev) > miliTim_Fall_Interval)
    {
        miliTim_Fall_Prev = millis();

        for (int i=0; i<sizeof raindrops/sizeof raindrops[0]; i++)
        {
            raindrops[i].Fall;
        }    
    }

    Screen_Alt raindrops_Screen
    for (int i=0; i<sizeof raindrops/sizeof raindrops[0]; i++)
    {
        raindrops[i].DrawOnScreen(raindrops_Screen);
    }  


}


enum State Animation_Rain_SwitchCheck(Screen_Alt &Screen, bool in[6])
{
    State ReturnState = ANIMATION_RAIN;

    if(in[3] && in[1] && in[4])
    {
        ReturnState = MENU;
    }

    return ReturnState;
}


