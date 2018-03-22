#ifndef BULLET_H
#define BULLET_H
#include "Field.h"
#include "AllyTank.h"
#include "CursorController.h"



class Bullet
{
    public:
        enum Direction {UP, DOWN, LEFT, RIGHT, NONE};
        struct CoordinatesDirection{
            int x;
            int y;
            Direction direction;
        };
        Bullet(Field *, AllyTank::CoordinatesDirection);
        virtual ~Bullet();
        void moveForward();
        CoordinatesDirection getBulletInfo();
        //CursorController * cursorController_;

    protected:

    private:
        CoordinatesDirection bulletInfo_;
        Field * field_;
};

#endif // BULLET_H
