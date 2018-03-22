#include "Bullet.h"
#include "Field.h"
#include "AllyTank.h"
#include "CursorController.h"

Bullet::Bullet(Field * field, AllyTank::CoordinatesDirection cd)
{
    //ctor
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::moveForward(){
    int x = 0;
    int y = 0;
    switch (tankInfo_.direction)
    {
    case UP:
    {
        y=-1;
    }
    break;
    case DOWN:
    {
        y=1;
    }
    break;
    case LEFT:
    {
        x=-1;
    }
    break;
    case RIGHT:
    {
        x=1;
    }
    break;
    }

}

Bullet::CoordinatesDirection Bullet::getBulletInfo(){

}
