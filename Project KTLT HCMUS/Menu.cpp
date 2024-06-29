#include "myLib.h"

std::string getConsoleLine(int x, int y, int width) {
    const int MAX_BUFFER_SIZE = 200;
    CHAR_INFO buffer[MAX_BUFFER_SIZE];
    if (width > MAX_BUFFER_SIZE) width = MAX_BUFFER_SIZE;
    COORD bufferSize = { static_cast<SHORT>(width), 1 };
    COORD bufferCoord = { 0, 0 };
    SMALL_RECT readRegion = { static_cast<SHORT>(x), static_cast<SHORT>(y), static_cast<SHORT>(x + width - 1), static_cast<SHORT>(y) };

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ReadConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &readRegion);

    std::string line;
    for (int i = 0; i < width; i++) {
        line += buffer[i].Char.AsciiChar;
    }

    return line;
}


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
    gotoXY(WIDTH_CONSOLE / 2 - 32, HEIGHT_CONSOLE - 1);
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

void paintColor(int x, int y, int width, int height, int color) {
    setBackgroundColor(color);
    for (int i = x; i <= x + width; i++)
    {
        for (int j = y; j <= y + height; j++)
        {
            gotoXY(i, j); cout << " ";
        }
    }
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
            setTextColor(purple); print("Picture\\3T6H3N.txt", WIDTH_CONSOLE / 2 - 58, 1);
            setTextColor(aqua); print("Picture\\U.txt", 10, 10); print("Picture\\S.txt", WIDTH_CONSOLE - 20, 10);
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
                else if (newY == y + 2 * (height + dis))
                {
                    menuAboutUs();
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
    setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions(); printMovingInstructionsAddTab();
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
                return;
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
    setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions(); printMovingInstructionsAddTab();
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
            if (choose == 27)
            {
                printTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE / 2 + 7, "Cancel login!");
                return;
            }
            else if (choose == 13)
            {
                drawInputLogin(x, y);
                if (newX == x)
                {
                    staffLogIn(lstStaff, listOfSY, listOfCourse, x + 5, y + 5);
                    return;
                }
                else if (newX == x + newWidth + dis)
                {
                    studentLogIn(lstStudent, listOfCourse, x + 5, y + 5);
                    return;
                }
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

void drawLineByX(int x, int y, int width)
{
    for (int i = 1; i < width; i++)
    {
        gotoXY(x + i, y);
        cout << (char)196;
    }

    gotoXY(x, y); cout << (char)199;
    gotoXY(x + width, y); cout << (char)182;
}

void drawInputLogin(int x, int y)
{
    gotoXY(x + 5, y + 5); cout << "Username: "; drawBox(x + 5 + strlen("Username: "), y + 4, 50 - strlen("Username: "), 2);
    gotoXY(x + 5, y + 8); cout << "Password: "; drawBox(x + 5 + strlen("Password: "), y + 7, 50 - strlen("Password: "), 2);
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

void printTextAtXY(int x, int y, std::string str)
{
    setTextColor(yellow);
    for (int i = 0; i < str.length(); i++) {
        gotoXY(x - str.length() / 2 + i, y);
        cout << str[i];
        Sleep(40);
    }
    Sleep(800);
    setTextColor(black);
}

void deleteTextAtXY(int x, int y, std::string str)
{
    for (int i = 0; i < str.length(); i++) {
        gotoXY(x - str.length() / 2 + i, y);
        cout << " ";
    }
}

void printMovingInstructionsAddTab()
{
    gotoXY(WIDTH_CONSOLE / 2 - 28, HEIGHT_CONSOLE);
    cout << "     Press 'tab' to move next box and 'esc' to return     ";
}

void menuChangePassword(int& x, int& y)
{
    system("cls");
    setTextColor(lblue); print("Picture\\Change Password.txt", WIDTH_CONSOLE / 2 - 35, 2);
    setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions(); printMovingInstructionsAddTab();
    setBackgroundColor(lwhite);

    x = WIDTH_CONSOLE / 2 - 40, y = HEIGHT_CONSOLE / 2 - 5;
    int height = 13, width = 80;
    setTextColor(green); printTwoLine(x, y - 1, height, width);
    setTextColor(black);
    gotoXY(x + 2, y + 2); cout << "Input old password: "; drawBox(x + 2 + strlen("Input old password: "), y + 1, 75 - strlen("Input old password: "), 2);
    gotoXY(x + 2, y + 5); cout << "Input new password: "; drawBox(x + 2 + strlen("Input new password: "), y + 4, 75 - strlen("Input new password: "), 2);
    gotoXY(x + 2, y + 8); cout << "Confirm new password: "; drawBox(x + 2 + strlen("Confirm new password: "), y + 7, 75 - strlen("Confirm new password: "), 2);
    x += 2, y += 2;
}

void deleteMenu(int x, int y, int height, int width)
{
    string str;
    for (int i = 1; i <= width; i++)
        str += ' ';
    for (int i = y; i <= y + height; i++)
    {
        gotoXY(x, i);
        cout << str;
    }
}

void menuClassOfStudent(int x, int y, int height, int width)
{
    setBackgroundColor(laqua);
    deleteMenu(x, y, height, width);
    setTextColor(blue); printTwoLine(x, y, height, width);

    drawLineByX(x, y + 2, width);
    drawLineByX(x, y + height - 2, width);

    setTextColor(purple);
    gotoXY(x + 1, y + 1); cout << "No";
    gotoXY(x + 6, y + 1); cout << "ID";
    gotoXY(x + 21, y + 1); cout << "Fullname";
    gotoXY(x + 51, y + 1); cout << "Gender";
    gotoXY(x + 61, y + 1); cout << "Date Of Birth";
    gotoXY(x + 81, y + 1); cout << "ID Social";
}

//void viewClassOfStudent()
//{
//    setTextColor(green); print("List.txt", WIDTH_CONSOLE / 2 - 12, 1);
//    int x = WIDTH_CONSOLE / 2 - 50, y = 8, height = 17, width = 100;
//    int Sum = 20;
//    int total, page = 1;
//    if (Sum % 12 == 0)
//        total = Sum / 12;
//    else
//        total = Sum / 12 + 1;
//    int New = 0, Old = 0;
//    string str = "     Use left and right keys to change pages !!!    ";
//    setBackgroundColor(lyellow); setTextColor(red); gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE - 1);
//    cout << str;
//    setBackgroundColor(lwhite);
//
//    menuClassOfStudent(x, y, height, width);
//    viewStudent((page - 1) * 12 + 1, page * 12, x, y);
//    str = "Page: " + to_string(page) + "/" + to_string(total);
//    setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 99);
//    setBackgroundColor(laqua);
//    setTextColor(purple); gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;
//    while (true)
//    {
//        char ch = _getch();
//        if (ch == -32) {
//            ch = _getch();
//            if (ch == 72 && New > 0) {
//                New--;
//            }
//            else if (ch == 80) {
//                if (page < total && New < 11)
//                    New++;
//                else if (page == total && New < Sum - (total - 1) * 12 - 1)
//                    New++;
//            }
//            else if (ch == 75 && page > 1) {
//                New = 0;
//                page--;
//                menuClassOfStudent(x, y, height, width);
//                viewStudent((page - 1) * 12 + 1, page * 12, x, y);
//                str = "Page: " + to_string(page) + "/" + to_string(total);
//                setTextColor(purple); gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;
//            }
//            else if (ch == 77 && page < total) {
//                New = 0;
//                page++;
//                menuClassOfStudent(x, y, height, width);
//                if (page != total)
//                    viewStudent((page - 1) * 12 + 1, page * 12, x, y);
//                else
//                    viewStudent((page - 1) * 12 + 1, Sum, x, y);
//                str = "Page: " + to_string(page) + "/" + to_string(total);
//                setTextColor(purple); gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;
//            }
//            else
//                continue;
//
//            gotoXY(x + 1, y + 3 + Old); setTextColor(black); cout << getConsoleLine(x + 1, y + 3 + Old, 99);
//            setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 99);
//            setBackgroundColor(laqua);
//            Old = New;
//        }
//    }
//}

void menuBoxViewCoursesForStudent(int x, int y, int height, int width)
{
    setBackgroundColor(laqua);
    deleteMenu(x, y, height, width);
    setTextColor(blue); printTwoLine(x, y, height, width);
    drawLineByX(x, y + 2, width);

    drawLineByX(x, y + height - 2, width);

    setTextColor(purple);
    gotoXY(x + 1, y + 1); cout << "No";
    gotoXY(x + 5, y + 1); cout << "IDCourse";
    gotoXY(x + 16, y + 1); cout << "Classname";
    gotoXY(x + 27, y + 1); cout << "Coursename";
    gotoXY(x + 52, y + 1); cout << "Teacher";
    gotoXY(x + 79, y + 1); cout << "Credits";
    gotoXY(x + 88, y + 1); cout << "Day of week";
}

void menuViewOfStudent(nodeStudent* Student)
{
    int x = WIDTH_CONSOLE / 2 - 50, y = HEIGHT_CONSOLE / 2 - 6;
    int width = 26, height = 2;
    int nBox = 3, dis = 2;

    int newX = x + 12, newY = y + 2;
    int oldX = newX, oldY = newY;
    bool check = true;
    int count = 0;
    while (true)
    {
        if (count == 0)
        {
            setBackgroundColor(lwhite);
            system("cls");
            std::string str = Student->student.info.lastName + " " + Student->student.info.firstName;
            setTextColor(blue); gotoXY(1, 0); cout << "Username: " << Student->student.account.userName;
            gotoXY(1, 1); cout << "Fullname: " << str;
            setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
            setBackgroundColor(lwhite); setTextColor(green); printTwoLine(x, y, 14, 50);
            setTextColor(lpurple); print("Picture\\View Student.txt", WIDTH_CONSOLE / 2 - 28, 1);

            string* option = new string[nBox];
            option[0] = "View courses";
            option[1] = "View score";
            option[2] = "Exit";
            setTextColor(black); drawNBoxByY(x + 12, y + 2, width, height, nBox, dis, option);
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
                if (newY == y + 2)
                {
                    Sleep(100);
                    viewOfStudent(Student, x + 60, y, 1);
                    count = 0;
                }
                else if (newY == y + 2 + height + dis)
                {
                    Sleep(100);
                    viewOfStudent(Student, x + 60, y, 2);
                    count = 0;
                }
                else if (newY == y + 2 + 2 * (height + dis))
                {
                    printTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE - 3, "Thanks you !!!");
                    return;
                }
            }
            else if (choose == -32)
            {
                choose = _getch();
                if (choose == 72 && newY > y + 2) 
                    newY = newY - height - dis;
                else if (choose == 80 && newY < y + 2 + (nBox - 1) * (height + dis))
                    newY = newY + height + dis;
            }

            check = true;
        }
    }
}

void menuBoxViewScoresForStudent(int x, int y, int height, int width)
{
    setBackgroundColor(laqua);
    deleteMenu(x, y, height, width);
    setTextColor(blue); printTwoLine(x, y, height, width);
    drawLineByX(x, y + 2, width);

    drawLineByX(x, y + height - 2, width);

    setTextColor(purple);
    gotoXY(x + 1, y + 1); cout << "No";
    gotoXY(x + 10, y + 1); cout << "Coursename";
    gotoXY(x + 45, y + 1); cout << "Classname";
    gotoXY(x + 60, y + 1); cout << "Other";
    gotoXY(x + 70, y + 1); cout << "Midterm";
    gotoXY(x + 80, y + 1); cout << "Final";
    gotoXY(x + 90, y + 1); cout << "Total";
}

void menuSchoolYearForStaff(nodeStaff* staff)
{
    int x = WIDTH_CONSOLE / 2 - 50, y = HEIGHT_CONSOLE / 2 - 8;
    int width = 30, height = 2;
    int nBox = 3, dis = 1;

    int newX = x + 5, newY = y + 1;
    int oldX = newX, oldY = newY;

    int cnt = 0;
    bool check = true;
    while (true)
    {
        if (cnt == 0)
        {
            system("cls");
            setTextColor(purple); print("Picture\\School Year.txt", WIDTH_CONSOLE / 2 - 25, 1);
            setTextColor(aqua); print("Picture\\FIT.txt", 20, 18);
            setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
            setBackgroundColor(lwhite);
            setTextColor(green); printTwoLine(x, y, 10, 40);

            string* option = new string[nBox];
            option[0] = "Create School Year";
            option[1] = "View School Year";
            option[2] = "Create Semester";
            setTextColor(black); drawNBoxByY(x + 5, y + 1, width, height, nBox, dis, option);
            delete[] option;

            cnt++;
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
            if (choose == 27)
            {
                return;
            }
            else if (choose == 13)
            {
                if (newY == y + 1)
                {
                    createSchoolYear(listOfSY, x + 55, y);
                }
                else if (newY == y + 1 + height + dis)
                {
                    viewSchoolYearForStaff(x + 55, y);
                }
                else if (newY == y + 1 + 2 * (height + dis))
                {
                    createSemester(x + 55, y);
                }

                cnt = 0;
            }
            else if (choose == -32)
            {
                choose = _getch();
                if (choose == 72 && newY > y + 1)
                    newY = newY - height - dis;
                else if (choose == 80 && newY < y + 1 + (nBox - 1) * (height + dis))
                    newY = newY + height + dis;
            }

            check = true;
        }
    }
}

void menuClassForStaff(nodeStaff* staff)
{
    int x = WIDTH_CONSOLE / 2 - 50, y = HEIGHT_CONSOLE / 2 - 8;
    int width = 20, height = 2;
    int nBox = 2, dis = 1;

    int newX = x + 10, newY = y + 1;
    int oldX = newX, oldY = newY;

    int cnt = 0;
    bool check = true;
    while (true)
    {
        if (cnt == 0)
        {
            system("cls");
            setTextColor(purple); print("Picture\\Class.txt", WIDTH_CONSOLE / 2 - 5, 1);
            setTextColor(aqua); print("Picture\\FIT.txt", 20, 15);
            setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
            setBackgroundColor(lwhite);
            setTextColor(green); printTwoLine(x, y, 7, 40);

            string* option = new string[nBox];
            option[0] = "Create Class";
            option[1] = "View Classes";
            setTextColor(black); drawNBoxByY(x + 10, y + 1, width, height, nBox, dis, option);
            delete[] option;

            cnt++;
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
            if (choose == 27)
                return;
            else if (choose == 13)
            {
                int tempx = x + 50, tempy = y;
                nodeSchoolYear* schoolYearNow = goToSchoolYear(listOfSY, tempx, tempy);
                deleteMenu(x + 50, y, 15, 50);
                if (newY == y + 1)
                {
                    createClass(schoolYearNow, schoolYearNow->y.listOfClass, x + 45, y);
                }
                else if (newY == y + 1 + height + dis)
                {
                    /*listClass listClass;
                    listClass.head = NULL;
                    string fileName = "./dataSchoolYear/Class_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + ".txt";
                    readFileListClass(listClass, fileName);*/

                   
                }

                cnt = 0;
            }
            else if (choose == -32)
            {
                choose = _getch();
                if (choose == 72 && newY > y + 1)
                    newY = newY - height - dis;
                else if (choose == 80 && newY < y + 1 + (nBox - 1) * (height + dis))
                    newY = newY + height + dis;
            }

            check = true;
        }
    }
}

void menuCourseForStaff(nodeStaff* staff)
{
    int x = WIDTH_CONSOLE / 2 - 50, y = HEIGHT_CONSOLE / 2 - 8;
    int nBox = 2, height = 2, width = 20, dis = 1;
    int newX = x + 10, newY = y + 1;
    int oldX = newX, oldY = newY;

    int cnt = 0;
    bool check = true;
    while (true)
    {
        if (cnt == 0) {
            system("cls");
            setTextColor(purple); print("Picture\\Course.txt", WIDTH_CONSOLE / 2 - 10, 1);
            setTextColor(aqua); print("Picture\\FIT.txt", 20, 15);
            setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
            setBackgroundColor(lwhite);
            setTextColor(green); printTwoLine(x, y, 7, 40);
            setTextColor(black);

            string* option = new string[nBox];
            option[0] = "Create Course";
            option[1] = "View Courses";
            drawNBoxByY(x + 10, y + 1, width, height, nBox, dis, option);
            delete[] option;

            cnt++;
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
            char ch = _getch();
            if (ch == 27)
            {
                deleteMenu(x, y, height, width);
                break;
            }
            else if (ch == 13)
            {
                int tempX = x + 50, tempY = y;
                nodeSchoolYear* schoolYearNow = goToSchoolYear(listOfSY, tempX, tempY);
                int optn;

                setTextColor(blue); gotoXY(tempX, tempY); cout << "Input semester (1, 2, 3): ";
                ShowCur(1); setTextColor(black);
                do
                {
                    gotoXY(tempX + strlen("Input semester (1, 2, 3): "), tempY); cout << "         ";
                    gotoXY(tempX + strlen("Input semester (1, 2, 3): "), tempY); cin >> optn;
                } while (optn > 3 || optn < 1);
                ShowCur(0);
                Semester semesterNow = schoolYearNow->y.listSemester[optn - 1];

                if (newY == y + 1)
                {
                    if (schoolYearNow->y.listSemester[optn - 1].NO == 0)
                    {
                        printTextAtXY(x + 50 + 45 / 2, tempY + 1, "This semester hasn't been initialized !!!");
                        string str = "Press any key to continue";
                        setTextColor(red); gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, HEIGHT_CONSOLE - 3); cout << str;
                        ch = _getch();
                        deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE - 3, str);
                        deleteMenu(x + 49, y, 12, 52);
                        setTextColor(black);
                        continue;
                    }
                    listOfCourse.head = NULL;
                    string fileName = "dataSemester\\Course_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(optn);
                    readCourseFile(listOfCourse, fileName);
                    createNewCourseForStaff(listOfCourse,schoolYearNow, semesterNow);
                    deleteAllCourse(listOfCourse);
                    listOfCourse.head = NULL;
                }
                else if (newY == y + 1 + height + dis)
                {
                    nodeCourse* courseNow = goToCourse(semesterNow.listCourse);
                    if (courseNow == NULL)
                    {
                        cnt = 0;
                        check = true;
                        continue;
                    }
                    if (semesterNow.listCourse.head == NULL)
                    {
                        break;
                    }
                    listStudent listStudentOfCourseNow;
                    string fileListStudent = "./dataCourse/" + courseNow->crs.info.courseName + "_" + courseNow->crs.info.className + "_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(semesterNow.NO) + ".txt";
                    readListStudentOfACourse(listStudentOfCourseNow, fileListStudent);
                    menuViewListCourses(listStudentOfCourseNow, schoolYearNow, semesterNow, courseNow);
                }

                cnt = 0;
            }
            else if (ch == -32)
            {
                ch = _getch();
                if (ch == 72 && newY > y + 1)
                    newY = newY - height - dis;
                else if (ch == 80 && newY < y + 1 + (nBox - 1) * (height + dis))
                    newY = newY + height + dis;
            }

            check = true;
        }
    }
}

