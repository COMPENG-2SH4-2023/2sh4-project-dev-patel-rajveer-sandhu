#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList();
    objPos startPos;
    startPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2,'*');
    // playerPosList->insertHead(startPos);
    // playerPosList->insertHead(startPos);
    // playerPosList->insertHead(startPos);
    // playerPosList->insertHead(startPos);
    // playerPosList->insertHead(startPos);

    // more actions to be included
}

Player::~Player()
{
    delete playerPosList;
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    char input;
    input = mainGameMechsRef->getInput();

    if(input == ' ')
    {
        mainGameMechsRef->setExitTrue();
    }

    // PPA3 input processing logic 
    else if (input != 0){
        //if input is capital letter, set to lowercase
        if(input >= 'A' && input <= 'Z')
        {
            input += 32;
        }

        switch(myDir){
            case STOP:
                if (input == 'w'){
                    myDir = UP;
                }
                else if (input == 'a'){
                    myDir = LEFT;
                }
                else if (input == 's'){
                    myDir = DOWN;
                }
                else if (input == 'd'){
                    myDir = RIGHT;
                }
                break;
            case LEFT:
                if (input == 'w'){
                    myDir = UP;
                }
                else if (input == 's'){
                    myDir = DOWN;
                }
                break;

            case RIGHT:
                if (input == 'w'){
                    myDir = UP;
                }
                else if (input == 's'){
                    myDir = DOWN;
                }
                break;

            case UP:
                if (input == 'a'){
                    myDir = LEFT;
                }
                else if (input == 'd'){
                    myDir = RIGHT;
                }
                break;  

            case DOWN:
                if (input == 'a'){
                    myDir = LEFT;
                }
                else if (input == 'd'){
                    myDir = RIGHT;
                }
                break;

            default:
                break;
            }
        }
    input = 0;
    //clear the most recent input (input = NULL)
    mainGameMechsRef->clearInput();
}     

void Player::movePlayer()
{
    objPos currendHeadpos;
    playerPosList->getHeadElement(currendHeadpos);
    // PPA3 Finite State Machine logic
    //BLUD loves HARD Coding lmao
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    if (myDir == UP){
        currendHeadpos.y--;
        if (currendHeadpos.y <= 0){
            currendHeadpos.y = boardY - 2;
        }
    }
    else if (myDir == DOWN){
        currendHeadpos.y++;
        if (currendHeadpos.y >= boardY - 1){
            currendHeadpos.y = 1;
        }
    }
    else if (myDir == LEFT){
        currendHeadpos.x--;
        if (currendHeadpos.x <= 0){
            currendHeadpos.x = boardX - 2;
        }
    }
    else if (myDir == RIGHT){
        currendHeadpos.x++;
        if (currendHeadpos.x >= boardX - 1){
            currendHeadpos.x = 1;
        }
    }
    playerPosList->insertHead(currendHeadpos);
    playerPosList->removeTail();
}
