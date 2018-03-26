#ifndef FIELD_H
#define FIELD_H
#include "CursorController.h"
#include <string>

class UserInterface;

struct FieldInfo{
            int x;
            int y;
            int width;
            int height;
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
        char ** nlevel_;

        bool isStash(int, int);
        bool isEmpty(int, int);
        FieldInfo getFieldInfo();
        bool isWall(int, int);
        char checkWallState(int, int);
        int getEnemiesCount();
        void setEnemiesCount(int);
        GoldCoordinates getGoldCoordinates();
        void drawField(int, int, std::string);
        void drawField(int, int, int);
        void drawEndGame(int);
        void drawHelp();
        void testDraw();
        char * gameStatsTime_;
        char * gameStatsKills_;
        char * gameStatsLeft_;

    protected:

    private:
        FieldInfo fieldInfo_;
        int maxEnemies_;
        int enemiesCount_;
        GoldCoordinates goldCoordinates_;
        CursorController * cursorController_;
        void generateLevel();

        const int maxHeight_ = 60;
        const int maxWidth_ = 210;
        const int minHeight_ = 20;
        const int minWidth_ = 10;
        const int leftUpperCornerX_ = 0;
        const int leftUpperCornerY_ = 3;

};

#endif // FIELD_H
