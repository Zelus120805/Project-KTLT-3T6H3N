#include "Menu.h"

void drawBox(int x, int y, int width, int height, std::string option)
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
    gotoXY(x + 1, y + 1); std::cout << option;
}

void drawNBox(int x, int y, int width, int height, int nBox, std::string* option)
{
    for (int i = 0; i < nBox; i++)
        drawBox(x, y + i * height, width, height, option[i]);

    for (int i = 1; i < nBox; i++)
    {
        gotoXY(x, y + i * height); std::cout << (char)195;
        gotoXY(x + width, y + i * height); std::cout << (char)180;
    }
}

void focus(int x, int y, int width, char c)
{
    gotoXY(x + width - 1, y + 1); std::cout << c;
}

void menuLogin(int x, int y, int width, int height, int nBox)
{
    system("cls");
    ShowCur(0);

    std::string* option = new std::string[nBox];
    option[0] = "1. Register";
    option[1] = "2. Sign in";
    option[2] = "3. Add a school year";
    option[3] = "4. Create a course";
    option[4] = "5. Quit";
    drawNBox(x, y, width, height, nBox, option);

    delete[] option;
}

void chooseOptionMenuLogin(listStudent& listST, listOfSchoolYear& listSY, listCourse& listOfCourse)
{
    int x = 40, y = 5, width = 50, height = 2, nBox = 5;
    int newX = x, newY = y;
    int oldX = x, oldY = y;
    bool check = true;
    int count = 0;
    while (true)
    {
        if (count == 0)
        {
            menuLogin(x, y, width, height, nBox);
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
                if (oldY == y)
                {
                    menuStudentRegister(40, 5, 50, 2, 8);
                    studentRegister(listST, "accountStudent.txt", x + 1, y + 1, height);
                }
                else if (oldY == y + height * 1)
                {
                    readFileStudent(listST, "accountStudent.txt");
                    studentLogIn(listST, "accountStudent.txt", listOfCourse);//Sua tham so ham LogIn de vao phien dang nhap cua user do.
                }
                else if (oldY == y + height * 2)
                {
                    operateWithSchoolYear(listSY);
                }
                else if (oldY == y + height * 3)
                {
                    createNewCourse(listOfCourse);
                }
                else if (oldY == y + height * 4)
                    return;

                count = 0;
            }
            else if (choose == -32)
            {
                choose = _getch();
                if (choose == 72 && newY > y)
                    newY -= 2;
                else if (choose == 80 && newY < y + height * (nBox - 1))
                    newY += 2;
            }

            check = true;
        }
    }
}

void menuStudentRegister(int x, int y, int width, int height, int nBox)
{
    system("cls");
    ShowCur(1);

    std::string* option = new std::string[nBox];
    option[0] = "1. Username: ";
    option[1] = "2. Password: ";
    option[2] = "3. Fullname: ";
    option[3] = "4. Gender: ";
    option[4] = "5. ID student: ";
    option[5] = "6. Date of birth (dd mm yyyy): ";
    option[6] = "7. Social ID: ";
    option[7] = "8. Class: ";

    drawNBox(x, y, width, height, nBox, option);

    delete[] option;
}