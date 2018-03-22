#ifndef DRAWER_H
#define DRAWER_H
#include "CursorController.h"
#include "GameTimer.h"
#include "Field.h"
#include "AllyTank.h"


class Drawer
{
    public:
        Drawer(CursorController *);
        virtual ~Drawer();

        void drawField(int, int, int, int, char**);
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

#endif // DRAWER_H
