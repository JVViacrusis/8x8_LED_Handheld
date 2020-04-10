#include "Screen_Alt.h"



struct Quad
{
  byte image[8];
  boolean isOn;
  long curMillis = 0;
  int blinkLength_1 = 400;

}
topQuad, bottomQuad, leftQuad, rightQuad;

byte allQuads[8];

boolean allQuadsOn;
boolean simon_ShowingSequence;

String simon_PlyrSqnce;
String simon_RqrdSqnce;

int simon_RqrdSqnceStppr;
long simon_millis_blinkNextInSqncePrev;
int simon_millis_blinkNextInSqnceInterval = 800;

void Game_SimonSays_Init(Screen_Alt Screen)
{
  randomSeed(analogRead(13));
  
  for (int i = 0; i < 6; i++)
  {
    firstClick[i] = 1;
  }

  topQuad.image[0] =    {B00011000};
  topQuad.image[1] =    {B00111100};
  topQuad.image[2] =    {B00111100};
  topQuad.image[3] =    {B00000000};
  topQuad.image[4] =    {B00000000};
  topQuad.image[5] =    {B00000000};
  topQuad.image[6] =    {B00000000};
  topQuad.image[7] =    {B00000000};

  bottomQuad.image[0] = {B00000000};
  bottomQuad.image[1] = {B00000000};
  bottomQuad.image[2] = {B00000000};
  bottomQuad.image[3] = {B00000000};
  bottomQuad.image[4] = {B00000000};
  bottomQuad.image[5] = {B00111100};
  bottomQuad.image[6] = {B00111100};
  bottomQuad.image[7] = {B00011000};

  leftQuad.image[0] =   {B00000000};
  leftQuad.image[1] =   {B00000000};
  leftQuad.image[2] =   {B01100000};
  leftQuad.image[3] =   {B11100000};
  leftQuad.image[4] =   {B11100000};
  leftQuad.image[5] =   {B01100000};
  leftQuad.image[6] =   {B00000000};
  leftQuad.image[7] =   {B00000000};

  rightQuad.image[0] =  {B00000000};
  rightQuad.image[1] =  {B00000000};
  rightQuad.image[2] =  {B00000110};
  rightQuad.image[3] =  {B00000111};
  rightQuad.image[4] =  {B00000111};
  rightQuad.image[5] =  {B00000110};
  rightQuad.image[6] =  {B00000000};
  rightQuad.image[7] =  {B00000000};

  topQuad.isOn = false;
  bottomQuad.isOn = false;
  leftQuad.isOn = false;
  rightQuad.isOn = false;

  allQuadsOn = false;
  simon_ShowingSequence = true;

  simon_PlyrSqnce = "5";
  simon_RqrdSqnce = "5"; //5 is the tail
  String simon_SqnceAddition = String(int(random(1, 5)));
  simon_RqrdSqnce += simon_SqnceAddition;

  simon_SqnceAddition = String(int(random(1, 5)));
  simon_RqrdSqnce += simon_SqnceAddition;

  simon_SqnceAddition = String(int(random(1, 5)));
  simon_RqrdSqnce += simon_SqnceAddition;

  simon_SqnceAddition = String(int(random(1, 5)));
  simon_RqrdSqnce += simon_SqnceAddition;

  simon_SqnceAddition = String(int(random(1, 5)));
  simon_RqrdSqnce += simon_SqnceAddition;

  simon_RqrdSqnceStppr = 0;

  memset(allQuads, B00000000, sizeof(allQuads));

  simon_millis_blinkNextInSqncePrev = millis();

//   Serial.println(simon_RqrdSqnce);
}


