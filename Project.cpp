#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *gamemech; //= new GameMechs(); 
Player *player1; // = new Player(gamemech);
objPos playerpos; 


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
    gamemech = new GameMechs(26, 13);
    player1 = new Player(gamemech);

}

void GetInput(void)
{
    //NO NEED FOR THIS AS UPDATE PLAYER DIRECTION CHECKS THIS
    /*
   if (MacUILib_hasChar()){
    gamemech->getInput();
   }
   */
}

void RunLogic(void)
{
    player1->updatePlayerDir();
    player1->movePlayer();
    
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

    //iteration 1B
    objPos tempPos;
    player1->getPlayerPos(tempPos);

    for(int i = 0; i < gamemech->getBoardSizeY(); i++)
    {
        for(int j = 0; j < gamemech->getBoardSizeX(); j++)
        {
            if(j == tempPos.x && i == tempPos.y)
            {
                MacUILib_printf("%c", tempPos.symbol);
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
        MacUILib_printf("\n");
    }   

    
    //BELOW IS FOR DEBUGGING OF GAMEMECH DATA MEMBERS
    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", 
                                gamemech->getBoardSizeX(), 
                                gamemech->getBoardSizeY(),
                                tempPos.x, tempPos.y, tempPos.symbol);


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
    delete gamemech;
}
