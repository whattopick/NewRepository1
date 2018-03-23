#ifndef GAMETIMER_H
#define GAMETIMER_H
#include "CursorController.h"

class UserInterface;

class GameTimer
{
    public:
        GameTimer(CursorController*);
        virtual ~GameTimer();
        void setSeconds(int);
        int getSeconds();

    protected:

    private:
        int seconds_ = 0;
    public:
        void tick();
    private:
        CursorController * cursorController_;
        void drawTime(int);
};

#endif // GAMETIMER_H
