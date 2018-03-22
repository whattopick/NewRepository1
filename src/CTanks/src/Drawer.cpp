#include "Drawer.h"
#include "CursorController.h"

Drawer::Drawer(CursorController * cursorController)
{
    //ctor
    cursorController_=cursorController;
    drawHeader();
    drawHealthPoints();
    drawEnemiesKilled();

}

Drawer::~Drawer()
{
    //dtor
    //delete cursorController_;
}

void Drawer::drawVictory()
{
    for (int i=3; i<15; i++)
    {
        cursorController_->drawAtPlace(0, i, "VICTORY!!!!!!!!");
    }
}

void Drawer::drawTime(int secs)
{
    cursorController_->drawAtPlace(3, 2, "Time spent: ");
    cursorController_->drawAtPlace(16, 2, (secs/60)/10);
    cursorController_->drawAtPlace(17, 2, (secs/60)%10);
    cursorController_->drawAtPlace(18, 2, "mm:");
    cursorController_->drawAtPlace(21, 2, (secs%60)/10);
    cursorController_->drawAtPlace(22, 2, (secs%60)%10);
    cursorController_->drawAtPlace(23, 2, "ss.");
}

void Drawer::drawHealthPoints(int healthPoints)
{
    cursorController_->drawAtPlace(30, 2, "Lives left: ");
    for(int i=0; i<healthPoints; i++)
    {
        cursorController_->drawAtPlace(43 + i*4, 2, "(o)");
    }

}

void Drawer::drawHeader()
{
    cursorController_->drawAtPlace(0, 0, "*** CRAZY TANKS ***");
}

void Drawer::drawField(int x, int y, int w, int h, char** level)
{
    for(int i=y; i<y+h; i++){
        for(int j=x; j<x+w; j++){
            cursorController_->drawAtPlace(j, i, level[i][j]);
        }
    }
}

void Drawer::drawEnemiesKilled(int enemiesKilled)
{
    cursorController_->drawAtPlace(59, 2, "Enemies killed: ");
    cursorController_->drawAtPlace(77, 2, enemiesKilled);

}
void Drawer::drawDefeat()
{
    for (int i=3; i<15; i++)
    {
        cursorController_->drawAtPlace(0, i, "DEFEAT........");
    }

}
