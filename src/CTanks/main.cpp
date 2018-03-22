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

using namespace std;

int main()
{
    //printf("********************************************************** CRAZY TANKS ************************************************\n");
    printf("Input width of field (min 10): ");
    int width;
    int height;
    scanf("%d", &width);
    printf("Input height of field (min 10): ");
    scanf("%d", &height);
    CursorController * cursorController = new CursorController();
    cursorController->drawAtPlace(0, 0, "---------------------------------- CRAZY TANKS ---------------------------------");
    cursorController->drawAtPlace(0, 1, "                                     ");
    cursorController->drawAtPlace(0, 1, "Loading, please wait");
    cursorController->hideCursor();
//    UserInterface * userInterface = new UserInterface(cursorController);
    Field * field = new Field(width, height, cursorController);
    cursorController->drawAtPlace(0, 1, "                                     ");
    //userInterface->drawField(field->getFieldInfo().x, field->getFieldInfo().y, field->getFieldInfo().width, field->getFieldInfo().height, field->level_);
    AllyTank * allyTank = new AllyTank(field, cursorController);
    //GameTimer * timer = new GameTimer(userInterface);
    GameTimer * timer = new GameTimer(cursorController);
    std::thread t1([timer]{timer->tick();});
    std::thread t2([allyTank]{allyTank->controlTank();});
    t1.join();
    delete timer;
    delete allyTank;
    delete field;
    //delete userInterface;
    delete cursorController;
    return 0;
}
