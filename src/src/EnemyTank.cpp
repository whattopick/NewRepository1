#include "EnemyTank.h"

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
    if( (tankInfo_.y==field_->getFieldInfo().height-2 && tankInfo_.x==field_->getFieldInfo().width/2) || (field_->level_[tankInfo_.y][tankInfo_.x])=='q' || field_->isStash(tankInfo_.x, tankInfo_.y)){
        delete this;
    }
    else{
    field_->level_[tankInfo_.y][tankInfo_.x]='q';
    field_->drawField(tankInfo_.x+field_->getFieldInfo().x, tankInfo_.y+field_->getFieldInfo().y, "q");
    }
    //field_->setMaxEnemies(1);
    //field_->setEnemiesCount(1);
    //field_->drawEnemiesKilled();
}

EnemyTank::~EnemyTank()
{
    //dtor
}

/*void EnemyTank::moveForward(){

}*/

/*void EnemyTank::shoot()
{

}*/

bool EnemyTank::isAlive()
{

}

void EnemyTank::doHisJob()
{
}

int EnemyTank::checkClosest(){
    int i;
    return i;
}
//}
/*void EnemyTank::rotateInDirection(Direction direction){

}*/
