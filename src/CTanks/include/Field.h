#ifndef FIELD_H
#define FIELD_H
//#include "UserInterface.h"
#include "CursorController.h"
#include <string>

class UserInterface;

class Field
{
    public:
        //Field(int, int, UserInterface *);
        Field(int, int, CursorController *);
        virtual ~Field();
        struct FieldInfo{
            int x = 0;
            int y = 3;
            int width = 10;
            int height = 10;
        };
        struct GoldCoordinates{
        int x;
        int y;
        };
        char ** level_;

        bool isEmpty(int, int);
        FieldInfo getFieldInfo();
        bool isWall(int, int);
        char checkWallState(int, int);
        int getEnemiesCount();
        void setEnemiesCount(int);
        int getMaxEnemies();
        GoldCoordinates getGoldCoordinates();
        void drawField(int, int, std::string);
        void drawEnemiesKilled(int);

    protected:

    private:
        FieldInfo fieldInfo_;
        int maxEnemies_;
        int enemiesCount_;
        GoldCoordinates goldCoordinates_;
        //UserInterface * userInterface_;
        CursorController * cursorController_;
        void generateLevel();



};

#endif // FIELD_H
