/*
    wack-a-mole (reaction game)
    tetris
    dodging game
    snake
    rock paper scissors somehow
*/


#include "Screen_Alt.h"
#include "IOControl.h"

enum State
{
    MENU,
    GAME_DODGE,
    GAME_DOODLEJUMP,
    GAME_SIMONSAYS,
    ANIMATION_RAIN
};

Screen_Alt m_Screen;
IOControl m_IOControl;

State Current_State = MENU;
State Previous_State = Current_State;

bool First_Cycle = true;


int MillisTimer_ScreenRefresh_Previous = 0;
//chang brightness (also change Screen_Alt.cpp__Screen_Alt::RefreshSreen__delayMicroseconds)
  int MillisTimer_ScreenRefresh_Interval = 5;  // most bright 
//  int MillisTimer_ScreenRefresh_Interval = 12;
//  int MillisTimer_ScreenRefresh_Interval = 20; // least bright 

bool      input[6] = {0, 0, 0, 0, 0, 0};
bool firstClick[6] = {1, 1, 1, 1, 1, 1};


void setup()
{
  Serial.begin(9600);
}

void loop()
{
//    m_IOControl.DebugButtonStates();

    switch(Current_State)
    {
        case MENU:
            if(First_Cycle)
            {
                First_Cycle = false;
                Menu_Init(m_Screen);
            }
            
            if(!First_Cycle)
            {
                m_IOControl.GetButtonStates(input);
                Menu_Periodic(m_Screen, input);
            }

            m_IOControl.GetButtonStates(input);
            Current_State = Menu_SwitchCheck(m_Screen, input);
            if(Current_State != Previous_State) //State Has Changed
            {
                Previous_State = Current_State;
                First_Cycle = true;
            }
        break;

        case GAME_DODGE:
            if(First_Cycle)
            {
                First_Cycle = false;
                Game_Dodge_Init(m_Screen);
            }
            
            if(!First_Cycle)
            {
                m_IOControl.GetButtonStates(input);
                Game_Dodge_Periodic(m_Screen, input);
            }

            m_IOControl.GetButtonStates(input);
            Current_State = Game_Dodge_SwitchCheck(m_Screen, input);
            if(Current_State != Previous_State) //State has changed
            {
                Previous_State = Current_State;
                First_Cycle = true;
            }
        break;

        case GAME_DOODLEJUMP:
            if(First_Cycle)
            {
                First_Cycle = false;
                Game_DoodleJump_Init(m_Screen);
            }
                
            if(!First_Cycle)
            {
                m_IOControl.GetButtonStates(input);
                Game_DoodleJump_Periodic(m_Screen, input);
            }

            m_IOControl.GetButtonStates(input);
            Current_State = Game_DoodleJump_SwitchCheck(m_Screen, input);
            if(Current_State != Previous_State) //State has changed
            {
                Previous_State = Current_State;
                First_Cycle = true;
            }
        break;


        case GAME_SIMONSAYS:
          if(First_Cycle)
            {
                First_Cycle = false;
                Game_SimonSays_Init(m_Screen);
            }
                
            if(!First_Cycle)
            {
                m_IOControl.GetButtonStates(input);
                Game_SimonSays_Periodic(m_Screen, input);
            }

            m_IOControl.GetButtonStates(input);
            Current_State = Game_SimonSays_SwitchCheck(m_Screen, input);
            if(Current_State != Previous_State) //State has changed
            {
                Previous_State = Current_State;
                First_Cycle = true;
            }
        break;

        case ANIMATION_RAIN:
            if(First_Cycle)
            {
                First_Cycle = false;
                Animation_Rain_Init(m_Screen);
            }
            
            if(!First_Cycle)
            {
                m_IOControl.GetButtonStates(input);
                Animation_Rain_Periodic(m_Screen, input);
            }

            m_IOControl.GetButtonStates(input);
            Current_State = Animation_Rain_SwitchCheck(m_Screen, input);
            if(Current_State != Previous_State) //State has changed
            {
                Previous_State = Current_State;
                First_Cycle = true;
            }
        break;



    }




    

//    m_Screen.AllPixelsOn();
//    if(tempCounter <= 50000)
//    {
//      byte newScreen[8] = 
//      {
//          B11111111,
//          B11111111,
//          B00011000,
//          B00011000,
//          B11011000,
//          B11011000,
//          B11011000,
//          B11111000,
//      };
//      m_Screen.EditFullScreen(newScreen);
//    }
//    else
//    {
//      byte newScreen[8] = 
//      {
//          B10000001,
//          B11000011,
//          B11000011,
//          B01100110,
//          B01100110,
//          B01100110,
//          B00111100,
//          B00011000,
//          
//      };
//      m_Screen.EditFullScreen(newScreen);  
//    }
    
    if((millis() - MillisTimer_ScreenRefresh_Previous) > MillisTimer_ScreenRefresh_Interval)
    {
      MillisTimer_ScreenRefresh_Previous = millis();
      m_Screen.RefreshScreen();
    }   
}
