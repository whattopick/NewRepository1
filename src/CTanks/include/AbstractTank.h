#ifndef ABSTRACTTANK_H
#define ABSTRACTTANK_H
#include "Field.h"
#include "CursorController.h"

class AbstractTank
{
    public:
        AbstractTank();
        virtual ~AbstractTank() = 0;

        enum Direction {UP, DOWN, LEFT, RIGHT, NONE};
        struct CoordinatesDirection{
            int x;
            int y;
            Direction direction;
        };
        CoordinatesDirection tankInfo_;
        void moveForward();
        virtual void shoot() = 0;
        void rotateInDirection(Direction);
        //void setDirection(Direction);
        Direction getDirection();
        Field * field_;
        CursorController * cursorController_;

    protected:

    private:
};

#endif // ABSTRACTTANK_H
