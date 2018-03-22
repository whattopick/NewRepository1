#ifndef CURSORCONTROLLER_H
#define CURSORCONTROLLER_H
#include <string>


class CursorController
{
    public:
        CursorController();
        virtual ~CursorController();
        void drawAtPlace(int, int, char);
        void drawAtPlace(int, int, std::string);
        void drawAtPlace(int, int, int);
        void hideCursor();


    protected:

    private:
};

#endif // CURSORCONTROLLER_H
