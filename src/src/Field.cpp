#include "Field.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string>
#include "GameTimer.h"
#include "AllyTank.h"

Field::Field(int width, int height, CursorController * cursorController)
{
    //ctor
    fieldInfo_.x=leftUpperCornerX_;
    fieldInfo_.y=leftUpperCornerY_;
    if (width>=minWidth_ && width<=maxWidth_)
    {
        fieldInfo_.width=width;
    }
    else if (width>maxWidth_)
    {
        fieldInfo_.width=maxWidth_;
    }
    else
    {
        fieldInfo_.width=minWidth_;
    }
    if (width>=minHeight_ && height<=maxHeight_)
    {
        fieldInfo_.height=height;
    }
    else if (height>maxHeight_)
    {
        fieldInfo_.height=maxHeight_;
    }
    else
    {
        fieldInfo_.height=minHeight_;
    }
    gameStatsTime_ = new char[9];
    gameStatsKills_ = new char[2];
    gameStatsLeft_ = new char[2];
    gameStatsTime_[0]='0';
    gameStatsTime_[1]='0';
    gameStatsTime_[2]='m';
    gameStatsTime_[3]='m';
    gameStatsTime_[4]=':';
    gameStatsTime_[5]='0';
    gameStatsTime_[6]='0';
    gameStatsTime_[7]='s';
    gameStatsTime_[8]='s';

    cursorController_=cursorController;
    drawHelp();
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

void Field::testDraw()
{
    if(GameTimer::seconds_<60)
    {

        snprintf(gameStatsTime_, 9, "%d", 100000000+(GameTimer::seconds_%60)*100);
        gameStatsTime_[0]='0';
        gameStatsTime_[1]='0';
    }
    else if(GameTimer::seconds_/60>10)
    {
        snprintf(gameStatsTime_, 9, "%d", (GameTimer::seconds_/60)*100000000+(GameTimer::seconds_%60)*100);
    }
    else
    {
        snprintf(gameStatsTime_, 9, "%d", 100000000+(GameTimer::seconds_/60)*10000000+(GameTimer::seconds_%60)*100);
        gameStatsTime_[0]='0';
    }
    gameStatsTime_[2]='m';
    gameStatsTime_[3]='m';
    gameStatsTime_[4]=':';
    gameStatsTime_[7]='s';
    gameStatsTime_[8]='s';

    for(int i=0; i<9; i++)
    {
        drawField(16+i, 2, std::string(1, gameStatsTime_[i]));
    }

    snprintf(gameStatsKills_, 2, "%d", maxEnemies_-enemiesCount_);
    snprintf(gameStatsLeft_, 9, "%d", enemiesCount_);

    for(int i=0; i<2; i++)
    {
        drawField(76+i, 2, std::string(1, gameStatsKills_[i]));
    }

    for(int i=0; i<2; i++)
    {
        drawField(99+i, 2, std::string(1, gameStatsLeft_[i]));
    }

    for(int i=0; i<3; i++)
    {
        if(i<AllyTank::healthPoints_)
        {
            drawField(43+i*4, 2, "(o)");
        }
        else
        {
            drawField(43+i*4, 2, "   ");
        }
    }

    for(int i=0; i<fieldInfo_.height; i++)
    {
        for(int j=0; j<fieldInfo_.width; j++)
        {
            if(nlevel_[i][j]!=level_[i][j])
            {
                nlevel_[i][j]=level_[i][j];
                drawField(j+fieldInfo_.x, i+fieldInfo_.y, std::string(1, level_[i][j]));
            }
        }
    }
}

void Field::setEnemiesCount(int enemiesCount)
{
    enemiesCount_=enemiesCount;
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

void Field::drawField(int x, int y, int s)
{
    while(cursorController_->isFree_==false);
    cursorController_->isFree_=false;
    cursorController_->drawAtPlace(x, y, s);
    cursorController_->isFree_=true;
}

void Field::drawEndGame(int result)
{
    Sleep(35);
    while(cursorController_->isFree_==false);
    cursorController_->isFree_=false;
    for (int i=fieldInfo_.y; i<fieldInfo_.y+fieldInfo_.height-3; i++)
    {
        if(result==0)
        {
            cursorController_->drawAtPlace(0, i, "DEFEAT...");
        }
        else
        {
            cursorController_->drawAtPlace(0, i, "VICTORY!!");
        }
        Sleep(20);
    }
    exit(0);
}

void Field::generateLevel()
{
    level_=new char *[fieldInfo_.height];
    nlevel_=new char *[fieldInfo_.height];
    for(int i=0; i<fieldInfo_.height; i++)
    {
        level_[i] =new char[fieldInfo_.width];
        nlevel_[i] =new char[fieldInfo_.width];
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
    while( (goldCoordinates_.x==fieldInfo_.width/2|| goldCoordinates_.x==fieldInfo_.width/2 + 1 || goldCoordinates_.x==fieldInfo_.width/2 -1) ||
            (goldCoordinates_.x==fieldInfo_.height-2 || goldCoordinates_.y==fieldInfo_.height-1 || goldCoordinates_.x==fieldInfo_.height-3));
    level_[getGoldCoordinates().y][getGoldCoordinates().x]='Y';
    level_[getGoldCoordinates().y-1][getGoldCoordinates().x]='-';
    level_[getGoldCoordinates().y+1][getGoldCoordinates().x]='-';
    level_[getGoldCoordinates().y][getGoldCoordinates().x-1]='|';
    level_[getGoldCoordinates().y][getGoldCoordinates().x+1]='|';

    int k1;
    int k2;
    for(int i=1; i<fieldInfo_.height-1; i++)
    {
        srand(i);
        for(int j=0; j<fieldInfo_.width/10; j++ )
        {
            k1=rand()%(fieldInfo_.width-3)+1;
            k2=rand()%8;
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
            else if(k2==2)
            {
                if(isEmpty(k1, i))
                {
                    if(!isWall(k1, i-1))
                    {
                        level_[i][k1]='`';
                    }
                }
            }
            else if(k2==4)
            {
                if(isEmpty(k1, i))
                {
                    if(isWall(k1-1, i))
                    {
                        k1+=2;
                    }
                    level_[i][k1]=':';
                }
            }
            else if(k2==6)
            {
                if(isEmpty(k1, i))
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
    for(int i=0; i<fieldInfo_.height; i++)
    {
        for(int j=0; j<fieldInfo_.width; j++)
        {
            nlevel_[i][j] = level_[i][j];
        }
    }
    srand(time(NULL));
    maxEnemies_= rand()%((fieldInfo_.width * fieldInfo_.height)/(minWidth_*minHeight_))+1;
    enemiesCount_=maxEnemies_;
    level_[fieldInfo_.height-2][fieldInfo_.width/2]=' ';

}

void Field::drawHelp()
{
    drawField(0, 0, " ----------------------------------------------------------------------------------------------------- CRAZY TANKS ----------------------------------------------------------------------------------------------");
    drawField(0, 1, "                                          ");
    drawField(3, 2, "Time spent: ");
    drawField(30, 2, "Lives left: ");
    drawField(59, 2, "Enemies killed:        Enemies left: ");
    drawField(214, 0, "---- HELP SECTION ----");
    drawField(214, 3, "----------------------");
    drawField(216, 5, "This is your tank");
    drawField(225, 7, "o");
    drawField(216, 9, "This is enemy tank");
    drawField(225, 11, "q");
    drawField(218, 13, "These are walls");
    drawField(222, 15, "| : ` -");
    drawField(219, 17, "This is gold");
    drawField(218, 18, "in its fortress");
    drawField(225, 19, "-");
    drawField(224, 20, "|Y|");
    drawField(225, 21, "-");
    drawField(216, 24, "Control your tank");
    drawField(216, 25, "using arrow keys");
    drawField(215, 27, "Hit space to shoot");
    drawField(215, 31, "Shoot 1x bullet to");
    drawField(215, 33, "damage intact wall");
    drawField(223, 34, "-OR-");
    drawField(215, 35, "ruin damaged wall");
    drawField(223, 36, "-OR-");
    drawField(219, 37, "kill enemy");
    drawField(216, 40, "You win when all");
    drawField(216, 41, "enemies are dead");
    drawField(217, 43, "You loose when");
    drawField(216, 45, "you die 3x times");
    drawField(223, 46, "-OR-");
    drawField(216, 47, "gold is captured");
    drawField(223, 50, "DOs:");
    drawField(218, 52, "kill enemies");
    drawField(218, 53, "protect gold");
    drawField(222, 55, "DON\'Ts:");
    drawField(217, 57, "shoot at gold");
    drawField(217, 58, "play for 1hour+");
    drawField(214, 62, "----------------------");
    for (int i=0; i<25; i+=24)
    {
        for(int j=1; j<maxHeight_-1; j++)
        {
            drawField(212+i, fieldInfo_.y+j, "|");
        }
    }
}

bool Field::isStash(int x, int y)
{
    if ( (x==getGoldCoordinates().x && y==getGoldCoordinates().y) ||
            (x==getGoldCoordinates().x-1 && y==getGoldCoordinates().y) ||
            (x==getGoldCoordinates().x+1 && y==getGoldCoordinates().y) ||
            (x==getGoldCoordinates().x && y==getGoldCoordinates().y+1) ||
            (x==getGoldCoordinates().x && y==getGoldCoordinates().y-1) )
    {
        return true;
    }
    else
    {
        return false;
    }
}
