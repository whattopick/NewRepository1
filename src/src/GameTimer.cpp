#include "GameTimer.h"
#include <windows.h>
#include <stdlib.h>
#include "CursorController.h"

GameTimer::GameTimer(CursorController * cursorController)
{
    //ctor
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
    while(cursorController_->isFree_==false);
    cursorController_->isFree_=false;
    cursorController_->drawAtPlace(3, 2, "Time spent:    mm:  ss");
    cursorController_->drawAtPlace(16, 2, (secs/60)/10);
    cursorController_->drawAtPlace(17, 2, (secs/60)%10);
    cursorController_->drawAtPlace(21, 2, (secs%60)/10);
    cursorController_->drawAtPlace(22, 2, (secs%60)%10);
    cursorController_->isFree_=true;
}
