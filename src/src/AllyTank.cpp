#include "AllyTank.h"
#include "Bullet.h"
#include "CursorController.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <thread>
#include "EnemyTank.h"

AllyTank::AllyTank(Field * field, CursorController * cursorController)
{
    //ctor
    field_=field;
    myBullet_=1;
    cursorController_= cursorController;
    tankInfo_.direction=UP;
    tankInfo_.x=field_->getFieldInfo().width/2;
    tankInfo_.y=field_->getFieldInfo().height-2;
    field_->level_[tankInfo_.y][tankInfo_.x]='o';
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
                if(tankInfo_.direction!=UP){
                rotateInDirection(UP);
                }
                else{
                    moveForward();
                }
            }
            if(c==80)
            {
                if(tankInfo_.direction!=DOWN){
                rotateInDirection(DOWN);
                }
                else{
                    moveForward();
                }
            }
            if(c==75)
            {
                if(tankInfo_.direction!=LEFT){
                    rotateInDirection(LEFT);
                }
                else{
                    moveForward();
                }
            }

            if(c==77)
            {
                if(tankInfo_.direction!=RIGHT){
                    rotateInDirection(RIGHT);
                }
                else{
                    moveForward();
                }
            }
        }
        else if (c==32)
        {
            if(canShoot_){
            canShoot_=false;
            std::thread t3([this]{shoot();});
            Sleep(100);
            canShoot_=true;
            t3.detach();
            }
        }
        Sleep(Bullet::speed_+10);
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

int AllyTank::healthPoints_=3;



