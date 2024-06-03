#include "Windows.h"

void inputAtPosition(std::string& input, int x, int y)
{
    char ch;
    input.clear();

    gotoXY(x, y);
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!input.empty())
            {
                input.pop_back();
                gotoXY(x + input.length(), y);
                std::cout << ' ';
                gotoXY(x + input.length(), y);
            }
        }
        else
        {
            input.push_back(ch);
            std::cout << ch;
        }
    }
}

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