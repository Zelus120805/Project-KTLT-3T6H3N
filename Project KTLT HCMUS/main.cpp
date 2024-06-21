#include "myLib.h"

listStudent lstStudent;
listOfSchoolYear listOfSY;
listCourse listOfCourse;
listStaff lstStaff;

int main()
{
	lstStudent.head = nullptr;
	listOfSY.head = nullptr;
	listOfCourse.head = nullptr;
	lstStaff.head = NULL;

	readFileStudent(lstStudent, "accountStudent.txt");
	readFileStaff(lstStaff, "accountStaff.txt");

	menuMain();

	//readCourseFileOfStudent(listOfCourse, "dataStudent\\23120360_Course_2021-2022_1.txt");

	deleteAllStudent(lstStudent);
	deleteAllStaff(lstStaff);
	//system("cls");

	return 0;
}