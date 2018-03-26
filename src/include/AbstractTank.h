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

    static bool canShoot_;
    virtual ~AbstractTank() = 0;
    CoordinatesDirection tankInfo_;
    void moveForward();
    void shoot();
    void rotateInDirection(Direction);
    Direction getDirection();
    Field * field_;
    CursorController * cursorController_;
    int myBullet_;
    static const int step_;

protected:

private:
};

#endif // ABSTRACTTANK_H
