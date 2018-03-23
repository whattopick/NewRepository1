#include "Field.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string>

Field::Field(int width, int height, CursorController * cursorController)
{
    //ctor
    if (width>fieldInfo_.width && width<=210)
    {
        fieldInfo_.width=width;
    }
    if (width>fieldInfo_.height && height<=60)
    {
        fieldInfo_.height=height;
    }
    cursorController_=cursorController;

    generateLevel();

    for(int i=0; i<fieldInfo_.height; i++)
    {
        for(int j=0; j<fieldInfo_.width; j++)
        {
            drawField(j+fieldInfo_.x, i+fieldInfo_.y, std::string(1, level_[i][j]));
        }
    }
}

Field::~Field()
{
    //dtor
}

void Field::setEnemiesCount(int enemiesCount){
    enemiesCount_=enemiesCount;
}

void Field::setMaxEnemies(int enemiesCount){
    maxEnemies_=enemiesCount;
}

bool Field::isEmpty(int x, int y)
{
    if (level_[y][x]==' ')
    {
        return true;
    }
    else
        return false;

}

bool Field::isWall(int x, int y)
{
    if (level_[y][x]=='-' || level_[y][x]=='|' || level_[y][x]==':' || level_[y][x]=='`')
    {
        return true;
    }
    else
        return false;

}

char Field::checkWallState(int x, int y)
{
    return level_[x][y];
}

int Field::getEnemiesCount()
{
    return enemiesCount_;
}

int Field::getMaxEnemies()
{
    return maxEnemies_;
}

FieldInfo Field::getFieldInfo()
{
    return fieldInfo_;
}

GoldCoordinates Field::getGoldCoordinates()
{
    return goldCoordinates_;

}

void Field::drawField(int x, int y, std::string s)
{
    while(cursorController_->isFree_==false);
    cursorController_->isFree_=false;
    cursorController_->drawAtPlace(x, y, s);
    cursorController_->isFree_=true;
}

void Field::drawEnemiesKilled()
{
    while(cursorController_->isFree_==false);
    cursorController_->isFree_=false;
    cursorController_->drawAtPlace(59, 2, "Enemies killed: ");
    cursorController_->drawAtPlace(77, 2, maxEnemies_-enemiesCount_);
    cursorController_->isFree_=true;
}

void Field::drawHealthPoints(int healthPoints)
{
    cursorController_->drawAtPlace(30, 2, "Lives left: ");
    for(int i=0; i<healthPoints; i++)
    {
        while(cursorController_->isFree_==false);
    cursorController_->isFree_=false;
        cursorController_->drawAtPlace(43 + i*4, 2, "(o)");
        cursorController_->isFree_=true;
    }

}

void Field::drawEndGame(int result){
    while(cursorController_->isFree_==false);
    cursorController_->isFree_=false;
    for (int i=fieldInfo_.y; i<fieldInfo_.y+fieldInfo_.height; i++)
    {
        if(result==0){
        cursorController_->drawAtPlace(0, i, "DEFEAT...");
        }
        else{
        cursorController_->drawAtPlace(0, i, "VICTORY!!");
        }
        Sleep(20);
    }
        exit(0);
}

void Field::generateLevel()
{
    level_=new char *[fieldInfo_.height];
    for(int i=0; i<fieldInfo_.height; i++)
    {
        level_[i] =new char[fieldInfo_.width];
        for(int j=0; j<fieldInfo_.width; j++)
        {
            level_[i][j] = ' ';
        }
    }
    for(int i=0; i<fieldInfo_.height; i+=fieldInfo_.height-1)
    {
        for(int j=1; j<fieldInfo_.width-1; j++)
        {
            level_[i][j]='-';
        }
    }
    for(int i=0; i<fieldInfo_.width; i+=fieldInfo_.width-1)
    {
        for(int j=1; j<fieldInfo_.height-1; j++)
        {
            level_[j][i]='|';
        }
    }
    srand(time(NULL));
    do
    {
        goldCoordinates_.x= (rand()%(fieldInfo_.width-2)+1);
        goldCoordinates_.y= (rand()%(fieldInfo_.height-2)+1);
        //goldCoordinates_.x= 9;
        //goldCoordinates_.y= 9;
    }
    while( (goldCoordinates_.x==fieldInfo_.width/2 || goldCoordinates_.x==fieldInfo_.width/2 + 1 || goldCoordinates_.x==fieldInfo_.width/2 -1) || (goldCoordinates_.x==fieldInfo_.height-2 || goldCoordinates_.y==fieldInfo_.height-1 || goldCoordinates_.x==fieldInfo_.height-3));
    level_[getGoldCoordinates().y][getGoldCoordinates().x]='Y';
    level_[getGoldCoordinates().y-1][getGoldCoordinates().x]='-';
    level_[getGoldCoordinates().y+1][getGoldCoordinates().x]='-';
    level_[getGoldCoordinates().y][getGoldCoordinates().x-1]='|';
    level_[getGoldCoordinates().y][getGoldCoordinates().x+1]='|';

    int k1;
    int k2;
    for(int i=1; i<fieldInfo_.height-1; i++)
    {
        srand(time(NULL));
        for(int j=0; j<fieldInfo_.width/10; j++ )
        {
            k1=rand()%(fieldInfo_.width-2)+1;
            k2=rand()%2;
            if(k2==0)
            {
                if(isEmpty(k1, i))
                {
                    if(!isWall(k1, i-1))
                    {
                        level_[i][k1]='-';
                    }
                }
            }
            else
            {
                if(isEmpty(k1, i))
                {
                    if(k1<fieldInfo_.width-2)
                    {
                        if(isWall(k1-1, i))
                        {
                            k1+=2;
                        }
                        level_[i][k1]='|';
                    }
                }
            }
        }
        Sleep(100);
        if(i%3==0)
        {
            /*while(cursorController_->isFree_==false);
            cursorController_->isFree_=false;
            cursorController_->drawAtPlace(21+i/3, 1, ".");
            cursorController_->isFree_=true;*/
            drawField(21+i/3, 1, ".");
        }
    }
    maxEnemies_=(fieldInfo_.width * fieldInfo_.height)/200;
    enemiesCount_=maxEnemies_;
    drawEnemiesKilled();
    level_[fieldInfo_.height-2][fieldInfo_.width/2]=' ';

}

bool Field::isStash(int x, int y){
    if ( (x==getGoldCoordinates().x && y==getGoldCoordinates().y) || (x==getGoldCoordinates().x-1 && y==getGoldCoordinates().y) || (x==getGoldCoordinates().x+1 && y==getGoldCoordinates().y) || (x==getGoldCoordinates().x && y==getGoldCoordinates().y+1) || (x==getGoldCoordinates().x && y==getGoldCoordinates().y-1) ){
            return true;
    }
    else{
        return false;
    }
}
