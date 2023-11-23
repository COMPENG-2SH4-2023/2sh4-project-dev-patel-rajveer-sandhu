#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    
}

GameMechs::GameMechs(int boardX, int boardY)
{

}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{

}

char GameMechs::getInput()
{
    if (MacUILib_hasChar() != 0){
        input = MacUILib_getChar();
    }
    return (input);
}

int GameMechs::getBoardSizeX()
{

}

int GameMechs::getBoardSizeY()
{

}


void GameMechs::setExitTrue()
{

}

void GameMechs::setInput(char this_input)
{

}

void GameMechs::clearInput()
{

}


