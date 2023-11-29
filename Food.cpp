#include "Food.h"


Food::Food(GameMechs* thisGMRef)
{
    foodPos.setObjPos(-1, -1, 'O');

    mainGameMechsRef = thisGMRef;

    objPos startPos;
    foodBucket = new objPosArrayList();
    for(int i = 0; i < BUCKET_ITEMS; i++)
    {
        startPos.setObjPos(i, i,'O');
        foodBucket->insertHead(startPos);
    }

    //seed the RNG when Food object initialized
    srand(time(NULL));
}

Food::~Food()
{
    delete foodBucket;
}

objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
    // return the reference to the playerPos arrray list
}

void Food::generateFood(objPosArrayList &blockOff)
{
    //generate random x and y coordinate and make sure 
    //not border position or player (blockOff) position 
    //use objPos.isEqual() to check blockoff
    objPos bodySeg, foodObj[BUCKET_ITEMS];
    bool foodGeneratedFlag = false;
    char symbol = 'O';
    int candidateX = 0, candidateY = 0, xRange, yRange;

    xRange = mainGameMechsRef->getBoardSizeX() - 1;
    yRange = mainGameMechsRef->getBoardSizeY() - 1;


    //continue coordinate generation if the food is on border or 
    //same position as player object


    for(int items = 0; items < BUCKET_ITEMS; items++)
    {
        candidateX = 0;
        candidateY = 0;
        foodGeneratedFlag = false;

        if(items == BUCKET_ITEMS - 1)
            symbol = '?';

        while(!foodGeneratedFlag)
        {
        
            foodGeneratedFlag = true;
            
            while(candidateX == 0)
            {
                candidateX = rand() % xRange;
            }

            while(candidateY == 0)
            {
                candidateY = rand() % yRange;
            }

            foodObj[items].setObjPos(candidateX, candidateY, symbol);
            
            for(int k = 0; k < items; k++)
            {
                foodBucket->getElement(foodObj[k], k);
                if(foodObj[items].isPosEqual(foodObj+k))
                {
                    foodGeneratedFlag = false;
                    candidateX = 0;
                    candidateY = 0;
                    break;
                }
            }

            if(foodGeneratedFlag)
            {
                for(int i = 0; i < blockOff.getSize(); i++)
                {
                    blockOff.getElement(bodySeg, i);
                    if(foodObj[items].isPosEqual(&bodySeg))
                    {
                    foodGeneratedFlag = false;
                    candidateX = 0;
                    break;
                    } 
                }
            }
            
        }
        foodBucket->removeTail();
        foodBucket->insertHead(foodObj[items]);

    }

}

void Food::getFoodPos(objPos &returnPos)
{
    //set all private members of returnPos to be equal to foodPos
    returnPos.setObjPos(foodPos);
}