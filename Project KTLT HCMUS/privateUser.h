#ifndef _H_PRIVATEUSER_H_
#define _H_PTIVATEUSER_H_

#include "User.h"
//#include "studentInformation.h"
#include "Course.h"

struct studentUser {
    User account;
    studentInformation info;
    inCourse* headOfEnrolledCourse;
};
struct nodeStudent
{
    studentUser student;
    nodeStudent* next;
};

//Danh sach hoc sinh
struct listStudent
{
    nodeStudent* head;
};
struct managerUser {
    User account;
    string name;
};
void studentRegister(listStudent&lst,const char fileName[]);
void readFileStudent(listStudent& lst, const char fileName[]);
void studentLogIn(listStudent &lst,const char fileName[]);
void workSessionOfStudent(nodeStudent*& node);
void viewInfo(nodeStudent* Student);
bool isStudentExisted(listStudent lst, string userName);
void writeStudentToFile(listStudent lst, const char fileName[]);
#endif