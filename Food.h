#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#define BUCKET_ITEMS 5

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
    private:
        objPos foodPos;
        objPosArrayList *foodBucket;

        /*
        1) intialize foodBucket array list and set to side of screen
        2) generate on game board each position
        3) create collision checker for each
        4) modify the symbols for some (special food)
        5) when checking if collision occurs, check for symbol too
        6) modify score accordigly 
        */

        //need for accessing border size
        GameMechs* mainGameMechsRef;

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        objPosArrayList* getFoodPos();

        void generateFood(objPosArrayList &blockOff); //need to upgrade this somehow...
        //need to accept the player body array list
        //go through each array list element to make sure they are all
        //blocked off from random food generation

        void getFoodPos(objPos &returnPos);
};

#endif