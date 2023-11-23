#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000
GameMechs *gamemech = new GameMechs(); 
Player *player1 = new Player(gamemech);
objPos playerpos; 

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
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

    exitFlag = false;
}

void GetInput(void)
{
   if (MacUILib_hasChar()){
    gamemech->getInput();
   }
}

void RunLogic(void)
{
    player1->updatePlayerDir();
    player1->movePlayer();
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    player1->getPlayerPos(playerpos); 
    for(int i=0; i<=9;i++){
        for(int j=0;j<=19;j++){
            if (i == 0 || i == 9 || j == 0 || j==19){
                MacUILib_printf("#");
            }
            else if (i==playerpos.y && j==playerpos.x){
                MacUILib_printf("@");
            }
            else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }   

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
