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

void createSchoolYear(listOfSchoolYear& lst, int x, int y)
{
    nodeSchoolYear* newNode = new nodeSchoolYear();
    newNode->nextYear = nullptr;
    ofstream fileSchoolYear("SchoolYear.txt", std::ios_base::app);
    if (!fileSchoolYear.is_open())
        return;

    for (int i = 0; i < 3; i++)
    {
        newNode->y.listSemester[i].NO = 0;
        newNode->y.listSemester[0].listCourse.head = NULL;
    }
    setTextColor(green); printTwoLine(x, y, 9, 42);
    setTextColor(blue);
    gotoXY(x + 3, y + 3); cout << "Input start year: "; 
    gotoXY(x + 5, y + 6); cout << "Input end year: ";
    setTextColor(black);
    drawBox(x + 3 + strlen("Input start year:"), y + 2, 20, 2);
    drawBox(x + 5 + strlen("Input end year:"), y + 5, 20, 2);
    ShowCur(1);
	char ch;
	int i = 0, curPos[2] = { 0 };
	std::string input[2];

	int newX[2] = { x + 3 + strlen("Input start year:") + 1,
					x + 5 + strlen("Input end year:") + 1 };
	int newY[2] = { y + 3, y + 6 };
	int oldX = newX[0], oldY = newY[0];

	gotoXY(oldX, oldY);
	while (true) {
		ch = _getch();

		if (ch == 27)
		{
            ShowCur(0);
            deleteMenu(x, y, 9, 45);
			return;
		}
		else if (ch == '\r')
		{
			if (input[0].length() == 4 && input[1].length() == 4)
			{
                if (stoi(input[1]) - stoi(input[0]) == 1) {
                    ShowCur(0);
                    deleteTextAtXY(x + 21, y + 8, "Input invalid !!!");
                    printTextAtXY(x + 21, y + 8, "Create school year successful !!!");
                    break;
                }
                i = 1;
			}
			else if (input[0].length() != 4)
				i = 0;
			else
				i = 1;

            ShowCur(0);
            printTextAtXY(x + 21, y + 8, "Input invalid !!!");
            ShowCur(1);

			curPos[i] = input[i].length();
			oldX = newX[i] + input[i].length();
			oldY = newY[i];
			gotoXY(oldX, oldY);
		}
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && i > 0) {
				i--;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 80 && i < 1) {
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
			else if (ch == 75 && curPos[i] > 0) {
				curPos[i]--;
				gotoXY(--oldX, oldY);
			}
			else if (ch == 77 && curPos[i] < input[i].length()) {
				curPos[i]++;
				gotoXY(++oldX, oldY);
			}
		}
		else if (ch == 9)
		{
			if (i < 1)
			{
				i++;
				oldX = newX[i] + curPos[i];
				oldY = newY[i];

				gotoXY(oldX, oldY);
			}
		}
		else if (ch == '\b' && curPos[i] > 0)
		{
			curPos[i]--;
			input[i].erase(curPos[i], 1);
			gotoXY(newX[i], oldY);
			std::cout << input[i] << " ";
			gotoXY(--oldX, oldY);
		}
		else if (ch != '\b')
		{
			input[i].insert(curPos[i], 1, ch);
			curPos[i]++;
			std::cout << input[i].substr(curPos[i] - 1);
			gotoXY(++oldX, oldY);
		}
	}

    newNode->y.startYear = stoi(input[0]);
    newNode->y.endYear = stoi(input[1]);

    if (lst.head == nullptr)
    {
        lst.head = newNode;
        fileSchoolYear << newNode->y.startYear << "-" << newNode->y.endYear << std::endl;
        return;
    }
    nodeSchoolYear* temp = lst.head;
    while (temp->nextYear != nullptr)
    {
        temp = temp->nextYear;
    }
    temp->nextYear = newNode;
    fileSchoolYear << newNode->y.startYear << "-" << newNode->y.endYear << std::endl;

    string str = "Press any key to continue";
    setTextColor(red); gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, HEIGHT_CONSOLE - 3); cout << str;
    ch = _getch();
    deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE - 3, str);
    deleteMenu(x, y, 9, 45);
    setTextColor(black);
}

