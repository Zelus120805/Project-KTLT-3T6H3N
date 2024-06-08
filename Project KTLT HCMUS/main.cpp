#include "myLib.h"

listStudent lst;

listOfSchoolYear list;

listCourse listOfCourse;

listStaff lstStaff;

int main()
{
	//readAccountFile(lst);
	//readAccountFile(lst);
	lst.head = nullptr;
	list.head = nullptr;
	listOfCourse.head = nullptr;
	lstStaff.head = NULL;
	readCourseFile(listOfCourse);
	readFileStudent(lst, "accountStudent.txt");

	menuMain();

	deleteAllCourse(listOfCourse);
	deleteAllSchoolYear(list);
	deleteAllStudent(lst);
	deleteAllStaff(lstStaff);
	system("cls");
	return 0;
}