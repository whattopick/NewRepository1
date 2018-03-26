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
        static int seconds_;

    protected:

    private:
    public:
        void tick();
    private:
        CursorController * cursorController_;
};

#endif // GAMETIMER_H
