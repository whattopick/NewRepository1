#include "EnemyTank.h"
#include <windows.h>
#include <stdlib.h>
#include <thread>
#include <math.h>

EnemyTank::EnemyTank(Field * field, int x, int y,  CursorController * cursorController, AllyTank * allyTank)
{
    //ctor
    field_=field;
    myBullet_=0;
    cursorController_= cursorController;
    allyTank_=allyTank;
    tankInfo_.direction=UP;
    tankInfo_.x=x;
    tankInfo_.y=y;
    if( (tankInfo_.y==field_->getFieldInfo().height-2 && tankInfo_.x==field_->getFieldInfo().width/2) ||
       (field_->level_[tankInfo_.y][tankInfo_.x])=='q' ||
       field_->isStash(tankInfo_.x, tankInfo_.y))
    {
        field_->setEnemiesCount(field_->getEnemiesCount()-1);
        delete this;
    }
    else
    {
        field_->level_[tankInfo_.y][tankInfo_.x]='q';
        field_->nlevel_[tankInfo_.y][tankInfo_.x]='q';
    }
}

EnemyTank::~EnemyTank()
{
    //dtor
}


bool EnemyTank::isAlive()
{
    if(field_->nlevel_[tankInfo_.y][tankInfo_.x]=='q')
    {
        return true;
    }
    else
        return false;
}

void EnemyTank::doHisJob()
{
        while(isAlive())
        {
            Sleep(1000);
            tankInfo_.direction=checkClosest(field_->getGoldCoordinates(), allyTank_->tankInfo_);
            moveForward();
            shoot();
        }
        delete this;
}

void EnemyTank::startIt(){
std::thread t30([this]{doHisJob();});
    t30.detach();
}

Direction EnemyTank::checkClosest(GoldCoordinates gc, CoordinatesDirection ac)
{
    Direction direction;
    if( fabs(gc.x-tankInfo_.x)<=fabs(ac.x-tankInfo_.x) ) //x1x2
    {
        if(tankInfo_.x<gc.x)
                {
                    direction=RIGHT;
                }
                else if(tankInfo_.x==gc.x)
                {
                    if(gc.y>tankInfo_.y)
                    {
                        direction=DOWN;
                    }
                    else
                    {
                        direction=UP;
                    }
                }
                else{
                    direction=LEFT;
                }
        if(fabs(gc.x-tankInfo_.x)<=fabs(gc.y-tankInfo_.y)) //x1y1
        {
            if(tankInfo_.x<gc.x)
                {
                    direction=RIGHT;
                }
                else if(tankInfo_.x==gc.x)
                {
                    if(gc.y>tankInfo_.y)
                    {
                        direction=DOWN;
                    }
                    else
                    {
                        direction=UP;
                    }
                }
                else{
                    direction=LEFT;
                }
            if(fabs(gc.x-tankInfo_.x)<=fabs(ac.y-tankInfo_.y)) //x1y2
            {
                if(tankInfo_.x<gc.x)
                {
                    direction=RIGHT;
                }
                else if(tankInfo_.x==gc.x)
                {
                    if(gc.y>tankInfo_.y)
                    {
                        direction=DOWN;
                    }
                    else
                    {
                        direction=UP;
                    }
                }
                else
                {
                    direction=LEFT;
                }
            }
            else
            {
                if(fabs(ac.y-tankInfo_.y)<=fabs(gc.y-tankInfo_.y)) //y2y1
                {
                    if(tankInfo_.y<ac.y)
                    {
                        direction=DOWN;
                    }
                    else if(tankInfo_.y==ac.y)
                    {
                        if(ac.x<tankInfo_.x)
                        {
                            direction=LEFT;
                        }
                        else
                        {
                            direction=RIGHT;
                        }
                    }
                    else
                    {
                        direction=UP;
                    }
                }
                else
                {
                    if(tankInfo_.y<gc.y)
                    {
                        direction=DOWN;
                    }
                    else if(tankInfo_.y==gc.y)
                    {
                        if(gc.x<tankInfo_.x)
                        {
                            direction=LEFT;
                        }
                        else
                        {
                            direction=RIGHT;
                        }
                    }
                    else
                    {
                        direction=UP;
                    }
                }
            }
        }
        else
        {
            if(tankInfo_.y<gc.y)
            {
                direction=DOWN;
            }
            else if(tankInfo_.y==gc.y)
            {
                if(gc.x<tankInfo_.x)
                {
                    direction=LEFT;
                }
                else
                {
                    direction=RIGHT;
                }
            }
            else
            {
                direction=UP;
            }
        }

    }
    else
    {
        if(fabs(ac.x-tankInfo_.x)<=fabs(ac.y-tankInfo_.y)) //x2y2
        {
            if(tankInfo_.x>ac.x)
                {
                    direction=LEFT;
                }
                else if(tankInfo_.x==ac.x)
                {
                    if(ac.y>tankInfo_.y)
                    {
                        direction=DOWN;
                    }
                    else
                    {
                        direction=UP;
                    }
                }
                else{
                    direction=RIGHT;
                }
            if(fabs(ac.x-tankInfo_.x)<=fabs(gc.y-tankInfo_.y)) //x2y1
            {
                if(tankInfo_.x>ac.x)
                {
                    direction=LEFT;
                }
                else if(tankInfo_.x==ac.x)
                {
                    if(ac.y>tankInfo_.y)
                    {
                        direction=DOWN;
                    }
                    else
                    {
                        direction=UP;
                    }
                }
                else
                {
                    direction=RIGHT;
                }
            }
            else
            {
                if(fabs(ac.y-tankInfo_.y)<=fabs(gc.y-tankInfo_.y)) //y2y1
                {
                    if(tankInfo_.y<ac.y)
                    {
                        direction=DOWN;
                    }
                    else if(tankInfo_.y==ac.y)
                    {
                        if(ac.x<tankInfo_.x)
                        {
                            direction=LEFT;
                        }
                        else
                        {
                            direction=RIGHT;
                        }
                    }
                    else
                    {
                        direction=UP;
                    }
                }
                else
                {
                    if(tankInfo_.y<gc.y)
                    {
                        direction=DOWN;
                    }
                    else if(tankInfo_.y==gc.y)
                    {
                        if(gc.x<tankInfo_.x)
                        {
                            direction=LEFT;
                        }
                        else
                        {
                            direction=RIGHT;
                        }
                    }
                    else
                    {
                        direction=UP;
                    }
                }
            }
        }
        else
        {
            if(tankInfo_.y<ac.y)
            {
                direction=DOWN;
            }
            else if(tankInfo_.y==ac.y)
            {
                if(ac.x<tankInfo_.x)
                {
                    direction=LEFT;
                }
                else
                {
                    direction=RIGHT;
                }
            }
            else
            {
                direction=UP;
            }
        }
    }
    return direction;
}

//bool EnemyTank::canStart_=false;