void menuViewStudentForStaff(int x, int y, int height, int width)
{
    setBackgroundColor(laqua);
    deleteMenu(x, y, height, width);
    setTextColor(blue); printTwoLine(x, y, height, width);
    drawLineByX(x, y + 2, width);

    drawLineByX(x, y + height - 2, width);

    setTextColor(purple);
    gotoXY(x + 1, y + 1); cout << "No";
    gotoXY(x + 5, y + 1); cout << "ID Student";
    gotoXY(x + 20, y + 1); cout << "Last Name";
    gotoXY(x + 45, y + 1); cout << "First Name";
}

void menuViewListCourses(listStudent& lst, nodeSchoolYear*& schoolYearNow, Semester& semesterNow, nodeCourse* courseNow)
{
    int x = WIDTH_CONSOLE / 2 - 40, y = HEIGHT_CONSOLE / 2 - 8;
    int width = 50, height = 2;
    int nBox = 7, dis = 0;

    int newX = x + 15, newY = y + 2;
    int oldX = newX, oldY = newY;

    bool check = true;
    int cnt = 0;
    while (true)
    {
        if (cnt == 0)
        {
            system("cls");
            setTextColor(purple); print("Picture\\View Course.txt", WIDTH_CONSOLE / 2 - 25, 1);
            setBackgroundColor(lyellow); setTextColor(red); printMovingInstructions();
            setBackgroundColor(lwhite);
            setTextColor(green); printTwoLine(x, y, 18, 80);

            string* option = new string[nBox];
            option[0] = "View List Student In Course";
            option[1] = "Add N Student To Course By CSV";
            option[2] = "Update Info Course";
            option[3] = "Delete A Course";
            option[4] = "Delete A Student";
            option[5] = "Export File CSV";
            option[6] = "Import Scoreboard";
            setTextColor(black); drawNBoxByY(x + 15, y + 2, width, height, nBox, dis, option);
            delete[] option;

            for (int i = 1; i <= 6; i++)
            {
                gotoXY(x + 15, y + 2 + i * height); cout << (char)195;
                gotoXY(x + 15 + width, y + 2 + i * height); cout << (char)180;
            }

            cnt++;
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
            if (choose == 27)
            {
                return;
            }
            else if (choose == 13)
            {
                if (newY == y + 2)
                    viewStudentForStaff(lst);
                else if (newY == y + 2 + height + dis)
                {
                    system("cls");
                    string fileName;
                    setTextColor(blue); gotoXY(WIDTH_CONSOLE / 2 - 40, 9); cout << "Input file name: ";
                    setTextColor(green); drawBox(WIDTH_CONSOLE / 2 - 40 + strlen("Input file name: "), 8, 60, 2);
                    setTextColor(black);
                    ShowCur(1); gotoXY(WIDTH_CONSOLE / 2 - 40 + strlen("Input file name: ") + 1, 9);
                    cin.ignore();
                    getline(cin, fileName);
                    ShowCur(0);
                    addNStudentFromFileForStaff(schoolYearNow, semesterNow, courseNow, fileName);
                }
                else if (newY == y + 2 + 2 * (height + dis))
                {
                    updateCourse(schoolYearNow, semesterNow, courseNow);
                }
                else if (newY == y + 2 + 3 * (height + dis))
                {
                    deleteACourse(schoolYearNow, semesterNow, semesterNow.listCourse, courseNow);
                    deleteNodeCourse(semesterNow.listCourse, courseNow);
                    return;
                }
                else if (newY == y + 2 + 4 * (height + dis))
                {
                    deleteAStudentFromCourse(schoolYearNow, semesterNow, courseNow, NULL);
                }
                else if (newY == y + 2 + 5 * (height + dis))
                {
                    system("cls");
                    string address;
                    setTextColor(blue); gotoXY(WIDTH_CONSOLE / 2 - 40, 9); cout << "Input address: ";
                    setTextColor(green); drawBox(WIDTH_CONSOLE / 2 - 40 + strlen("Input address: "), 8, 65, 2);
                    setTextColor(black);
                    ShowCur(1); gotoXY(WIDTH_CONSOLE / 2 - 40 + strlen("Input address: ") + 1, 9);
                    cin.ignore();
                    getline(cin, address);
                    ShowCur(0);
                    exportCSVFile(schoolYearNow, semesterNow, address, courseNow);
                }
                else if (newY == y + 2 + 6 * (height + dis))
                {
                    system("cls");
                    string fileName;
                    setTextColor(blue); gotoXY(WIDTH_CONSOLE / 2 - 40, 9); cout << "Input file name: ";
                    setTextColor(green); drawBox(WIDTH_CONSOLE / 2 - 40 + strlen("Input file name: "), 8, 60, 2);
                    setTextColor(black);
                    ShowCur(1); gotoXY(WIDTH_CONSOLE / 2 - 40 + strlen("Input file name: ") + 1, 9);
                    cin.ignore();
                    getline(cin, fileName);
                    ShowCur(0);
                    importScoreBoard(schoolYearNow, semesterNow, courseNow, fileName);
                    checkScore = true;
                }

                cnt = 0;
            }
            else if (choose == -32)
            {
                choose = _getch();
                if (choose == 72 && newY > y + 2)
                    newY = newY - height - dis;
                else if (choose == 80 && newY < y + 2 + (nBox - 1) * (height + dis))
                    newY = newY + height + dis;
            }

            check = true;
        }
    }
}

