﻿#include "myLib.h"

listStudent lstStudent;
listOfSchoolYear listOfSY;
listCourse listOfCourse;
listStaff lstStaff;
bool checkScore = true;

int main()
{
	lstStudent.head = nullptr;
	listOfSY.head = nullptr;
	listOfCourse.head = nullptr;
	lstStaff.head = NULL;

	readFileStudent(lstStudent, "accountStudent.txt");
	readFileStaff(lstStaff, "accountStaff.txt");

	menuMain();

	deleteAllStudent(lstStudent);
	deleteAllStaff(lstStaff);

	return 0;
}