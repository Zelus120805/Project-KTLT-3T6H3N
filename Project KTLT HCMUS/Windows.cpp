#include "Windows.h"

void ShowCur(bool showCursor)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showCursor;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoXY(int x, int y)
{
    COORD coord = { };
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}