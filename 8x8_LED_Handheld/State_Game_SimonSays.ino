#include "Screen_Alt.h"
struct Quad
{
  byte image[8];
  boolean isOn;
  long curMillis = 0;
}
topQuad, bottomQuad, leftQuad, rightQuad;
int simon_QuadBlinkLength;


byte allQuads[8];

boolean allQuadsOn;
boolean simon_PlayingGame;
boolean simon_ShowingSequence;
boolean simon_Lose;
boolean simon_PlayingLoseAnimation;
boolean simon_ShowingScore;
boolean simon_NextRound;

String simon_PlyrSqnce;
String simon_RqrdSqnce;

int simon_RqrdSqnceStppr;
long simon_millis_blinkNextInSqncePrev;
int simon_millis_blinkNextInSqnceInterval;

int simon_FinalScore;
int simon_ScoreStppr;
long simon_millis_loseSequencePrev;
int simon_millis_loseSequenceInterval;

boolean simon_isWaiting;
long simon_millis_waitPrev;
int simon_millis_waitInterval = 4000;

boolean simon_canClick = true;


////////////////////////////////////////////
//             FUNCTION DEFS              //
//                 START                  //
////////////////////////////////////////////

void simon_GameStart()
{
  topQuad.isOn = false;
  bottomQuad.isOn = false;
  leftQuad.isOn = false;
  rightQuad.isOn = false;

  allQuadsOn = false;
  simon_PlayingGame = true;
  simon_ShowingSequence = true;
  simon_Lose = false;
  simon_PlayingLoseAnimation = false;
  simon_ShowingScore = false;
  simon_NextRound = false;
  simon_isWaiting = false;

  simon_PlyrSqnce = "5";
  simon_RqrdSqnce = "5"; //5 is the tail

  String simon_SqnceAddition = String(int(random(1, 5)));
  simon_RqrdSqnce += simon_SqnceAddition;

//   simon_SqnceAddition = String(int(random(1, 5)));
//   simon_RqrdSqnce += simon_SqnceAddition;

//   simon_SqnceAddition = String(int(random(1, 5)));
//   simon_RqrdSqnce += simon_SqnceAddition;

//   simon_SqnceAddition = String(int(random(1, 5)));
//   simon_RqrdSqnce += simon_SqnceAddition;

//   simon_SqnceAddition = String(int(random(1, 5)));
//   simon_RqrdSqnce += simon_SqnceAddition;

//   Serial.print("Req: ");
//   Serial.println(simon_RqrdSqnce);

  simon_RqrdSqnceStppr = 0;
  simon_ScoreStppr = 0;

  simon_FinalScore = 0;

  memset(allQuads, B00000000, sizeof(allQuads));

  simon_millis_blinkNextInSqncePrev = millis();
  simon_millis_loseSequenceInterval = 0;
}


/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////


void simon_CheckPlayerInput(bool in[6])
{
    //up
        if (in[0] && firstClick[0]) //if click left first time
        {
            firstClick[0] = false;

            String simon_PlyrSqnceAddition = "1";                           //adds TOP to the player's input sequence
            simon_PlyrSqnce += simon_PlyrSqnceAddition;    //

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
            simon_PlyrSqnce += simon_PlyrSqnceAddition;    //

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
            simon_PlyrSqnce += simon_PlyrSqnceAddition;    //

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
            simon_PlyrSqnce += simon_PlyrSqnceAddition;    //

            simon_CompareSequeneces();

            rightQuad.curMillis = millis(); //blink right for set duration

        }else if (!in[3] && !firstClick[3]) //first click reset
        {
            firstClick[3] = true;
        }
}


/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////


void simon_ShowSequence()
{
    if (millis() - simon_millis_blinkNextInSqncePrev > simon_millis_blinkNextInSqnceInterval)
    {
        simon_millis_blinkNextInSqncePrev = millis();
        switch (int(simon_RqrdSqnce.charAt(simon_RqrdSqnce.length() - simon_RqrdSqnceStppr - 1)) - 48) // -48 => convert ascii number value to int number value
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
                simon_RqrdSqnceStppr = 0;
            break;
        }
    }
}


