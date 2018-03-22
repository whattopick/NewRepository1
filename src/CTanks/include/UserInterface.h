#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "CursorController.h"
#include "GameTimer.h"
#include "Field.h"
#include "AllyTank.h"


class UserInterface
{
    public:
        UserInterface(CursorController *);
        virtual ~UserInterface();

        void drawField(int, int, char *);
        void drawEnemiesKilled(int);
        void drawHealthPoints(int);
        void drawTime(int);
        void drawVictory();
        void drawDefeat();



    protected:

    private:
        void drawHeader();
        CursorController * cursorController_;
};

#endif // USERINTERFACE_H