void createSemester(int x, int y)
{
    int tempX = x, tempY = y;
    nodeSchoolYear* schoolYear = goToSchoolYear(listOfSY, tempX, tempY);
    Semester newSemester;

    setTextColor(blue); gotoXY(tempX, tempY); cout << "Input semester (1, 2, 3): ";
    ShowCur(1); setTextColor(black);
    newSemester.NO = 0;
    do
    {
        gotoXY(tempX + strlen("Input semester (1, 2, 3): "), tempY); cout << "         ";
        gotoXY(tempX + strlen("Input semester (1, 2, 3): "), tempY); cin >> newSemester.NO;
    } while (newSemester.NO > 3 || newSemester.NO < 1);
    if (schoolYear->y.listSemester[newSemester.NO - 1].NO != 0)
    {
        printTextAtXY(x + 45 / 2, tempY + 1, "Semester has not been initialized");
        char ch = _getch();
        deleteMenu(x, y, 17, 50);
        return;
    }
    ShowCur(0);
    deleteMenu(x, y, 17, 50);

    setTextColor(green); printTwoLine(x, y, 13, 50);
    setTextColor(red); gotoXY(x + 5, y + 1); cout << "- SchoolYear: "; setTextColor(black); cout << schoolYear->y.startYear << "-" << schoolYear->y.endYear;
    setTextColor(red); gotoXY(x + 5, y + 2); cout << "- Semester: "; setTextColor(black); cout << newSemester.NO;
    setTextColor(green); drawLineByX(x, y + 3, 50);
    setTextColor(blue);
    gotoXY(x + 2, y + 5); cout << "Input start date (dd mm yyyy): ";
    gotoXY(x + 4, y + 8); cout << "Input end date (dd mm yyyy): ";
    setTextColor(black);
    drawBox(x + 2 + strlen("Input start date (dd mm yyyy): "), y + 4, 15, 2);
    drawBox(x + 4 + strlen("Input end date (dd mm yyyy): "), y + 7, 15, 2);
    ShowCur(1);
    char ch;
    int i = 0, curPos[2] = { 0 };
    std::string input[2];

    int newX[2] = { x + 2 + strlen("Input start date (dd mm yyyy): ") + 1,
                    x + 4 + strlen("Input end date (dd mm yyyy): ") + 1 };
    int newY[2] = { y + 5, y + 8 };
    int oldX = newX[0], oldY = newY[0];

    gotoXY(oldX, oldY);
    while (true) {
        ch = _getch();

        if (ch == 27)
        {
            ShowCur(0);
            deleteMenu(x, y, 15, 52);
            return;
        }
        else if (ch == '\r')
        {
            if (input[0].length() == 10 && input[1].length() == 10)
            {
                if (!isValidRegisterDate(input[0]))
                    i = 0;
                else if (!isValidRegisterDate(input[1]))
                    i = 1;
                else {
                    ShowCur(0);
                    printTextAtXY(x + 25, y + 11, "Initialize the semester successfully !!!");
                    break;
                }
            }
            else if (input[0].length() != 10)
                i = 0;
            else
                i = 1;

            ShowCur(0);
            printTextAtXY(x + 21, y + 12, "Input invalid !!!");
            ShowCur(1);

            curPos[i] = input[i].length();
            oldX = newX[i] + input[i].length();
            oldY = newY[i];
            gotoXY(oldX, oldY);
        }
        else if (ch == -32) {
            ch = _getch();
            if (ch == 72 && i > 0) {
                i--;
                oldX = newX[i] + curPos[i];
                oldY = newY[i];

                gotoXY(oldX, oldY);
            }
            else if (ch == 80 && i < 1) {
                i++;
                oldX = newX[i] + curPos[i];
                oldY = newY[i];

                gotoXY(oldX, oldY);
            }
            else if (ch == 75 && curPos[i] > 0) {
                curPos[i]--;
                gotoXY(--oldX, oldY);
            }
            else if (ch == 77 && curPos[i] < input[i].length()) {
                curPos[i]++;
                gotoXY(++oldX, oldY);
            }
        }
        else if (ch == 9)
        {
            if (i < 1)
            {
                i++;
                oldX = newX[i] + curPos[i];
                oldY = newY[i];

                gotoXY(oldX, oldY);
            }
        }
        else if (ch == '\b' && curPos[i] > 0)
        {
            curPos[i]--;
            input[i].erase(curPos[i], 1);
            gotoXY(newX[i], oldY);
            std::cout << input[i] << " ";
            gotoXY(--oldX, oldY);
        }
        else if (ch != '\b')
        {
            input[i].insert(curPos[i], 1, ch);
            curPos[i]++;
            std::cout << input[i].substr(curPos[i] - 1);
            gotoXY(++oldX, oldY);
        }
    }

    size_t index1 = input[0].find(' ');
    size_t index2 = input[0].find(' ', index1 + 1);
    newSemester.startDate.day = stoi(input[0].substr(0, index1));
    newSemester.startDate.month = stoi(input[0].substr(index1 + 1, index2));
    newSemester.startDate.year = stoi(input[0].substr(index2 + 1));

    index1 = input[1].find(' ');
    index2 = input[1].find(' ', index1 + 1);
    newSemester.endDate.day = stoi(input[1].substr(0, index1));
    newSemester.endDate.month = stoi(input[1].substr(index1 + 1, index2));
    newSemester.endDate.year = stoi(input[1].substr(index2 + 1));

    schoolYear->y.listSemester[newSemester.NO - 1] = newSemester;

    string fileName = "./dataSemester/Course_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(newSemester.NO) + ".txt";
    ofstream fileSemesterW(fileName, ios_base::app);
    if (!fileSemesterW.is_open())
        return;
    fileSemesterW.close();


    string fileNameS = "./dataSchoolYear/Semester_" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + ".txt";
    ofstream fileSchoolYearW(fileNameS, ios_base::app);
    if (!fileSchoolYearW.is_open())
        return;

    fileSchoolYearW << newSemester.NO << "," << newSemester.startDate.day << "/" << newSemester.startDate.month << "/" << newSemester.startDate.year << ",";
    fileSchoolYearW << newSemester.endDate.day << "/" << newSemester.endDate.month << "/" << newSemester.endDate.year << "\n";
    fileSchoolYearW.close();

    string str = "Press any key to continue";
    setTextColor(red); gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, HEIGHT_CONSOLE - 3); cout << str;
    ch = _getch();
    deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE - 3, str);
    deleteMenu(x, y, 9, 45);
    setTextColor(black);
}

