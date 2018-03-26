#ifndef ENEMYTANK_H
#define ENEMYTANK_H
#include "AbstractTank.h"
#include "Field.h"
#include "AllyTank.h"
#include "CursorController.h"


class EnemyTank : public AbstractTank
{
    public:
        EnemyTank(Field *, int, int, CursorController *, AllyTank *);
        virtual ~EnemyTank();
        void doHisJob();
        void startIt();

    protected:

    private:
        AllyTank * allyTank_;
        bool isAlive();
        Direction checkClosest(GoldCoordinates, CoordinatesDirection);
};

#endif // ENEMYTANK_H
