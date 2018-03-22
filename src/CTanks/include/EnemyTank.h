#ifndef ENEMYTANK_H
#define ENEMYTANK_H
#include "AbstractTank.h"
#include "Field.h"
#include "AllyTank.h"


class EnemyTank : public AbstractTank
{
    public:
        EnemyTank(Field *, AllyTank *);
        virtual ~EnemyTank();

    protected:

    private:
        CoordinatesDirection tankInfo_;
        AllyTank * allyTank_;
        void shoot();
};

#endif // ENEMYTANK_H
