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
    Field * field = new Field(width, height, cursorController);
    while(cursorController->isFree_==false);
    cursorController->isFree_=false;
    cursorController->drawAtPlace(0, 1, "                                          ");
    cursorController->isFree_=true;
    AllyTank * allyTank = new AllyTank(field, cursorController);
    EnemyTank * enemyTanks[field->getEnemiesCount()];
    srand(time(NULL));
    for (int i=0; i<field->getEnemiesCount(); i++){
    EnemyTank * enemyTank = new EnemyTank(field, rand()%(field->getFieldInfo().width-3)+1,rand()%(field->getFieldInfo().height-3)+1, cursorController, allyTank);
    enemyTanks[i]=enemyTank;
    }
    GameTimer * timer = new GameTimer(cursorController);
    std::thread t1([timer]{timer->tick();});
    std::thread t2([allyTank]{allyTank->controlTank();});
    t1.join();
    delete timer;
    delete allyTank;
    delete field;
    delete cursorController;
    return 0;
}
