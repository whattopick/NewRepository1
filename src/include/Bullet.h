#ifndef BULLET_H
#define BULLET_H
#include "Field.h"
#include "AllyTank.h"
#include "CursorController.h"

class Bullet
{
    public:
        Bullet(Field *, CoordinatesDirection, int);
        virtual ~Bullet();
        void moveForward();
        CoordinatesDirection getBulletInfo();

    protected:

    private:
        CoordinatesDirection bulletInfo_;
        Field * field_;
        void redrawField(int, int, char, char);
        int whoseBullet_;
};

#endif // BULLET_H
