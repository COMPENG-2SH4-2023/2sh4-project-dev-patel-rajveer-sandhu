#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *gamemech;
Player *player1;
Food *foodObj;



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(gamemech->getExitFlagStatus() == false)  
    {
        //GET INPUT NOT NEEDED ANYMORE I THINK
        //GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();


    //recommended default board size is 30 x 15
    //we are using game board with size 26 by 13, for now at least
    gamemech = new GameMechs(30, 15);

    foodObj = new Food(gamemech);

    
    
    //this is a makeshift setup so I don't have to touch generateItem yet
    //once you upgrade generateFood to accept reference to the arrayList, remove tempPos
    //objPos tempPos(1,1,'o');
    //tempPos now holds player position
    //player1->getPlayerPos();
    player1 = new Player(gamemech, foodObj);
    objPosArrayList* player1Body = player1->getPlayerPos();

    //generateFood() requires player reference, you will
    //need to provide it AFTER player object is instantiated
    foodObj->generateFood(*player1Body);   

    
}

void GetInput(void)
{
    //NO NEED FOR THIS AS UPDATE PLAYER DIRECTION CHECKS THIS
}

void RunLogic(void)
{
    player1->updatePlayerDir();
    player1->movePlayer();
    
    /*
    //debug for generateFood by inputting 'p'
    if(gamemech->getInput() == 'p')
    {
        objPos tempPos;
        player1->getPlayerPos(tempPos);
        foodObj->generateFood(tempPos);
    }
    */
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    if(gamemech->getExitFlagStatus())
    {
        if(gamemech->getLoseFlagStatus())
        {
            MacUILib_printf("The snake ate itself! You Scored: %d.\n", gamemech->getScore());
        }
        else
        {
            MacUILib_printf("Game Ended. You Scored: %d.\n", gamemech->getScore());
        }
        
        return;
    }

    //iteration 2B
    objPos foodPos,BodySeg;
    bool body_drawn, food_drawn;
  //  objPos tempPos(1,1,'o');
    
    objPosArrayList* player1Body = player1->getPlayerPos();
    objPosArrayList* foodPositions = foodObj->getFoodPos();

    //copy data members of playerPos into foodPos
    //foodPos.setObjPos(tempPos);
    //get position of food
    //foodObj->getFoodPos(foodPos);

    for(int i = 0; i < gamemech->getBoardSizeY(); i++)
    {
        for(int j = 0; j < gamemech->getBoardSizeX(); j++)
        {
            body_drawn = false;
            for (int k = 0; k<player1Body->getSize();k++){
                player1Body -> getElement(BodySeg, k);
                if (j == BodySeg.x && i == BodySeg.y){
                    body_drawn = true;
                    MacUILib_printf("%c",BodySeg.symbol);
                    break;
                }
            }
            if (!body_drawn)
            {
                food_drawn = false;
                for(int k = 0; k < foodPositions->getSize(); k++)
                {
                    foodPositions -> getElement(foodPos, k);
                    if (j == foodPos.x && i == foodPos.y)
                    {
                        food_drawn = true;
                        MacUILib_printf("%c",foodPos.symbol);
                        break;
                    }
                }
                if(!food_drawn)
                {
                    if(i == 0 || i == gamemech->getBoardSizeY() - 1 || j == 0 || j == gamemech->getBoardSizeX() - 1)
                    {
                        MacUILib_printf("#");
                    }
                    else
                    {
                        MacUILib_printf(" ");
                    }
                }
                
            }
        }
        MacUILib_printf("\n");
    }   

    
    //BELOW IS FOR DEBUGGING OF GAMEMECH DATA MEMBERS
    player1Body->getHeadElement(BodySeg);
    MacUILib_printf("Score: %d", gamemech->getScore());
    MacUILib_printf("\n======== DEBUG MESSAGE ========");
    MacUILib_printf("\nBoard Size: %dx%d", gamemech->getBoardSizeX(), gamemech->getBoardSizeY());
    MacUILib_printf("\nPlayer Direction: %c", player1->getPlayerDir());
    MacUILib_printf("\nPlayer Postion: %d, %d", BodySeg.x, BodySeg.y);

    // MacUILib_printf("\nFood Position: <%d, %d> + %c\n",
    //                             foodPos.x, foodPos.y, foodPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
  
    MacUILib_uninit();

    delete player1;
    delete foodObj;
    delete gamemech;
}
