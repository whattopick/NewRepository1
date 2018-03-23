#ifndef FIELD_H
#define FIELD_H
#include "CursorController.h"
#include <string>

class UserInterface;

struct FieldInfo{
            int x = 0;
            int y = 3;
            int width = 20;
            int height = 10;
        };
        struct GoldCoordinates{
        int x;
        int y;
        };

class Field
{
    public:
        Field(int, int, CursorController *);
        virtual ~Field();

        char ** level_;

        bool isStash(int, int);
        bool isEmpty(int, int);
        FieldInfo getFieldInfo();
        bool isWall(int, int);
        char checkWallState(int, int);
        int getEnemiesCount();
        void setEnemiesCount(int);
        void setMaxEnemies(int);
        int getMaxEnemies();
        GoldCoordinates getGoldCoordinates();
        void drawField(int, int, std::string);
        void drawEnemiesKilled();
        void drawHealthPoints(int);
        void drawEndGame(int);

    protected:

    private:
        FieldInfo fieldInfo_;
        int maxEnemies_;
        int enemiesCount_;
        GoldCoordinates goldCoordinates_;
        CursorController * cursorController_;
        void generateLevel();

};

#endif // FIELD_H
