#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false;

    loseFlag = false;

    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;

    loseFlag = false;

    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
//FILL LATER
GameMechs::~GameMechs()
{

}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    //FIGURE OUT WHERE TO USE THE SETTER
    char this_input = 0;

    if (MacUILib_hasChar()){
        this_input = MacUILib_getChar();
    }

    setInput(this_input);
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore()
{
    return score;
}

// void GameMechs::incrementScore(int playerSize)
// {
//     //set score to list length of player - 1
//     score = playerSize - 1;   
// }

void GameMechs::incrementScore(int amount)
{
    score += amount;
}
