#include "myLib.h"

nodeSchoolYear* goToSchoolYear(listOfSchoolYear listSchoolYear, int& x, int& y)
{
    int i = 1;
    nodeSchoolYear* temp = listSchoolYear.head;
    if (temp == NULL)
    {
        setTextColor(red); gotoXY(x, y); std::cout << "No school year available" << std::endl;
        return NULL;
    }

    int count = 0;
    setTextColor(red);
    while (temp != NULL)
    {
        if (count < 3)
        {
            gotoXY(x + count * 20, y); std::cout << i << ". " << temp->y.startYear << "-" << temp->y.endYear;
            count++;
        }
        else
        {
            count = 0;
            y++;
        }
        temp = temp->nextYear;
        i++;
    }

    setTextColor(black);
    int imax = i;
    int optn = 0;

    setTextColor(blue); gotoXY(x, ++y); std::cout << "Select a school year: ";
    ShowCur(1); setTextColor(black);
    do
    {
        gotoXY(x + strlen("Select a school year: "), y); cout << "         ";
        gotoXY(x + strlen("Select a school year: "), y);
        std::cin >> optn;
    } while (optn > imax || optn < 0);
    ShowCur(0);

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
        n++;

    return n;
}