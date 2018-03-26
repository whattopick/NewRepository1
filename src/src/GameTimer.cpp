#include "GameTimer.h"
#include <windows.h>
#include <stdlib.h>
#include "CursorController.h"
#include <thread>
//#include "Field.h"

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
        Sleep(1000);
        setSeconds(getSeconds()+1);
    }
}

int GameTimer::seconds_=0;
