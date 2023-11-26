#include "Food.h"


Food::Food(GameMechs* thisGMRef)
{
    foodPos.setObjPos(-1, -1, 'O');

    mainGameMechsRef = thisGMRef;

    //seed the RNG when Food object initialized
    srand(time(NULL));
}

Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{
    //generate random x and y coordinate and make sure 
    //not border position or player (blockOff) position 
    //use objPos.isEqual() to check blockoff
    bool foodGeneratedFlag = false;
    int candidateX = 0, candidateY = 0, xRange, yRange;

    xRange = mainGameMechsRef->getBoardSizeX() - 1;
    yRange = mainGameMechsRef->getBoardSizeY() - 1;

    //continue coordinate generation if the food is on border or 
    //same position as player object
    while(!foodGeneratedFlag)
    {
        while(candidateX == 0)
            candidateX = rand() % xRange;

        while(candidateY == 0)
            candidateY = rand() % yRange;

        foodPos.setObjPos(candidateX, candidateY, 'O');

        if(foodPos.isPosEqual(&blockOff) == false)
            foodGeneratedFlag = true;
    }

}

void Food::getFoodPos(objPos &returnPos)
{
    //set all private members of returnPos to be equal to foodPos
    returnPos.setObjPos(foodPos);
}