/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////


void simon_UpdateBlinkStatus()
{
    simon_canClick = true;
    //top 
    if(millis() - topQuad.curMillis < simon_QuadBlinkLength)
    {
        topQuad.isOn = true;
        simon_canClick = false;
    }else
    {
        topQuad.isOn = false;   
    }

    //bottom
    if(millis() - bottomQuad.curMillis < simon_QuadBlinkLength)
    {
        bottomQuad.isOn = true;
        simon_canClick = false;
    }else
    {
        bottomQuad.isOn = false;
    }

    //left
    if(millis() - leftQuad.curMillis < simon_QuadBlinkLength)
    {
        leftQuad.isOn = true;
        simon_canClick = false;
    }else
    {
        leftQuad.isOn = false;
    }

    //right
    if(millis() - rightQuad.curMillis < simon_QuadBlinkLength)
    {
        rightQuad.isOn = true;
        simon_canClick = false;
    }else
    {
        rightQuad.isOn = false;
    }
}

/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////


void simon_DisplayBlinks(Screen_Alt Screen)
{
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
}


/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////


void simon_CompareSequeneces()
{

    //if sequences are matching so far
        //if they are also of the same length, go on to the next round
        //else if they are not yet the same length, keep matching

    //else if they arent matching, you lose

    char nextRqrdChar = simon_RqrdSqnce.charAt(simon_RqrdSqnce.length() - simon_PlyrSqnce.length() + 1);
    char latestPlyrChar = simon_PlyrSqnce.charAt(simon_PlyrSqnce.length() - 1);

    boolean sameChars = nextRqrdChar == latestPlyrChar;
    boolean sameLength = simon_RqrdSqnce.length() == simon_PlyrSqnce.length();

    // Serial.print("R: ");
    // Serial.println(nextRqrdChar);
    // Serial.print("P: ");
    // Serial.println(latestPlyrChar);
    // Serial.print("SC?: ");
    // Serial.println(sameChars);
    // Serial.print("SL?: ");
    // Serial.println(sameLength);
    // Serial.println("");
    // Serial.println("");


    if(!sameChars)
    {
        simon_PlayingGame = false;
        simon_Lose = true;
        simon_PlayingLoseAnimation = true;
        simon_FinalScore = simon_RqrdSqnce.length() - 1;
        if(simon_FinalScore < 2) // if the player doesnt score anything, show a pixel anyway or else they might think the game broke.
        {
            simon_FinalScore = 2;
        }
        // Serial.println(nextRqrdChar);

        //for lose animation
        simon_RqrdSqnce = "5";
        for(int i = 0; i < simon_QuadBlinkLength % 100; i++)
        {
            simon_RqrdSqnce += String(nextRqrdChar);
        }
        // Serial.println(simon_RqrdSqnce);
        simon_RqrdSqnceStppr = 0;
        simon_millis_blinkNextInSqncePrev = millis();
        simon_ShowingSequence = true;

    }else if(sameChars)
    {
        if(sameLength)
        {
            simon_NextRound = true;
        }else if(!sameLength)
        {
            //just let it keep going
        }
    }
}


/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////


void simon_PlayLoseAnimation()
{
    if (millis() - simon_millis_blinkNextInSqncePrev > simon_millis_blinkNextInSqnceInterval)
    {
        simon_millis_blinkNextInSqncePrev = millis();
        switch (int(simon_RqrdSqnce.charAt(simon_RqrdSqnce.length() - simon_RqrdSqnceStppr - 1)) - 48) // -48 => convert ascii number value to int number value
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
                simon_RqrdSqnceStppr = 0;
            break;
        }
    }


    //WHEN DONE
    if(!simon_ShowingSequence)
    {
        simon_PlayingLoseAnimation = false;
        simon_ShowingScore = true;
    }
}


/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////


