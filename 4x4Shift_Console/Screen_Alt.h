#include "Arduino.h"
#include "SPI.h"

#ifndef SCREEN_ALT_H
#define SCREEN_ALT_H
class Screen_Alt
{
  public:
    Screen_Alt();

    void SetDataState(boolean newState);
    void SetClockState(boolean newState);
    void SetLatchState(boolean newState);
    void CycleClatch();

    void ResetScreen();
    void RefreshScreen();

    void EditPixel(int row, int col, int bitVal);
    void EditRow(int row, byte newRow);
    void EditFullScreen(byte newScreen[8]);

    void AllPixelsOn();
    void AllPixelsOff();

    static byte Screen_Bytes[8];


  private:
    const int SHIFT_DATA_PIN = 11;
    const int SHIFT_CLOCK_PIN = 12;
    const int SHIFT_LATCH_PIN = 10;

    const int ROW_PINS[8] = {9, 8, 7, 6, 5, 4, 3, 2};

};
#endif



/*
            B11111111,
            B11111111,
            B11111111,
            B11111111,
            B11111111,
            B11111111,
            B11111111,
            B11111111
*/
