#ifndef ABSTRACTTANK_H
#define ABSTRACTTANK_H
#include "Field.h"
#include "CursorController.h"

enum Direction {UP, DOWN, LEFT, RIGHT, NONE};
struct CoordinatesDirection
{
    int x;
    int y;
    Direction direction;
};

class AbstractTank
{
public:
    AbstractTank();
    virtual ~AbstractTank() = 0;
    CoordinatesDirection tankInfo_;
    void moveForward();
    void shoot();
    void rotateInDirection(Direction);
    //void setDirection(Direction);
    Direction getDirection();
    Field * field_;
    CursorController * cursorController_;
    int myBullet_;

protected:

private:
};

#endif // ABSTRACTTANK_H
