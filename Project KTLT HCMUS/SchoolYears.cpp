#include "myLib.h"

nodeSchoolYear* goToSchoolYear(listOfSchoolYear listSchoolYear, int& x, int& y)
{
    int n = countLine("SchoolYear.txt");
    int add = 0;
    if (n % 2 == 0)
        add = n / 2;
    else
        add = n / 2 + 1;
    setTextColor(green); printTwoLine(x, y, 5 + add, 45);
    x += 4, y += 1;
    int i = 1;
    nodeSchoolYear* temp = listSchoolYear.head;
    setTextColor(red);
    if (temp == NULL)
    {
        gotoXY(x, y); std::cout << "No school year available" << std::endl;
        return NULL;
    }

    int count = 0;
    while (temp != NULL)
    {
        if (count == 2)
        {
            count = 0;
            y++;
        }
        gotoXY(x + count * 25, y); std::cout << i << ". " << temp->y.startYear << "-" << temp->y.endYear;
        temp = temp->nextYear;
        count++;
        i++;
    }

    setTextColor(black);
    int imax = i - 1;
    int optn = 0;
    setTextColor(green); drawLineByX(x - 4, y + 1, 45);
    y += 2, x += -2;
    setTextColor(blue); gotoXY(x, y); std::cout << "Select a school year: ";
    ShowCur(1); setTextColor(black);
    do
    {
        gotoXY(x + strlen("Select a school year: "), y); cout << "         ";
        gotoXY(x + strlen("Select a school year: "), y);
        std::cin >> optn;
        ShowCur(0);
        if (optn > imax || optn <= 0)
            printTextAtXY(x - 2 + 23, y + 2, "Input invalid !!!");
        ShowCur(1);
    } while (optn > imax || optn <= 0);
    ShowCur(0);
    deleteTextAtXY(x - 2 + 23, y + 2, "Input invalid !!!");

    temp = listSchoolYear.head;
    for (int j = 1; j < optn; j++)
        temp = temp->nextYear;
    y++;
    return temp;
}

int countLine(const string fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        return 0;
    int n = 0;
    std::string line;
    while (getline(file, line))
    {
        if (line != "")
            n++;
    }

    return n;
}