#include "myLib.h"

void viewCoursesOfStudent(nodeStudent* Student, int x, int y)
{
	listOfSchoolYear lst;
	lst.head = NULL;
	readSchoolYear(lst);
	nodeSchoolYear* schoolYearNow = goToSchoolYear(lst, x, y);
	int optn;

	setTextColor(blue); gotoXY(x, y); cout << "Input semester (1, 2, 3): ";
	ShowCur(1); setTextColor(black);
	do
	{
		gotoXY(x + strlen("Input semester (1, 2, 3): "), y); cout << "         ";
		gotoXY(x + strlen("Input semester (1, 2, 3): "), y); cin >> optn;
	} while (optn > 3 || optn < 1);
	ShowCur(0);

	string fileName = "./dataStudent/" + to_string(Student->student.info.idStudent) + "_Course_" + to_string(schoolYearNow->y.startYear) + "-" + to_string(schoolYearNow->y.endYear) + "_" + to_string(optn) + ".txt";
	listCourse l1;
	l1.head = NULL;
	readCourseFileOfStudent(l1, fileName);

	system("cls");
	setTextColor(green); print("Picture\\List.txt", WIDTH_CONSOLE / 2 - 12, 1);
	x = WIDTH_CONSOLE / 2 - 50, y = 7;
	int height = 17, width = 100;
	int Sum = countLine(fileName);
	int total, page = 1;
	if (Sum % 12 == 0)
		total = Sum / 12;
	else
		total = Sum / 12 + 1;
	int New = 0, Old = 0;
	string str = "     Use left and right keys to change pages !!!    ";
	setBackgroundColor(lyellow); setTextColor(red); gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE - 1); cout << str;
	str = "     Press 'esc' to return    ";
	gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE); cout << str;
	setBackgroundColor(lwhite);

	menuDrawBoxForView(x, y, height, width);
	viewCourses(l1, 1, Sum, x, y);
	str = "Page: " + to_string(page) + "/" + to_string(total);
	setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 99);
	setBackgroundColor(laqua);
	setTextColor(purple); gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;
	while (true)
	{
		char ch = _getch();
		if (ch == 27)
			return;
		else if (ch == -32) {
			ch = _getch();
			if (ch == 72 && New > 0) {
				New--;
			}
			else if (ch == 80) {
				if (page < total && New < 11)
					New++;
				else if (page == total && New < Sum - (total - 1) * 12 - 1)
					New++;
			}
			else if (ch == 75 && page > 1) {
				New = 0;
				page--;
				menuDrawBoxForView(x, y, height, width);
				viewStudent((page - 1) * 12 + 1, page * 12, x, y);
				str = "Page: " + to_string(page) + "/" + to_string(total);
				setTextColor(purple); gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;
			}
			else if (ch == 77 && page < total) {
				New = 0;
				page++;
				menuDrawBoxForView(x, y, height, width);
				if (page != total)
					viewCourses(l1, (page - 1) * 12 + 1, page * 12, x, y);
				else
					viewCourses(l1, (page - 1) * 12 + 1, Sum, x, y);
				str = "Page: " + to_string(page) + "/" + to_string(total);
				setTextColor(purple); gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;
			}
			else
				continue;

			gotoXY(x + 1, y + 3 + Old); setTextColor(black); cout << getConsoleLine(x + 1, y + 3 + Old, 99);
			setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 99);
			setBackgroundColor(laqua);
			Old = New;
		}
	}

	setBackgroundColor(lwhite);
	deleteAllCourse(l1);
	deleteAllSchoolYear(lst);
}

void viewCourses(listCourse l1, int start, int end, int x, int y)
{
	if (end == 0)
	{
		setTextColor(red);
		gotoXY(HEIGHT_CONSOLE / 2, y + 3); cout << "No data of student in course !!!";
		return;
	}

	setTextColor(black);
	int index = 0;
	nodeCourse* temp = l1.head;
	while(temp != NULL)
	{
		gotoXY(x + 1, y + 3 + index); cout << index + 1;
		gotoXY(x + 5, y + 3 + index); cout << temp->crs.info.idCourse;
		gotoXY(x + 16, y + 3 + index); cout << temp->crs.info.className;
		gotoXY(x + 27, y + 3 + index); cout << temp->crs.info.courseName;
		gotoXY(x + 52, y + 3 + index); cout << temp->crs.info.teacherName;
		gotoXY(x + 79, y + 3 + index); cout << temp->crs.info.numberOfCredits;
		gotoXY(x + 88, y + 3 + index); cout << temp->crs.info.dayOfWeek;

		temp = temp->Next;
		index++;
	}
}