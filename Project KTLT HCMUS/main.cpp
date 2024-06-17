#include "myLib.h"

listStudent lstStudent;

listOfSchoolYear list;

listCourse listOfCourse;

listStaff lstStaff;

int main()
{
	//readAccountFile(lst);
	//readAccountFile(lst);
	lstStudent.head = nullptr;
	list.head = nullptr;
	listOfCourse.head = nullptr;
	lstStaff.head = NULL;
	readCourseFile(listOfCourse);
	readFileStudent(lstStudent, "accountStudent.txt");
	readFileStaff(lstStaff, "accountStaff.txt");

	menuMain();

	deleteAllCourse(listOfCourse);
	deleteAllSchoolYear(list);
	deleteAllStudent(lstStudent);
	deleteAllStaff(lstStaff);
	system("cls");
	return 0;
}