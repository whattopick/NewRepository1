#include <iostream>
#include <stdio.h>
#include "CursorController.h"
#include "UserInterface.h"
#include "GameTimer.h"
#include "Field.h"
#include "AllyTank.h"
#include "EnemyTank.h"
#include "Bullet.h"
#include <thread>
#include <string>
#include "string.h"
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <time.h>

using namespace std;

int main()
{
    //printf("********************************************************** CRAZY TANKS ************************************************\n");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    printf("Input width of field (min 20, max 210): ");
    int width;
    int height;
    scanf("%d", &width);
    printf("Input height of field (min 10, max 60): ");
    scanf("%d", &height);
    CursorController * cursorController = new CursorController();
    cursorController->hideCursor();
    while(cursorController->isFree_==false);
    cursorController->isFree_=false;
    cursorController->drawAtPlace(0, 0, "------------------------------------------------------------- CRAZY TANKS -------------------------------------------------------------------");
    cursorController->drawAtPlace(0, 1, "                                          ");
    cursorController->drawAtPlace(0, 1, "Loading, please wait");
    cursorController->isFree_=true;
//    UserInterface * userInterface = new UserInterface(cursorController);
    Field * field = new Field(width, height, cursorController);
    while(cursorController->isFree_==false);
    cursorController->isFree_=false;
    cursorController->drawAtPlace(0, 1, "                                          ");
    cursorController->isFree_=true;
    //userInterface->drawField(field->getFieldInfo().x, field->getFieldInfo().y, field->getFieldInfo().width, field->getFieldInfo().height, field->level_);
    AllyTank * allyTank = new AllyTank(field, cursorController);
    EnemyTank * enemyTanks[field->getEnemiesCount()];
    srand(time(NULL));
    for (int i=0; i<field->getEnemiesCount(); i++){
    EnemyTank * enemyTank = new EnemyTank(field, rand()%(field->getFieldInfo().width-3)+1,rand()%(field->getFieldInfo().height-3)+1, cursorController, allyTank);
    enemyTanks[i]=enemyTank;
    //Sleep(20);
    }
    //GameTimer * timer = new GameTimer(userInterface);
    GameTimer * timer = new GameTimer(cursorController);
    std::thread t1([timer]{timer->tick();});
    std::thread t2([allyTank]{allyTank->controlTank();});
    //std::thread t3([allyTank]{allyTank->shoot();});
    t1.join();
    delete timer;
   // delete enemyTank;
    delete allyTank;
    delete field;
    //delete userInterface;
    delete cursorController;
    return 0;
}
