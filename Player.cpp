#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, 
                                mainGameMechsRef->getBoardSizeY() / 2,'*');

    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x,playerPos.y,playerPos.symbol);
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
    // PPA3 Finite State Machine logic
    //BLUD loves HARD Coding lmao

    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    if (myDir == UP){
        playerPos.y--;
        if (playerPos.y <= 0){
            playerPos.y = boardY - 2;
        }
    }
    else if (myDir == DOWN){
        playerPos.y++;
        if (playerPos.y >= boardY - 1){
            playerPos.y = 1;
        }
    }
    else if (myDir == LEFT){
        playerPos.x--;
        if (playerPos.x <= 0){
            playerPos.x = boardX - 2;
        }
    }
    else if (myDir == RIGHT){
        playerPos.x++;
        if (playerPos.x >= boardX - 1){
            playerPos.x = 1;
        }
    }
}
