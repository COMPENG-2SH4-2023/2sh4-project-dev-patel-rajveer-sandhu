#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        ~Player(); 

        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3.
        void updatePlayerDir();
        void movePlayer();
        void updateMovement(objPos &currentHeadPos);
        //Need more actions in here:
        //after inserting the head but before removing the tail
        // - check if new head position collides with food
        // - if yes, increment the score in GM, generate new food, and do NOT remove tail
        // otherwise, remove tail and move on
        bool checkFoodConsumption(objPos currentHeadPos, char &symbol);
        void changePlayerLength(objPos currentHeadPos, char symbol);
        bool checkSelfCollision();

        //Lastly, add self collision checks:
        // -if self-collided
        // set loseFlag and exitFlag both to true (through GM)
        //
        //-if ending, you need to differentiate the end game state

    private:
        objPosArrayList *playerPosList;    
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        //need reference to food object
        Food *foodRef;
};

#endif