void menuViewChooseCourses(int x, int y, int height, int width)
{
    setBackgroundColor(laqua);
    deleteMenu(x, y, height, width);
    setTextColor(blue); printTwoLine(x, y, height, width);
    drawLineByX(x, y + 2, width);

    drawLineByX(x, y + height - 2, width);

    setTextColor(purple);
    gotoXY(x + 1, y + 1); cout << "No";
    gotoXY(x + 5, y + 1); cout << "Course Name";
    gotoXY(x + 35, y + 1); cout << "Teacher Name";
    gotoXY(x + 65, y + 1); cout << "Class Name";
}

void ViewChooseCourses(listCourse lst, int start, int end, int x, int y)
{
    setTextColor(red);
    if (end == 0)
    {
        gotoXY(WIDTH_CONSOLE / 2 - 30, y + 3); cout << "No data !!!";
        return;
    }

    setTextColor(black);
    int index = 0, i = 1;
    nodeCourse* temp = lst.head;
    while (temp != NULL)
    {
        if (i == start)
            break;
        i++;
        temp = temp->Next;
    }

    while (temp != NULL)
    {
        if (i == end + 1)
            break;
        gotoXY(x + 1, y + 3 + index); cout << i;
        gotoXY(x + 5, y + 3 + index); cout << temp->crs.info.courseName;
        gotoXY(x + 35, y + 3 + index); cout << temp->crs.info.teacherName;
        gotoXY(x + 65, y + 3 + index); cout << temp->crs.info.className;

        temp = temp->Next;
        index++; i++;
    }
}

