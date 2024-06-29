#include "myLib.h"

void viewStudentForStaff(listStudent lst) 
{
	system("cls");
	setTextColor(blue); print("Picture\\View List Student.txt", WIDTH_CONSOLE / 2 - 40, 1);
	int Sum = 0;
	nodeStudent* temp = lst.head;
	if (temp == NULL)
	{
		Sum = 0;
	}
	else {
		while (temp != NULL)
		{
			temp = temp->next;
			Sum++;
		}
	}
	int total, page;
	if (Sum % 12 == 0)
		total = Sum / 12;
	else
		total = Sum / 12 + 1;
	if (total == 0)
		page = 0;
	else
		page = 1;

	int x = WIDTH_CONSOLE / 2 - 30, y = 7, width = 60, height = 17;
	int New = 0, Old = 0;
	string str = "     Use left and right keys to change pages !!!    ";
	setBackgroundColor(lyellow); setTextColor(red); gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE - 1); cout << str;
	str = "     Press 'esc' to return    ";
	gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE); cout << str;
	setBackgroundColor(lwhite);

	bool check = true;
	while (true)
	{
		if (check == true)
		{
			str = "Page: " + to_string(page) + "/" + to_string(total);
			setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 59);
			setBackgroundColor(laqua);
			setTextColor(purple);
			menuViewStudentForStaff(x, y, height, width); 
			gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;

			if (page != total)
				printStudent(lst, (page - 1) * 12 + 1, page * 12, x, y);
			else
				printStudent(lst, (page - 1) * 12 + 1, Sum, x, y);

			check = false;
		}
		gotoXY(x + 1, y + 3 + Old); setTextColor(black); cout << getConsoleLine(x + 1, y + 3 + Old, 59);
		setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 59);
		setBackgroundColor(laqua);
		Old = New;

		char ch = _getch();
		if (ch == 27)
			break;
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
				check = true;
			}
			else if (ch == 77 && page < total) {
				New = 0;
				page++;
				check = true;
			}
			else
				continue;
		}
	}

	setBackgroundColor(lwhite);
}

bool isInCourse(nodeSchoolYear* schoolYear, Semester semester, nodeStudent* student, nodeCourse* course)
{
	string studentFile = "./dataStudent/" + to_string(student->student.info.idStudent) + "Course" + to_string(schoolYear->y.startYear) + "-" + to_string(schoolYear->y.endYear) + "_" + to_string(semester.NO) + ".txt";
	std::ifstream fileStudent(studentFile);

	if (!fileStudent.is_open())
	{
		return false;
	}
	string line;
	while (std::getline(fileStudent, line))
	{
		if (line.find(course->crs.info.courseName.c_str()) != string::npos)
		{
			return true;
		}
	}
	return false;
}

int deleteAStudentForStaffInCourse(listStudent lst)
{
	system("cls");
	setTextColor(blue); print("Picture\\Delete A Student.txt", WIDTH_CONSOLE / 2 - 30, 1);
	int Sum = 0;
	nodeStudent* temp = lst.head;
	while (temp != NULL)
	{
		;
		temp = temp->next;
		Sum++;
	}
	int total, page;
	if (Sum % 12 == 0)
		total = Sum / 12;
	else
		total = Sum / 12 + 1;
	if (total == 0)
		page = 0;
	else
		page = 1;

	int x = WIDTH_CONSOLE / 2 - 30, y = 7, width = 60, height = 17;
	int New = 0, Old = 0;
	string str = "     Use left and right keys to change pages !!!    ";
	setBackgroundColor(lyellow); setTextColor(red); gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE - 1); cout << str;
	str = "     Press 'esc' to return    ";
	gotoXY((WIDTH_CONSOLE - str.length()) / 2, HEIGHT_CONSOLE); cout << str;
	setBackgroundColor(lwhite);

	bool check = true;
	while (true)
	{
		if (check == true)
		{
			str = "Page: " + to_string(page) + "/" + to_string(total);
			setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 59);
			setBackgroundColor(laqua);
			setTextColor(purple);
			menuViewStudentForStaff(x, y, height, width);
			gotoXY(x + width - str.length() - 2, y + height - 1); cout << str;

			if (page != total)
				printStudent(lst, (page - 1) * 12 + 1, page * 12, x, y);
			else
				printStudent(lst, (page - 1) * 12 + 1, Sum, x, y);

			check = false;
		}
		gotoXY(x + 1, y + 3 + Old); setTextColor(black); cout << getConsoleLine(x + 1, y + 3 + Old, 59);
		setBackgroundColor(lwhite); setTextColor(red); gotoXY(x + 1, y + 3 + New); cout << getConsoleLine(x + 1, y + 3 + New, 59);
		setBackgroundColor(laqua);
		Old = New;

		char ch = _getch();
		if (ch == 27)
		{
			setBackgroundColor(lwhite);
			return 0;
		}
		else if (ch == '\r')
			break;
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
				check = true;
			}
			else if (ch == 77 && page < total) {
				New = 0;
				page++;
				check = true;
			}
			else
				continue;
		}
	}

	setBackgroundColor(lwhite);
	return New + (page - 1) * 12 + 1;
}