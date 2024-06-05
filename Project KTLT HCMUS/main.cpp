#include "include.h"
#include "Menu.h"
#include "Windows.h"
listStudent lst;

listOfSchoolYear list;

listCourse listOfCourse;

int main()
{
	//readAccountFile(lst);
	//readAccountFile(lst);
	lst.head = nullptr;
	list.head = nullptr;
	listOfCourse.head = nullptr;
	readCourseFile(listOfCourse);
	readFileStudent(lst, "accountStudent.txt");
	chooseOptionMenuLogin(lst, list, listOfCourse);
	deleteAllCourse(listOfCourse);
	deleteAllSchoolYear(list);
	deleteAllStudent(lst);
	system("cls");
	return 0;
}