void simon_ShowScore(Screen_Alt Screen)
{
    //if interval
        //reset interval
        //update interval time to correspond with score. (interval = 1000 - 100 * score with minimum of 100)
        //turn_pixel_on(scoreStppr);
        //ScoreStppr++;
        //if scoreStppr > finalScore
            //simon_ShowingScore = false;

    if(millis() - simon_millis_loseSequencePrev > simon_millis_loseSequenceInterval)
    {
        if(!simon_isWaiting)
        {
            simon_millis_loseSequencePrev = millis();
            simon_millis_loseSequenceInterval = 500 - (50 * (simon_FinalScore - simon_ScoreStppr));
            simon_millis_loseSequenceInterval = simon_millis_loseSequenceInterval > 60 ? simon_millis_loseSequenceInterval : 60;

            int x = (simon_ScoreStppr - 1) % 8;
            int y = (simon_ScoreStppr - 1) / 8;
            Screen.EditPixel(x, y, 1);

            simon_ScoreStppr++;
        }

        if(simon_ScoreStppr == simon_FinalScore && !simon_isWaiting)
        {
            //start witing for a short time
            simon_isWaiting = true;
            simon_millis_waitPrev = millis();
        }else if(simon_isWaiting && millis() - simon_millis_waitPrev > simon_millis_waitInterval)
        {
            simon_ShowingScore = false;
        }
    }



    //WHEN DONE
    // simon_ShowingScore = false;
}
////////////////////////////////////////////
//             FUNCTION DEFS              //
//                  END                   //
////////////////////////////////////////////





void Game_SimonSays_Init(Screen_Alt Screen, bool in[6])
{
  randomSeed(analogRead(A6));
  
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

  //Speed Mods (final digits represent how many times the correct sequence-step is blinked when you lose)
  if(in[0] && in[4]) //Ultra Turbo (UP, A)
  {
    simon_QuadBlinkLength = 108;
    simon_millis_blinkNextInSqnceInterval = 200;
  }else if(in[4]) //Turbo (Just A)
  {
    simon_QuadBlinkLength = 205;
    simon_millis_blinkNextInSqnceInterval = 400;
  }else
  {
    simon_QuadBlinkLength = 403;
    simon_millis_blinkNextInSqnceInterval = 800;
  }
  

    simon_GameStart();

//   Serial.println(simon_RqrdSqnce);
}


void Game_SimonSays_Periodic(Screen_Alt Screen, bool in[6])
{

    if(simon_PlayingGame)
    {
        //animate simon_Sequence
        if(simon_ShowingSequence)
        {
            simon_ShowSequence();
        }


        //click conditions
        if (!simon_ShowingSequence && simon_canClick) // only set to false while AI is showing sequence
        {
            simon_CheckPlayerInput(in);
        }

        if(simon_NextRound)
        {
            simon_NextRound = false;

            simon_PlyrSqnce = "5";

            //Ugly Code Incoming. Previously laid foundation forces me to either do this or rewrite most of the structure of this game. Maybe in the future.
            char simon_SqnceAddition = char(int(random(1, 5)) + 48); // +48 to convert from ascii value to ascii char
            simon_RqrdSqnce.setCharAt(0, simon_SqnceAddition);
            simon_RqrdSqnce = "5" + simon_RqrdSqnce;
            // Serial.println(simon_RqrdSqnce);

            simon_ShowingSequence = true;
            simon_millis_blinkNextInSqncePrev = millis();
        }

        //check if told to blink and display those updated statuses
        simon_UpdateBlinkStatus();
        simon_DisplayBlinks(Screen);

    }else if(simon_Lose)
    {
        if(simon_PlayingLoseAnimation)
        {
            simon_PlayLoseAnimation();

            //check if told to blink and display those updated statuses
            simon_UpdateBlinkStatus();
            simon_DisplayBlinks(Screen);
        }else if(simon_ShowingScore)
        {
            simon_ShowScore(Screen);
        }
        else
        {
            simon_GameStart();
        }
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


//    simon_RqrdSqnce = "e";
//    String simon_SqnceAddition = String(int(random(1, 5)));
//    simon_RqrdSqnce += simon_SqnceAddition;
//    Serial.println(simon_RqrdSqnce);
