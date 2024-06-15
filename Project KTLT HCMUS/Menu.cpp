#include "myLib.h"

void ShowCur(bool showCursor) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showCursor;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void setBackgroundColor(int bg) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, (consoleInfo.wAttributes & 0xFF0F) | (bg << 4));
}

void setTextColor(int text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, (consoleInfo.wAttributes & 0xFFF0) | text);
}

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print(const char* fileName, int x, int y) {
    ifstream file(fileName);
    string line;
    int i = 0;
    while (getline(file, line)) {
        gotoXY(x, y + i++);
        cout << line << endl;
    }
    file.close();
}

void printTwoLine(int x, int y, int height, int width)
{
    for (int i = x; i <= x + width; i++)
    {
        gotoXY(i, y); cout << (char)205;
        gotoXY(i, y + height); cout << (char)205;
    }
    for (int i = y; i <= y + height; i++)
    {
        gotoXY(x, i); cout << (char)186;
        gotoXY(x + width, i); cout << (char)186;
    }
    gotoXY(x, y); cout << (char)201;
    gotoXY(x, y + height); cout << (char)200;
    gotoXY(x + width, y); cout << (char)187;
    gotoXY(x + width, y + height); cout << (char)188;
}

void focus(int x, int y, int width, char c)
{
    gotoXY(x + width - 1, y + 1); cout << c;
}

void drawBoxAndText(int x, int y, int width, int height, string option)
{

    for (int i = x + 1; i < x + width; i++)
    {
        gotoXY(i, y);
        std::cout << (char)196;
        gotoXY(i, y + height);
        std::cout << (char)196;
    }

    for (int j = y + 1; j < y + height; j++)
    {
        gotoXY(x, j);
        std::cout << (char)179;
        gotoXY(x + width, j);
        std::cout << (char)179;
    }

    gotoXY(x, y); std::cout << (char)218;
    gotoXY(x + width, y); std::cout << (char)191;
    gotoXY(x, y + height); std::cout << (char)192;
    gotoXY(x + width, y + height); std::cout << (char)217;
    gotoXY(x + (width - option.length()) / 2 + 1, y + 1); std::cout << option;
}

void drawBox(int x, int y, int width, int height)
{

    for (int i = x + 1; i < x + width; i++)
    {
        gotoXY(i, y);
        std::cout << (char)196;
        gotoXY(i, y + height);
        std::cout << (char)196;
    }

    for (int j = y + 1; j < y + height; j++)
    {
        gotoXY(x, j);
        std::cout << (char)179;
        gotoXY(x + width, j);
        std::cout << (char)179;
    }

    gotoXY(x, y); std::cout << (char)218;
    gotoXY(x + width, y); std::cout << (char)191;
    gotoXY(x, y + height); std::cout << (char)192;
    gotoXY(x + width, y + height); std::cout << (char)217;
}

void printMovingInstructions()
{
    gotoXY(WIDTH_CONSOLE / 2 - 38, HEIGHT_CONSOLE - 1);
    cout << "          Use arrow keys to move, Press 'Enter' to select          ";
}

void drawNBoxByX(int x, int y, int width, int height, int nBox, int dis, std::string* option)
{
    for (int i = 0; i < nBox; i++)
        drawBoxAndText(x + i * (width + dis), y, width, height, option[i]);
}

void drawNBoxByY(int x, int y, int width, int height, int nBox, int dis, std::string* option)
{
    for (int i = 0; i < nBox; i++)
        drawBoxAndText(x, y + i * (height + dis), width, height, option[i]);
}

