#include <iostream>
#include <stdio.h>
#include "CursorController.h"
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
    Field * field = new Field(width, height, cursorController);
    GameTimer * timer = new GameTimer(cursorController);
    std::thread t1([timer]{timer->tick();});
    AllyTank * allyTank = new AllyTank(field, cursorController);
    EnemyTank * enemyTanks[field->getEnemiesCount()];
    srand(time(NULL));
    for (int i=0; i<field->getEnemiesCount(); i++){
    EnemyTank * enemyTank = new EnemyTank(field, rand()%(field->getFieldInfo().width-5)+1,rand()%(field->getFieldInfo().height-5)+1, cursorController, allyTank);
    enemyTanks[i]=enemyTank;
    }
    for (int i=0; i<field->getEnemiesCount(); i++){
    enemyTanks[i]->startIt();
    }
    std::thread t8([field]{while(true) {Sleep(15); field->testDraw();} });
    std::thread t2([allyTank]{allyTank->controlTank();});
    t8.join();
    t1.join();
    t2.join();
    for (int i=0; i<field->getEnemiesCount(); i++){
    delete enemyTanks[i];
    }
    delete allyTank;
    delete timer;
    delete field;
    delete cursorController;
    return 0;
}
