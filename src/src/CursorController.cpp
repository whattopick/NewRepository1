#include "CursorController.h"
#include <windows.h>
#include <stdio.h>

CursorController::CursorController()
{
    //ctor
    isFree_=true;
}

CursorController::~CursorController()
{
    //dtor
}

void CursorController::drawAtPlace(int x, int y, std::string str)
{
    HANDLE a =GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO b;
    GetConsoleScreenBufferInfo(a, &b);
    b.dwCursorPosition.X = x;
    b.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(a, b.dwCursorPosition);
    printf("%s", str.c_str());
}

void CursorController::drawAtPlace(int x, int y, int c)
{
    HANDLE a =GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO b;
    GetConsoleScreenBufferInfo(a, &b);
    b.dwCursorPosition.X = x;
    b.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(a, b.dwCursorPosition);
    printf("%d", c);
}

void CursorController::hideCursor()
{
    HANDLE a =GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO b;
    GetConsoleCursorInfo(a, &b);
    b.bVisible=false;
    SetConsoleCursorInfo(a, &b);
}