void menuViewSchoolYearForStaff(int x, int y, int height, int width) {
    deleteMenu(x, y, height, width);
    setTextColor(blue); printTwoLine(x, y, height, width);
    drawLineByX(x, y + 2, 50);

    setTextColor(purple);
    gotoXY(x + 2, y + 1); cout << "No";
    gotoXY(x + 8, y + 1); cout << "Start year";
    gotoXY(x + 29, y + 1); cout << "Start year";
}

void viewSchoolYearForStaff(int x, int y) {
    int i = 1;
    nodeSchoolYear* temp = listOfSY.head;
    int add = countLine("SchoolYear.txt");

    menuViewSchoolYearForStaff(x, y, 3 + add, 50);
    setTextColor(black);
 
    if (temp == NULL)
    {
        gotoXY(x + 5, y + 3); std::cout << "No data of school year ";
    }

    while (temp != NULL)
    {
        gotoXY(x + 2, y + 2 + i); cout << i;
        gotoXY(x + 8, y + 2 + i); cout << temp->y.startYear;
        gotoXY(x + 29, y + 2 + i); cout << temp->y.endYear;

        i++;
        temp = temp->nextYear;
    }

    string str = "Press any key to continue";
    setTextColor(red); gotoXY(WIDTH_CONSOLE / 2 - str.length() / 2, HEIGHT_CONSOLE - 3); cout << str;
    char ch = _getch();
    deleteTextAtXY(WIDTH_CONSOLE / 2, HEIGHT_CONSOLE - 3, str);
    deleteMenu(x, y, 3 + add, 52);
    setTextColor(black);
}