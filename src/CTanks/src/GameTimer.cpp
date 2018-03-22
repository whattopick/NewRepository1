#include "GameTimer.h"
#include <windows.h>
#include <stdlib.h>
//#include "UserInterface.h"
#include "CursorController.h"

//GameTimer::GameTimer(UserInterface * userInterface)
GameTimer::GameTimer(CursorController * cursorController)
{
    //ctor
    //userInterface_=userInterface;
    cursorController_=cursorController;
}

GameTimer::~GameTimer()
{
    //dtor
    delete cursorController_;
}

int GameTimer::getSeconds()
{
    return seconds_;
}

void GameTimer::setSeconds(int secs)
{
    seconds_=secs;
}

void GameTimer::tick()
{
    while(true)
    {
        drawTime(getSeconds());
        Sleep(1000);
        setSeconds(getSeconds()+1);
    }

}

void GameTimer::drawTime(int secs)
{
    cursorController_->drawAtPlace(3, 2, "Time spent: ");
    cursorController_->drawAtPlace(16, 2, (secs/60)/10);
    cursorController_->drawAtPlace(17, 2, (secs/60)%10);
    cursorController_->drawAtPlace(18, 2, "mm:");
    cursorController_->drawAtPlace(21, 2, (secs%60)/10);
    cursorController_->drawAtPlace(22, 2, (secs%60)%10);
    cursorController_->drawAtPlace(23, 2, "ss.");
}
