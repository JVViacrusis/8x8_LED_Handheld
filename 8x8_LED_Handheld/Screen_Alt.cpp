#include "Screen_Alt.h"


Screen_Alt::Screen_Alt()
{
    pinMode(SHIFT_DATA_PIN, OUTPUT);
    pinMode(SHIFT_CLOCK_PIN, OUTPUT);
    pinMode(SHIFT_LATCH_PIN, OUTPUT);

    for(int i = 0; i < sizeof(ROW_PINS); i++)
    {
        pinMode(ROW_PINS[i], OUTPUT);
    }
    for(int i = 0; i < sizeof(ROW_PINS); i++)
    {
        digitalWrite(ROW_PINS[i], HIGH);
    }
    ResetScreen();
}

void Screen_Alt::SetDataState(boolean state)
{
    digitalWrite(SHIFT_DATA_PIN, state);
}

void Screen_Alt::SetClockState(boolean state)
{
    digitalWrite(SHIFT_CLOCK_PIN, state);
}

void Screen_Alt::SetLatchState(boolean state)
{
    digitalWrite(SHIFT_LATCH_PIN, state);
}

void Screen_Alt::CycleClatch()
{
    SetClockState(HIGH);
    SetClockState(LOW);
    SetLatchState(HIGH);
    SetLatchState(LOW);
}

void Screen_Alt::ResetScreen()
{
    SetDataState(LOW);
    for(int i = 0; i < 8; i++)
    {
        CycleClatch();
    }
}

void Screen_Alt::RefreshScreen()
{
    for(int i = 0; i < 8; i++)
    {
        SetLatchState(LOW);                                                      //  stops displaying pixels, shifts row data out to pixels, displays pixels.
        shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, MSBFIRST, Screen_Bytes[i]);    //        
        SetLatchState(HIGH);                                                     //
        
        digitalWrite(ROW_PINS[i], LOW);   // Current row is powered
        //change brightness (also change 4x4Shift_Console.MillisTimer_ScreenRefresh_Interval) (Higher Number, Higher Brightness)
            // delayMicroseconds(600); //most bright
            delayMicroseconds(200);
            // delayMicroseconds(10);
//          // delayMicroseconds(1); //least bright
        digitalWrite(ROW_PINS[i], HIGH);  // current row is unpowered
    }
}



void Screen_Alt::EditPixel(int col_x, int row_y, int bitVal)
{
    bitWrite(Screen_Bytes[row_y], 7-col_x, bitVal);
}

void Screen_Alt::EditRow(int row, byte newRow)
{
    Screen_Bytes[row] = newRow;
}

void Screen_Alt::EditFullScreen(byte newScreen[8])
{
    for(int i = 0; i < 8 ; i++)
    {
        Screen_Bytes[i] = newScreen[i];
    }
}



void Screen_Alt::AllPixelsOn()
{
    for(int i = 0; i < 8; i++)
    {
        Screen_Bytes[i] = B11111111;
    }
}

void Screen_Alt::AllPixelsOff()
{
    for(int i = 0; i < 8; i++)
    {
        Screen_Bytes[i] = B00000000;
    }
}



byte Screen_Alt::Screen_Bytes[] = 
{
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
};
