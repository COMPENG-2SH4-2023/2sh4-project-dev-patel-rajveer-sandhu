#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;

    myDir = STOP;
    playerPosList = new objPosArrayList();
    objPos startPos;
    startPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2,'*');
    playerPosList->insertHead(startPos);
}

Player::~Player()
{
    delete playerPosList;
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

void Player::updateMovement(objPos &currentHeadPos)
{
    // PPA3 Finite State Machine logic
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    if (myDir == UP){
        currentHeadPos.y--;
        if (currentHeadPos.y <= 0){
            currentHeadPos.y = boardY - 2;
        }
    }
    else if (myDir == DOWN){
        currentHeadPos.y++;
        if (currentHeadPos.y >= boardY - 1){
            currentHeadPos.y = 1;
        }
    }
    else if (myDir == LEFT){
        currentHeadPos.x--;
        if (currentHeadPos.x <= 0){
            currentHeadPos.x = boardX - 2;
        }
    }
    else if (myDir == RIGHT){
        currentHeadPos.x++;
        if (currentHeadPos.x >= boardX - 1){
            currentHeadPos.x = 1;
        }
    }
}

void Player::movePlayer()
{
    //get position of player head
    objPos currentHeadPos;
    objPos bodySeg;

    char symbol;

    playerPosList->getHeadElement(currentHeadPos);
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(bodySeg, i);
        if(currentHeadPos.isPosEqual(&bodySeg)){
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            return;
        }     
    }

    updateMovement(currentHeadPos);

    //check whether the head overlaps with food position
    //might change where insertHead is placeed for bonus...
    playerPosList->insertHead(currentHeadPos);
    if(checkFoodConsumption(currentHeadPos, symbol))
    {
        //mainGameMechsRef->incrementScore(symbol);
        changePlayerLength(currentHeadPos, symbol);
        foodRef->generateFood(*playerPosList);
    }
    else
    {
        playerPosList->removeTail();
    }
}

bool Player::checkFoodConsumption(objPos currentHeadPos, char &symbol)
{
    objPos foodPos;
    objPosArrayList* foodPositions = foodRef->getFoodPos();
    for(int i = 0; i < foodPositions->getSize(); i++)
    {
        foodPositions->getElement(foodPos, i);
        if(foodPos.isPosEqual(&currentHeadPos))
        {
            symbol = foodPos.getSymbolIfPosEqual(&currentHeadPos);
            return true;
        }
    }

    return false;
}

//might not be needed...
void Player::changePlayerLength(objPos currentHeadPos, char symbol)
{
    int chances;
    if(symbol == '?')
    {
        chances = rand() % 3;
        switch(chances)
        {
            case 0:
                //increase size by 3 (2 here and 1 in other loop), keep score the same
                for(int i = 0; i < 2; i++)
                {
                    updateMovement(currentHeadPos);
                    playerPosList->insertHead(currentHeadPos);
                }
                break;
            case 1:
                //increase score by 10, and keep size same
                mainGameMechsRef->incrementScore(10);
                playerPosList->removeTail();
                break;
            case 2:
                //decrease score by 5, keep same size
                mainGameMechsRef->incrementScore(-5);
                playerPosList->removeTail();
                break;
            default:
                mainGameMechsRef->incrementScore(1);
                break;
        }
    }
    else
    {
        mainGameMechsRef->incrementScore(1);
    }
}

// might not be needed...
char  Player::getPlayerDir(){
    switch(myDir){
            case LEFT:
                return('L');
                break;
            case RIGHT:
                return('R');
                break;
            case UP:
                return('U');
                break;
            case DOWN:
                return('D');
                break;
            default:
                return('S');
    }
}
    