void menuMain()
{
    ShowCur(0);
    int x = WIDTH_CONSOLE / 2 - 30 + 15, y = HEIGHT_CONSOLE / 2 - 6 + 1, width = 30, height = 2;
    int newX = x, newY = y;
    int oldX = x, oldY = y;
    int nBox = 4, dis = 2;

    bool check = true;
    int count = 0;
    while (true)
    {
        if (count == 0)
        {
            setBackgroundColor(lwhite);
            system("cls");
            setTextColor(aqua); print("Picture\\3T6H3N.txt", WIDTH_CONSOLE / 2 - 58, 1);
            setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
            setBackgroundColor(lwhite); setTextColor(green); printTwoLine(WIDTH_CONSOLE / 2 - 30, HEIGHT_CONSOLE / 2 - 7, 18, 60);

            string* option = new string[nBox];
            option[0] = "Register";
            option[1] = "Login";
            option[2] = "Information About Us";
            option[3] = "Quit";
            setTextColor(black); drawNBoxByY(x, y, width, height, nBox, dis, option);
            delete[] option;

            count++;
        }
        if (check == true)
        {
            gotoXY(oldX, oldY);
            focus(oldX, oldY, width, ' ');
            oldX = newX, oldY = newY;

            focus(newX, newY, width, (char)174);
            check = false;
        }
        if (_kbhit())
        {
            char choose = _getch();
            if (choose == 13)
            {
                if (newY == y)
                {
                    Sleep(100);
                    menuRegister();
                    count = 0;
                }
                else if (newY == y + height + dis)
                {
                    Sleep(100);
                    menuLogIn();
                    count = 0;
                }
                else if (newY == y + 3 * (height + dis))
                {
                    Sleep(100);
                    system("cls");
                    return;
                }
            }
            else if (choose == -32)
            {
                choose = _getch();
                if (choose == 72 && newY > y)
                    newY = newY - height - dis;
                else if (choose == 80 && newY < y + (nBox - 1) * (height + dis))
                    newY = newY + height + dis;
            }

            check = true;
        }
    }
}

void menuRegister()
{
    system("cls");
    setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions(); printMovingInstructionsInRegister();
    setBackgroundColor(lwhite);
    setTextColor(blue); print("Picture\\Register.txt", WIDTH_CONSOLE / 2 - 23, 1);
    int x = WIDTH_CONSOLE / 2 - 50, y = HEIGHT_CONSOLE / 2 - 9, height = 19, width = 100;
    setTextColor(green); printTwoLine(x, y, height, width);
    setTextColor(black);

    int newX = x + 5, newY = y + 3;
    int oldX = newX, oldY = newY;
    int newWidth = 20, newHeight = 2;
    int nBox = 2, dis = 2;
    string* option = new string[nBox];
    option[0] = "Staff";
    option[1] = "Student";
    drawNBoxByY(newX, newY, newWidth, newHeight, nBox, dis, option);
    delete[] option;

    bool check = true;
    while (true)
    {
        if (check == true)
        {
            gotoXY(oldX, oldY);
            focus(oldX, oldY, newWidth, ' ');
            oldX = newX, oldY = newY;

            focus(newX, newY, newWidth, (char)174);
            check = false;
        }
        if (_kbhit())
        {
            char choose = _getch();
            if (choose == 27)
            {
                printAtXY(x, y, "Cancel registration!");
                return;
            }
            else if (choose == 13)
            {
                if (newY == y + 3)
                {
                    setTextColor(green); drawLineByY(x + 30, y, height);
                    setTextColor(black);
                    staffRegister(lstStaff, "accountStaff.txt", x + 30, y);
                    setTextColor(black);
                    return;
                }
                else if (newY == y + 3 + newHeight + dis)
                {
                    setTextColor(green); drawLineByY(x + 30, y, height);
                    setTextColor(black);
                    studentRegister(lstStudent, "accountStudent.txt", x + 30, y);
                    setTextColor(black);
                    return;
                }
            }
            else if (choose == -32)
            {
                choose = _getch();
                if (choose == 72 && newY > y + 3)
                    newY = newY - newHeight - dis;
                else if (choose == 80 && newY < y + 3 + (nBox - 1) * (newHeight + dis))
                    newY = newY + newHeight + dis;
            }

            check = true;
        }
    }
}

