#include "Bullet.h"
#include "Field.h"
#include "AllyTank.h"
#include "CursorController.h"
#include <windows.h>

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
        bulletInfo_.y-=1;
    }
    break;
    case DOWN:
    {
        bulletInfo_.y+=1;
    }
    break;
    case LEFT:
    {
        bulletInfo_.x-=1;
    }
    break;
    case RIGHT:
    {
        bulletInfo_.x+=1;
    }
    break;
    }
    if(field_->isEmpty(bulletInfo_.x, bulletInfo_.y))
    {
        field_->drawField(bulletInfo_.x+field_->getFieldInfo().x, bulletInfo_.y+field_->getFieldInfo().y, "*");
        moveForward();
    }
    else
    {
        if(field_->isWall(bulletInfo_.x, bulletInfo_.y))
        {
            if(bulletInfo_.y!=field_->getFieldInfo().height-1 && bulletInfo_.y!=0 && bulletInfo_.x!=field_->getFieldInfo().width-1 && bulletInfo_.x!=0)
            {
                char c = field_->checkWallState(bulletInfo_.y, bulletInfo_.x);
                if (c=='-')
                {
                    field_->level_[bulletInfo_.y][bulletInfo_.x]='`';
                }
                else if(c=='`')
                {
                    field_->level_[bulletInfo_.y][bulletInfo_.x]=' ';
                }
                else if(c=='|')
                {
                    field_->level_[bulletInfo_.y][bulletInfo_.x]=':';
                }
                else
                {
                    field_->level_[bulletInfo_.y][bulletInfo_.x]=' ';
                }
            }
            field_->drawField(bulletInfo_.x+field_->getFieldInfo().x, bulletInfo_.y+field_->getFieldInfo().y, std::string(1, field_->level_[bulletInfo_.y][bulletInfo_.x]));
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
    while(field_->isEmpty(bulletInfo_.x+x, bulletInfo_.y+y))
    {
        redrawField(x, y, '*', ' ');
        bulletInfo_.x=bulletInfo_.x+x;
        bulletInfo_.y=bulletInfo_.y+y;
        Sleep(30);
    }
    if(!field_->isWall(bulletInfo_.x+x, bulletInfo_.y+y))
    {
        if(field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=='q')
        {
            redrawField(x, y, ' ', ' ');
            if(whoseBullet_==1){
            field_->setEnemiesCount(field_->getEnemiesCount()-1);
            field_->drawEnemiesKilled();
            if(field_->getEnemiesCount()==0)
            {
                field_->drawEndGame(1);
            }
            }
        }
        else if(field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=='Y')
        {
            redrawField(x, y, ' ', ' ');
            field_->drawEndGame(0);
        }
    }
    else
    {
        if(bulletInfo_.y+y!=field_->getFieldInfo().height-1 && bulletInfo_.y+y!=0 && bulletInfo_.x+x!=field_->getFieldInfo().width-1 && bulletInfo_.x+x!=0)
        {
            char c = field_->checkWallState(bulletInfo_.y+y, bulletInfo_.x+x);
            if (c=='-')
            {
                field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]='`';
            }
            else if(c=='`')
            {
                field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=' ';
            }
            else if(c=='|')
            {
                field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=':';
            }
            else
            {
                field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]=' ';
            }
        }
        field_->level_[bulletInfo_.y][bulletInfo_.x]=' ';
        field_->drawField(bulletInfo_.x+x+field_->getFieldInfo().x, bulletInfo_.y+y+field_->getFieldInfo().y, std::string(1, field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]));
        field_->drawField(bulletInfo_.x+field_->getFieldInfo().x, bulletInfo_.y+field_->getFieldInfo().y, std::string(1, field_->level_[bulletInfo_.y][bulletInfo_.x]));
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
    field_->level_[bulletInfo_.y][bulletInfo_.x]=c2;
    field_->drawField(bulletInfo_.x+x+field_->getFieldInfo().x, bulletInfo_.y+y+field_->getFieldInfo().y, std::string(1, field_->level_[bulletInfo_.y+y][bulletInfo_.x+x]));
    field_->drawField(bulletInfo_.x+field_->getFieldInfo().x, bulletInfo_.y+field_->getFieldInfo().y, std::string(1, field_->level_[bulletInfo_.y][bulletInfo_.x]));
}
