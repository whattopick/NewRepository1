#include "AbstractTank.h"
#include <string>
#include "Bullet.h"

AbstractTank::AbstractTank()
{
    //ctor
}

AbstractTank::~AbstractTank()
{
    //dtor
}

void AbstractTank::moveForward()
{
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
    case NONE: default:{
        printf("Something went wrong...");
    }
    break;
    }
    if(field_->isEmpty(tankInfo_.x+x, tankInfo_.y+y))
    {
        field_->level_[tankInfo_.y+y][tankInfo_.x+x]='o';
        field_->level_[tankInfo_.y][tankInfo_.x]=' ';
        field_->drawField(tankInfo_.x+x+field_->getFieldInfo().x, tankInfo_.y+y+field_->getFieldInfo().y, std::string(1, field_->level_[tankInfo_.y+y][tankInfo_.x+x]));
        field_->drawField(tankInfo_.x+field_->getFieldInfo().x, tankInfo_.y+field_->getFieldInfo().y, std::string(1, field_->level_[tankInfo_.y][tankInfo_.x]));
        tankInfo_.x=tankInfo_.x+x;
        tankInfo_.y=tankInfo_.y+y;
    }
}


void AbstractTank::rotateInDirection(Direction direction)
{

    tankInfo_.direction=direction;
}


Direction AbstractTank::getDirection()
{
    return tankInfo_.direction;
}

void AbstractTank::shoot()
{
    Bullet * bullet = new Bullet(field_, tankInfo_, myBullet_);
}
