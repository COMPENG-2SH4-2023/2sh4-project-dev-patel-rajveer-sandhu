#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
    private:
        objPos foodPos;

        //need for accessing border size
        GameMechs* mainGameMechsRef;

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOff); //need to upgrade this somehow...
        //need to accept the player body array list
        //go through each array list element to make sure they are all
        //blocked off from random food generation

        void getFoodPos(objPos &returnPos);
};

#endif