void Game_SimonSays_Periodic(Screen_Alt Screen, bool in[6])
{

    //click conditions
    if (!simon_ShowingSequence) // only set to false while AI is showing sequence
    {
        //up
        if (in[0] && firstClick[0]) //if click left first time
        {
            firstClick[0] = false;

            String simon_PlyrSqnceAddition = "1";                           //adds TOP to the player's input sequence
            simon_PlyrSqnce = simon_PlyrSqnceAddition + simon_PlyrSqnce;    //

            simon_CompareSequeneces();
            
            topQuad.curMillis = millis(); //blink top for set duration
        }else if (!in[0] && !firstClick[0]) //first click reset
        {
            firstClick[0] = true;
        }

        //down
        if (in[1] && firstClick[1]) //if click left first time
        {
            firstClick[1] = false;

            String simon_PlyrSqnceAddition = "2";                           //adds BOTTOM to the player's input sequence
            simon_PlyrSqnce = simon_PlyrSqnceAddition + simon_PlyrSqnce;    //

            simon_CompareSequeneces();
            
            bottomQuad.curMillis = millis(); //blink bottom for set duration

        }else if (!in[1] && !firstClick[1]) //first click reset
        {
            firstClick[1] = true;
        }

        //left
        if (in[2] && firstClick[2]) //if click left first time
        {
            firstClick[2] = false;

            String simon_PlyrSqnceAddition = "3";                           //adds LEFT to the player's input sequence
            simon_PlyrSqnce = simon_PlyrSqnceAddition + simon_PlyrSqnce;    //

            simon_CompareSequeneces();

            leftQuad.curMillis = millis(); //blink left for set duration

        }else if (!in[2] && !firstClick[2]) //first click reset
        {
            firstClick[2] = true;
        }

        //right
        if (in[3] && firstClick[3]) //if click left first time
        {
            firstClick[3] = false;            

            String simon_PlyrSqnceAddition = "4";                           //adds RIGHT to the player's input sequence
            simon_PlyrSqnce = simon_PlyrSqnceAddition + simon_PlyrSqnce;    //

            simon_CompareSequeneces();

            rightQuad.curMillis = millis(); //blink right for set duration

        }else if (!in[3] && !firstClick[3]) //first click reset
        {
            firstClick[3] = true;
        }
    }


    //animate simon_Sequence
        if(simon_ShowingSequence)
        {
            if (millis() - simon_millis_blinkNextInSqncePrev > simon_millis_blinkNextInSqnceInterval)
            {
                simon_millis_blinkNextInSqncePrev = millis();
                switch (int(simon_RqrdSqnce.charAt(simon_RqrdSqnce.length() - simon_RqrdSqnceStppr - 1)) - 48) // -48 => convert ascii value to int
                {
                    case 1://top
                        topQuad.curMillis = millis();
                        simon_RqrdSqnceStppr++;
                    break;

                    case 2://bottom
                        bottomQuad.curMillis = millis();
                        simon_RqrdSqnceStppr++;
                    break;

                    case 3://left
                        leftQuad.curMillis = millis();
                        simon_RqrdSqnceStppr++;
                    break;

                    case 4://right
                        rightQuad.curMillis = millis();
                        simon_RqrdSqnceStppr++;
                    break;

                    case 5: //when it reaches the tail, stop displaying and allow user input
                        simon_ShowingSequence = false;
                    break;
                }
            }
        }


  //check if told to blink
    //top
    if(millis() - topQuad.curMillis < topQuad.blinkLength_1)
    {
        topQuad.isOn = true;
    } else
    {
        topQuad.isOn = false;
    }

    //bottom
    if(millis() - bottomQuad.curMillis < bottomQuad.blinkLength_1)
    {
        bottomQuad.isOn = true;
    }else
    {
        bottomQuad.isOn = false;
    }

    //left
    if(millis() - leftQuad.curMillis < leftQuad.blinkLength_1)
    {
        leftQuad.isOn = true;
    }else
    {
        leftQuad.isOn = false;
    }

    //right
    if(millis() - rightQuad.curMillis < rightQuad.blinkLength_1)
    {
        rightQuad.isOn = true;
    }else
    {
        rightQuad.isOn = false;
    }

    //display if told to display
    if (topQuad.isOn || allQuadsOn)
    {
        for (int i = 0; i < 8; i++)
        {
            allQuads[i] |= topQuad.image[i];
        }
    }
    if (bottomQuad.isOn || allQuadsOn)
    {
        for (int i = 0; i < 8; i++)
        {
            allQuads[i] |= bottomQuad.image[i];
        }
    }
    if (leftQuad.isOn || allQuadsOn)
    {
        for (int i = 0; i < 8; i++)
        {
            allQuads[i] |= leftQuad.image[i];
        }
    }
    if (rightQuad.isOn || allQuadsOn)
    {
        for (int i = 0; i < 8; i++)
        {
            allQuads[i] |= rightQuad.image[i];
        }
    }
  Screen.EditFullScreen(allQuads);
  memset(allQuads, B00000000, 8);


if(in[0])
{
    Screen.EditPixel(2, 0, 1);
}else
{
    Screen.EditPixel(2, 0, 0);   
}

if(in[1])
{
    Screen.EditPixel(2, 2, 1);
}else
{
    Screen.EditPixel(2, 2, 0);   
}

if(in[2])
{
    Screen.EditPixel(1, 1, 1);
}else
{
    Screen.EditPixel(1, 1, 0);   
}

if(in[3])
{
    Screen.EditPixel(3, 1, 1);
}else
{
    Screen.EditPixel(3, 1, 0);   
}

if(in[4])
{
    Screen.EditPixel(5, 1, 1);
}else
{
    Screen.EditPixel(5, 1, 0);   
}

if(in[5])
{
    Screen.EditPixel(6, 0, 1);
}else
{
    Screen.EditPixel(6, 0, 0);   
}
}


enum State Game_SimonSays_SwitchCheck(Screen_Alt Screen, bool in[6])
{
  State ReturnState = GAME_SIMONSAYS;

  if (in[3] && in[1] && in[4])
  {
    ReturnState = MENU;
  }
  return ReturnState;
}



void simon_CompareSequeneces()
{
    //check to see if the player's sequence checks out compared to the required sequence
        boolean sqnceIsCorrect = true;
        for(int i = 0; i < simon_PlyrSqnce.length(); i++)
        {
        //   Serial.println(simon_PlyrSqnce.length());
        //   Serial.print("Player: ");
        //   Serial.println(simon_PlyrSqnce.charAt(simon_PlyrSqnce.length() - i));
        //   Serial.print("Required: ");
        //   Serial.println(simon_RqrdSqnce.charAt(simon_RqrdSqnce.length() - i));
            //if the player's sequence does not match the required sequence, 
            if(simon_PlyrSqnce.charAt(simon_PlyrSqnce.length() - i) 
                != 
               simon_RqrdSqnce.charAt(simon_RqrdSqnce.length() - i))
            {   
                sqnceIsCorrect = false;
            }
        }

    //if the player's sequence checks out and it is just as long as the required sequence (player has inputed the perfect sequenece)
        if(sqnceIsCorrect && simon_PlyrSqnce.length() == simon_RqrdSqnce.length())
        {//make the sequence longer and play the animation
            String simon_SqnceAddition = String(int(random(1, 5)));
            simon_RqrdSqnce += simon_SqnceAddition;

            simon_ShowingSequence = true;
            // Serial.println("CORRECT!");
        }else if(!sqnceIsCorrect)
        {
            // Serial.println("WRONG YOU LOSE");
        }
}


//    simon_RqrdSqnce = "e";
//    String simon_SqnceAddition = String(int(random(1, 5)));
//    simon_RqrdSqnce += simon_SqnceAddition;
//    Serial.println(simon_RqrdSqnce);
