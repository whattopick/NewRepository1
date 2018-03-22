#include "AllyTank.h"
#include "Bullet.h"
#include "CursorController.h"
#include <windows.h>
#include <conio.h>

AllyTank::AllyTank(Field * field, CursorController * cursorController)
{
    //ctor
    field_=field;
    cursorController_=cursorController;
    tankInfo_.direction=UP;
    tankInfo_.x=field_->getFieldInfo().width/2;
    tankInfo_.y=field_->getFieldInfo().height-2;
    field_->level_[tankInfo_.y][tankInfo_.x]='o';
    field_->drawField(tankInfo_.x+field_->getFieldInfo().x, tankInfo_.y+field_->getFieldInfo().y, "o");
}

AllyTank::~AllyTank()
{
    //dtor
}


void AllyTank::controlTank()
{
    int c;
    while(true)
    {
        c=_getch();
        if(c==224)
        {
            c=_getch();

            if(c==72)
            {
                rotateInDirection(UP);
                moveForward();
            }
            if(c==80)
            {
                rotateInDirection(DOWN);
                moveForward();
            }
            if(c==75)
            {
                rotateInDirection(LEFT);
                moveForward();
            }

            if(c==77)
            {
                rotateInDirection(RIGHT);
                moveForward();
            }
        }
        /*if (c==32)
        {
            allyBullet_->shoot(tankCoordinates_[0], tankCoordinates_[1], currentDirection_);
        }*/
    }

}

int AllyTank::getHealthPoints()
{
    return healthPoints_;
}

void AllyTank::setHealthPoints(int hp)
{
    healthPoints_=hp;
}

void AllyTank::shoot()
{
    Bullet * bullet = new Bullet(field_, tankInfo_);
    bullet->moveForward();
}