void printText(int x, int y, string str)
{
    gotoXY(x, y);
    for (int i = 0; i < str.length(); i++)
    {
        gotoXY(x + i, y); cout << str[i];
        Sleep(30);
    }
}

void menuAboutUs()
{
    system("cls");
    Sleep(200);
    setTextColor(aqua); printText(WIDTH_CONSOLE / 2 - strlen("Meet Our Awesome Team - 3T6H3N") / 2, 2, "Meet Our Awesome Team - 3T6H3N");
    Sleep(400);
    setTextColor(blue); printText(WIDTH_CONSOLE / 2 - strlen("We are a tight-knit trio, working together to create magic !!!") / 2, 4, "We are a tight-knit trio, working together to create magic !!!");
    Sleep(400);
    setTextColor(red);
    string str = "Project: Course management.";
    printText(10, 6, str);
    str = "Teacher: Nguyen Le Hoang Dung.";
    printText(10, 7, str);
    Sleep(400);

    setTextColor(green);
    str = "Member:";
    Sleep(400);
    printText(10, 10, str);
    setTextColor(black);
    str = "- Le Nhat Thanh (ID Student: 23120357): He's our creative genius. He's good at debugging and bring";
    printText(15, 11, str);
    str = "fresh ideas to our projects.";
    printText(17, 12, str);
    Sleep(400);
    str = "- Nguyen Tien Thanh (ID: 23120358): He is our coding virtuoso. Almost every function in our project owes";
    printText(15, 13, str);
    str = "its excellence to his skillful coding.";
    printText(17, 14, str);
    Sleep(400);
    str = "- Dang Le Duc Thinh (ID: 23120360): He is our console maestro. They've crafted the frontend, ensuring a";
    printText(15, 15, str);
    str = "seamless user experience.";
    printText(17, 16, str);
    Sleep(400);

    str = "During the time we worked together, our project didn't always go the way we wanted. However, thanks to our";
    printText(10, 19, str);
    str = "patience and determination, we managed to fix it, and we never gave up. On behalf of my team, I want to";
    printText(10, 20, str);
    str = "express my gratitude to HCMUS for giving us the chance to work on this project.";
    printText(10, 21, str);
    Sleep(800);

    setTextColor(red);
    str = "Thank you, 3T6H3N team, for your outstanding work! We appreciate your support !!!";
    printTextAtXY(WIDTH_CONSOLE / 2, 24, str);
    str = "Thank you for using our app!";
    printTextAtXY(WIDTH_CONSOLE / 2, 25, str);
    char ch = _getch();
}