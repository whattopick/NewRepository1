#include "Field.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string>

Field::Field(int width, int height, CursorController * cursorController)
{
    //ctor
    if (width>fieldInfo_.width && width<301)
    {
        fieldInfo_.width=width;
    }
    if (width>fieldInfo_.height && height<156)
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
    if (level_[y][x]=='-' || level_[y][x]=='|')
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

Field::FieldInfo Field::getFieldInfo()
{
    return fieldInfo_;
}

Field::GoldCoordinates Field::getGoldCoordinates()
{
    return goldCoordinates_;

}

void Field::drawField(int x, int y, std::string s)
{
    cursorController_->drawAtPlace(x, y, s);
}

void Field::drawEnemiesKilled(int enemiesKilled)
{
    cursorController_->drawAtPlace(59, 2, "Enemies killed: ");
    cursorController_->drawAtPlace(77, 2, enemiesKilled);

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
        if(i%3==0){
        cursorController_->drawAtPlace(21+i/3, 1, ".");}
    }
    level_[fieldInfo_.height-2][fieldInfo_.width/2]=' ';

}
