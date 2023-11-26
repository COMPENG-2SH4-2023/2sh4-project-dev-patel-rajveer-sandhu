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

        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);
};

#endif