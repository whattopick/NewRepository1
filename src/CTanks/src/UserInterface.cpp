#include "UserInterface.h"
#include "CursorController.h"

UserInterface::UserInterface(CursorController * cursorController)
{
    //ctor
    cursorController_=cursorController;
    drawHeader();
}

UserInterface::~UserInterface()
{
    //dtor
    //delete cursorController_;
}

void UserInterface::drawVictory()
{
    for (int i=3; i<15; i++)
    {
        cursorController_->drawAtPlace(0, i, "VICTORY!!!!!!!!");
    }
}

void UserInterface::drawTime(int secs)
{
    cursorController_->drawAtPlace(3, 2, "Time spent: ");
    cursorController_->drawAtPlace(16, 2, (secs/60)/10);
    cursorController_->drawAtPlace(17, 2, (secs/60)%10);
    cursorController_->drawAtPlace(18, 2, "mm:");
    cursorController_->drawAtPlace(21, 2, (secs%60)/10);
    cursorController_->drawAtPlace(22, 2, (secs%60)%10);
    cursorController_->drawAtPlace(23, 2, "ss.");
}

void UserInterface::drawHealthPoints(int healthPoints)
{
    cursorController_->drawAtPlace(30, 2, "Lives left: ");
    for(int i=0; i<healthPoints; i++)
    {
        cursorController_->drawAtPlace(43 + i*4, 2, "(o)");
    }

}

void UserInterface::drawHeader()
{
    cursorController_->drawAtPlace(0, 0, "********* CRAZY TANKS *********\n                         ");
}

void UserInterface::drawField(int x, int y, char * c)
{
    cursorController_->drawAtPlace(x, y, c);
}

void UserInterface::drawEnemiesKilled(int enemiesKilled)
{
    cursorController_->drawAtPlace(59, 2, "Enemies killed: ");
    cursorController_->drawAtPlace(77, 2, enemiesKilled);

}
void UserInterface::drawDefeat()
{
    for (int i=3; i<15; i++)
    {
        cursorController_->drawAtPlace(0, i, "DEFEAT........");
    }

}
