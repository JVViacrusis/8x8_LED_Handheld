

class IOControl
{
    public:
        IOControl();

        void GetButtonStates(bool inputs_[6]);

        void DebugButtonStates();


    private:
        const int     IO_BUTTON_UP_PIN = A2;
        const int   IO_BUTTON_DOWN_PIN = A5;
        const int   IO_BUTTON_LEFT_PIN = A4;
        const int  IO_BUTTON_RIGHT_PIN = A3;
        const int      IO_BUTTON_A_PIN = A1;
        const int      IO_BUTTON_B_PIN = A0;
};
