//DONT NEED THIS BUT IT STOPS ERRORS
#include "Screen_Alt.h"


int Game_Selection_MinNum = 1;
int Game_Selection_MaxNum = 4;

int SelectionCurrent = Game_Selection_MinNum;
bool SelectionConfirmed;

void Menu_Init(Screen_Alt &Screen)
{
    for(int i = 0; i < 6; i++)
    {
        firstClick[i] = true;
    }

    SelectionCurrent = Game_Selection_MinNum; // -1 because when exiting the game, you are holding the right button which causes the menu to go one to the right
    SelectionConfirmed = false;
}


void Menu_Periodic(Screen_Alt &Screen, bool in[6])
{
    SelectionConfirmed = false;
    //Selection Changing
    if(in[2] && firstClick[2]) //if click left first time, selection left.
    {
        firstClick[2] = false;

        if(SelectionCurrent > Game_Selection_MinNum)
        {
            SelectionCurrent--;
        }
    }
    else if(!in[2] && !firstClick[2]) //first click reset
    {
        firstClick[2] = true;
    }


    if(in[3] && firstClick[3])  //if click right first time, selection right.
    {
        firstClick[3] = false;

        if(SelectionCurrent < Game_Selection_MaxNum)
        {
            SelectionCurrent++;
        }
    }
    else if(!in[3] && !firstClick[3])  //first click reset
    {
        firstClick[3] = true;
    }

    

    if(in[5] && firstClick[5])  //if click B first time, selection confirmed.
    {
        firstClick[5] = false;

        SelectionConfirmed = true;
    }
    else if(!in[5] && !firstClick[5])  //first click reset
    {
        firstClick[5] = true;
    }



    //selection display
    byte displayImage[8];

    if(SelectionCurrent == 1) //Dodge Game
    {
        displayImage[0] = B11100000; 
        displayImage[1] = B00000000;
        displayImage[2] = B00011100;
        displayImage[3] = B00000000;
        displayImage[4] = B11100000;
        displayImage[5] = B00000100;
        displayImage[6] = B11111111;
        displayImage[7] = B10000000;
    }
    else if(SelectionCurrent == 2)  // DoodleJump
    {
        displayImage[0] = B00000011;
        displayImage[1] = B00000000;
        displayImage[2] = B01100000;
        displayImage[3] = B00000000;
        displayImage[4] = B00100110;
        displayImage[5] = B00100000;
        displayImage[6] = B11111111;
        displayImage[7] = B01000000;
    }
    else if(SelectionCurrent == 3)  // Simon Says
    {
        displayImage[0] = B00011000;
        displayImage[1] = B00111100;
        displayImage[2] = B01100110;
        displayImage[3] = B01100110;
        displayImage[4] = B00111100;
        displayImage[5] = B00011000;
        displayImage[6] = B11111111;
        displayImage[7] = B00100000;
    }
    else if(SelectionCurrent == 4) // Rain
    {
        displayImage[0] = B01000100;
        displayImage[1] = B10001001;
        displayImage[2] = B00100001;
        displayImage[3] = B00100000;
        displayImage[4] = B10001000;
        displayImage[5] = B00010001;
        displayImage[6] = B11111111;
        displayImage[7] = B00010000;
    }
    
    Screen.EditFullScreen(displayImage);  
}


enum State Menu_SwitchCheck(Screen_Alt &Screen, bool in[6])
{
    State ReturnState = MENU;   //default repeat current state unless told changed to different state

    if(SelectionConfirmed && in[5])
    {
        ReturnState = (State)SelectionCurrent;
    }
    return ReturnState;
}
