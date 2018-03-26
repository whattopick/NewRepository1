#include "Bullet.h"
#include "Field.h"
#include "AllyTank.h"
#include "AbstractTank.h"
#include "CursorController.h"
#include <windows.h>
#include <stdio.h>

Bullet::Bullet(Field * field, CoordinatesDirection coordinatesDirection, int whoseBullet)
{
    //ctor
    bulletInfo_=coordinatesDirection;
    whoseBullet_=whoseBullet;
    field_=field;
    switch (bulletInfo_.direction)
    {
    case UP:
    {
        bulletInfo_.y-=AbstractTank::step_;
    }
    break;
    case DOWN:
    {
        bulletInfo_.y+=AbstractTank::step_;
    }
    break;
    case LEFT:
    {
        bulletInfo_.x-=AbstractTank::step_;
    }
    break;
    case RIGHT:
    {
        bulletInfo_.x+=AbstractTank::step_;
    }
    break;
    case NONE: default:
    {
        printf("Something went wrong...");
    }
    break;
    }
    if(field_->isEmpty(bulletInfo_.x, bulletInfo_.y))
    {
        field_->level_[bulletInfo_.y][bulletInfo_.x]='*';
        moveForward();
    }
    else
    {
        if(!field_->isWall(bulletInfo_.x, bulletInfo_.y))
        {
            if(field_->level_[bulletInfo_.y][bulletInfo_.x]=='q')
            {
                if(whoseBullet_==1)
                {
                    redrawField(0, 0, ' ', ' ');
                    field_->setEnemiesCount(field_->getEnemiesCount()-1);
                    if(field_->getEnemiesCount()==0)
                    {
                        field_->drawEndGame(1);
                    }
                }
                else{
                redrawField(0, 0, 'q', ' ');
            }
            }
            else if(field_->level_[bulletInfo_.y][bulletInfo_.x]=='Y')
            {
                redrawField(0, 0, ' ', ' ');
                field_->drawEndGame(0);
            }
            else if(field_->level_[bulletInfo_.y][bulletInfo_.x]=='o')
        {
            AllyTank::healthPoints_-=1;
            if(AllyTank::healthPoints_==0){
            redrawField(0, 0, ' ', ' ');
            field_->drawEndGame(0);}
            else{
                redrawField(0, 0, 'o', ' ');
            }
        }
        else if(field_->level_[bulletInfo_.y][bulletInfo_.x]=='*')
        {
            redrawField(0, 0, ' ', ' ');
        }
        }
        else
        {
            if(bulletInfo_.y!=field_->getFieldInfo().height-1
               && bulletInfo_.y!=0 && bulletInfo_.x!=field_->getFieldInfo().width-1
               && bulletInfo_.x!=0)
            {
                char c = field_->checkWallState(bulletInfo_.y, bulletInfo_.x);
                if (c=='-')
                {
                    redrawField(0, 0, '`', ' ');
                }
                else if(c=='`' || c==':')
                {
                    redrawField(0, 0, ' ', ' ');
                }
                else if(c=='|')
                {
                    redrawField(0, 0, ':', ' ');
                }
            }
        }
        delete this;
    }
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::moveForward()
{
    int x = 0;

    int y = 0;
    switch (bulletInfo_.direction)
    {
    case UP:
    {
        y=-AbstractTank::step_;
    }
    break;
    case DOWN:
    {
        y=AbstractTank::step_;
    }
    break;
    case LEFT:
    {
        x=-AbstractTank::step_;
    }
    break;
    case RIGHT:
    {
        x=AbstractTank::step_;
    }
    break;
    case NONE: default:
    {
        printf("Something went wrong...");
    }
    break;
    }
    while(field_->isEmpty(bulletInfo_.x+x, bulletInfo_.y+y))
    {
        Sleep(speed_);
        redrawField(x, y, '*', ' ');
        bulletInfo_.x=bulletInfo_.x+x;
        bulletInfo_.y=bulletInfo_.y+y;
    }
    if(!field_->isWall(bulletInfo_.x+x, bulletInfo_.y+y))
    {
        if(field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=='q')
        {
            if(whoseBullet_==1)
            {
                redrawField(x, y, ' ', ' ');
                field_->setEnemiesCount(field_->getEnemiesCount()-1);
                if(field_->getEnemiesCount()==0)
                {
                    field_->drawEndGame(1);
                }
            }
            else{
                redrawField(x, y, 'q', ' ');
            }
        }
        else if(field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=='Y')
        {
            redrawField(x, y, ' ', ' ');
            field_->drawEndGame(0);
        }
        else if(field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=='o')
        {
            AllyTank::healthPoints_-=1;
            if(AllyTank::healthPoints_==0){
            redrawField(x, y, ' ', ' ');
            field_->drawEndGame(0);}
            else{
                redrawField(x, y, 'o', ' ');
            }
        }
        else if(field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=='*')
        {
            redrawField(x, y, ' ', ' ');
        }
    }
    else
    {
        if(bulletInfo_.y+y!=field_->getFieldInfo().height-1
           && bulletInfo_.y+y!=0
           && bulletInfo_.x+x!=field_->getFieldInfo().width-1
           && bulletInfo_.x+x!=0)
        {
            char c = field_->checkWallState(bulletInfo_.y+y, bulletInfo_.x+x);
            if (c=='-')
            {
                redrawField(x, y, '`', ' ');
            }
            else if(c=='`' || c==':')
            {
                redrawField(x, y, ' ', ' ');
            }
            else if(c=='|')
            {
                redrawField(x, y, ':', ' ');
            }
        }
        else{
                redrawField(0, 0, ' ', ' ');
        }
    }
    delete this;
}

CoordinatesDirection Bullet::getBulletInfo()
{
    return bulletInfo_;
}

void Bullet::redrawField(int x, int y, char c1, char c2)
{
    field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=c1;
    if(x!=y)
    {
    field_->level_[bulletInfo_.y][bulletInfo_.x]=c2;
    }
}

const int Bullet::speed_=30;
