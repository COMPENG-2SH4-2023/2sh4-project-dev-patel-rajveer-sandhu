#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

//BOARD SIZE DEFINITION PUT SOMEWHERE


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;

        bool loseFlag;
        int score;
        
        int boardSizeX;
        int boardSizeY;

        //will need an objPos object for the food position

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);

        ~GameMechs();
        
        bool getExitFlagStatus();
        void setExitTrue();

        bool getLoseFlagStatus();
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getScore();
        void incrementScore();

        int getBoardSizeX();
        int getBoardSizeY();
      

      //ADD MORE METHODS WHEN NEEDED LIKE GENERATE FOOD AND 
      //GENERATE FOOD POSITION

};

#endif