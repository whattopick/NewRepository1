#ifndef GAMETIMER_H
#define GAMETIMER_H
//#include "UserInterface.h"
#include "CursorController.h"

class UserInterface;

class GameTimer
{
    public:
        //GameTimer(UserInterface*);
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
        //UserInterface* userInterface_;
        CursorController * cursorController_;
        void drawTime(int);
};

#endif // GAMETIMER_H
