#ifndef ALLYTANK_H
#define ALLYTANK_H
#include "AbstractTank.h"
#include "Field.h"
#include "CursorController.h"

class Field;
class UserInterface;

class AllyTank : public AbstractTank
{
    public:
        AllyTank(Field*, CursorController *);
        virtual ~AllyTank();
        void controlTank();


    protected:

    private:
        int healthPoints_=3;
        int getHealthPoints();
        void setHealthPoints(int);
        void shoot();
};

#endif // ALLYTANK_H