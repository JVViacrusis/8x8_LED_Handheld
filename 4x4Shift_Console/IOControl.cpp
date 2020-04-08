#include "Arduino.h"
#include "IOControl.h"




IOControl::IOControl()
{
    pinMode(IO_BUTTON_UP_PIN, INPUT);
    pinMode(IO_BUTTON_DOWN_PIN, INPUT);
    pinMode(IO_BUTTON_LEFT_PIN, INPUT);
    pinMode(IO_BUTTON_RIGHT_PIN, INPUT);
    pinMode(IO_BUTTON_A_PIN, INPUT);
    pinMode(IO_BUTTON_B_PIN, INPUT);
}


void IOControl::GetButtonStates(bool inputs_[6])
{
    inputs_[0] = digitalRead(IO_BUTTON_UP_PIN);
    inputs_[1] = digitalRead(IO_BUTTON_DOWN_PIN);
    inputs_[2] = digitalRead(IO_BUTTON_LEFT_PIN);
    inputs_[3] = digitalRead(IO_BUTTON_RIGHT_PIN);
    inputs_[4] = digitalRead(IO_BUTTON_A_PIN);
    inputs_[5] = digitalRead(IO_BUTTON_B_PIN);
}

void IOControl::DebugButtonStates()
{
//    Serial.print("UP: ");
//    Serial.println(digitalRead(IO_BUTTON_UP_PIN));
//    
//    Serial.print("DOWN: ");
//    Serial.println(digitalRead(IO_BUTTON_DOWN_PIN));
//    
//    Serial.print("LEFT: ");
//    Serial.println(digitalRead(IO_BUTTON_LEFT_PIN));
//    
//    Serial.print("RIGHT: ");
//    Serial.println(digitalRead(IO_BUTTON_RIGHT_PIN));
//    
//    Serial.print("A: ");
//    Serial.println(digitalRead(IO_BUTTON_A_PIN));
//    
//    Serial.print("B: ");
//    Serial.println(digitalRead(IO_BUTTON_B_PIN));
}
