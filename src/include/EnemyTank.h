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

    protected:

    private:
        AllyTank * allyTank_;
        bool isAlive();
        int checkClosest();
};

#endif // ENEMYTANK_H
