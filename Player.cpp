#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(10,5,'*');

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
    // PPA3 input processing logic 
    if (mainGameMechsRef->getInput() != 0){
        char input;
        input = mainGameMechsRef->getInput();
        switch(input){
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
            input = 0;
        }
}     

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    if (myDir == UP){
        playerPos.y--;
        if (playerPos.y == 0){
            playerPos.y = 9;
        }
    }
    else if (myDir == DOWN){
        playerPos.y++;
        if (playerPos.y == 10){
            playerPos.y = 1;
        }
    }
    else if (myDir == LEFT){
        playerPos.x--;
        if (playerPos.x == 0){
            playerPos.x = 19;
        }
    }
    else if (myDir == RIGHT){
        playerPos.x++;
        if (playerPos.x == 20){
            playerPos.x = 1;
        }
    }
}
