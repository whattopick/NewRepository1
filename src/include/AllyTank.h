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
        static int healthPoints_;

    protected:

    private:

        int getHealthPoints();
        void setHealthPoints(int);
};

#endif // ALLYTANK_H