void menuLogIn()
{
    system("cls");
    setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
    setBackgroundColor(lwhite);
    int x = WIDTH_CONSOLE / 2 - 40, y = HEIGHT_CONSOLE / 2 - 6, height = 15, width = 80;
    setTextColor(purple); print("Picture\\LogIn.txt", WIDTH_CONSOLE / 2 - 23, 1);
    setTextColor(green); printTwoLine(x, y, height, width);
    setTextColor(black);
    x = x + 10, y = y + 2;
    int newX = x, newY = y;
    int oldX = x, oldY = y;

    int newWidth = 20, newHeight = 2;
    int nBox = 2, dis = 20;
    string* option = new string[nBox];
    option[0] = "Staff";
    option[1] = "Student";
    drawNBoxByX(newX, newY, newWidth, newHeight, nBox, dis, option);
    delete[] option;

    bool check = true;
    while (true)
    {
        if (check == true)
        {
            gotoXY(oldX, oldY);
            focus(oldX, oldY, newWidth, ' ');
            oldX = newX, oldY = newY;

            focus(newX, newY, newWidth, (char)174);
            check = false;
        }
        if (_kbhit())
        {
            char choose = _getch();
            if (choose == 13)
            {
                inputLogin(x, y);
                return;
            }
            else if (choose == -32)
            {
                choose = _getch();
                if (choose == 77 && newX < x + (nBox - 1) * (dis + newWidth))
                    newX = newX + newWidth + dis;
                else if (choose == 75 && newX > x)
                    newX = newX - newWidth - dis;
            }

            check = true;
        }
    }
}

void drawLineByY(int x, int y, int height)
{
    for (int i = 0; i < height; i++)
    {
        gotoXY(x, y + i);
        cout << (char)179;
    }

    gotoXY(x, y); cout << (char)209;
    gotoXY(x, y + height); cout << (char)207;
}

void inputLogin(int x, int y)
{
    string user, pass;
    ShowCur(1);
    gotoXY(x + 5, y + 5); cout << "Username: "; drawBox(x + 5 + strlen("Username: "), y + 4, 50 - strlen("Username: "), 2);
    gotoXY(x + 5, y + 8); cout << "Password: "; drawBox(x + 5 + strlen("Password: "), y + 7, 50 - strlen("Username: "), 2);
    gotoXY(x + 5 + strlen("Username: ") + 1, y + 5); cin >> user;
    if (user[0] == 'd')
    {
        string str = "Nhap sai!";
        for (int i = 0; i < str.length(); i++) {
            gotoXY(WIDTH_CONSOLE / 2 - 8 + i, HEIGHT_CONSOLE / 2 + 7);
            cout << str[i];
            Sleep(40);
        }
        Sleep(500);
        for (int i = 0; i < user.length(); i++)
        {
            gotoXY(x + 5 + strlen("Username: ") + 1 + i, y + 5);
            cout << " ";
        }

        gotoXY(x + 5 + strlen("Username: ") + 1, y + 5); cin >> user;
        for (int i = 0; i < str.length(); i++) {
            gotoXY(WIDTH_CONSOLE / 2 - 8 + i, HEIGHT_CONSOLE / 2 + 7);
            cout << " ";
        }
    }
    gotoXY(x + 5 + strlen("Password: ") + 1, y + 8); cin >> pass;
    ShowCur(0);

    string str = "Login succesful!";
    for (int i = 0; i < str.length(); i++) {
        gotoXY(WIDTH_CONSOLE / 2 - 8 + i, HEIGHT_CONSOLE / 2 + 7);
        cout << str[i];
        Sleep(40);
    }

    Sleep(500);
}

bool isValidRegisterDate(std::string date)
{
    if (date.length() == 0)
        return false;
    size_t index1 = date.find(' ');
    size_t index2 = date.find(' ', index1 + 1);
    if (index1 == string::npos || index2 == string::npos || date.find(' ', index2 + 1) != string::npos)
        return false;

    return isValidDate(stoi(date.substr(0, index1)), stoi(date.substr(index1 + 1, index2)), stoi(date.substr(index2 + 1)));
}

void printAtXY(int x, int y, std::string str)
{
    setTextColor(yellow);
    for (int i = 0; i < str.length(); i++) {
        gotoXY(x - 15 - str.length() / 2 + i, y + 17);
        cout << str[i];
        Sleep(40);
    }
    Sleep(600);
    for (int i = 0; i < str.length(); i++) {
        gotoXY(x - 15 - str.length() / 2 + i, y + 17);
        cout << " ";
    }
    setTextColor(black);
}

void printMovingInstructionsInRegister()
{
    gotoXY(WIDTH_CONSOLE / 2 - 38, HEIGHT_CONSOLE);
    cout << "     Press 'tab' to move next box and 'esc' to cancel register     ";
}