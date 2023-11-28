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

    objPos tempPos(1,1,'o');

    //recommended default board size is 30 x 15
    gamemech = new GameMechs(26, 13);
    player1 = new Player(gamemech);

    foodObj = new Food(gamemech);
    
    //tempPos now holds player position
    player1->getPlayerPos();

    //generateFood() requires player reference, you will
    //need to provide it AFTER player object is instantiated
    foodObj->generateFood(tempPos);   

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
            MacUILib_printf("Lost innit\n");
        }
        else
        {
            MacUILib_printf("GAME EXITED\n");
        }
        
        return;
    }

    //iteration 2B
    objPos foodPos,BodySeg;
    bool body_drawn;
    objPos tempPos(1,1,'o');
    
    objPosArrayList* player1Body = player1->getPlayerPos();

    //copy data members of playerPos into foodPos
    foodPos.setObjPos(tempPos);
    //get position of food
    foodObj->getFoodPos(tempPos);

    for(int i = 0; i < gamemech->getBoardSizeY(); i++)
    {
        for(int j = 0; j < gamemech->getBoardSizeX(); j++)
        {
            body_drawn = false;
            for (int k = 0; k<player1Body->getSize();k++){
                player1Body -> getElement(BodySeg,k);
                if (j == BodySeg.x && i == BodySeg.y){
                    body_drawn = true;
                    MacUILib_printf("%c",BodySeg.symbol);
                    break;
                }
            }
            if (!body_drawn){
                if(j == foodPos.x && i == foodPos.y)
                {
                    MacUILib_printf("%c", foodPos.symbol);
                }
                else if(i == 0 || i == gamemech->getBoardSizeY() - 1 || j == 0 || j == gamemech->getBoardSizeX() - 1)
                {
                    MacUILib_printf("#");
                }
                else
                {
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }   

    
    //BELOW IS FOR DEBUGGING OF GAMEMECH DATA MEMBERS
    MacUILib_printf("BoardSize: %dx%d", 
                                gamemech->getBoardSizeX(), 
                                gamemech->getBoardSizeY());

    MacUILib_printf("Food Position: <%d, %d> + %c\n",
                                foodPos.x, foodPos.y, foodPos.symbol);


    MacUILib_printf("Score: %d .... Lose Flag: %d\n", 
                                gamemech->getScore(), 
                                gamemech->getLoseFlagStatus());

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
