#ifndef _H_PRIVATEUSER_H_
#define _H_PTIVATEUSER_H_

#include "User.h"
#include "Course.h"
//#include "studentInformation.h"


struct studentUser {
    User account;
    studentInformation info;
    listCourse* enrolledCourse;
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

void studentRegister(listStudent&lst,const char fileName[], int x, int y, int height);
void readFileStudent(listStudent& lst, const char fileName[]);
void studentLogIn(listStudent &lst,const char fileName[],listCourse list);
void workSessionOfStudent(nodeStudent*& node, listCourse list);
void viewInfo(nodeStudent* Student);
bool isStudentExisted(listStudent lst, string userName);
void writeStudentToFile(listStudent lst, const char fileName[]);

//--------------------
void viewListCourse(listCourse lst);

//Ghi thông tin môn học ra file lưu trữ
void writeACourseToFile(nodeCourse* course, const string fileName);

//Tạo một khóa học mới
void createNewCourse(listCourse& lst);

//Thêm một học sinh vào khóa học
void addAStudentToCourse(nodeCourse*&course, nodeStudent* student);

//addTail khóa học
void addTailCourse(listCourse& lst, Course newCourse);

//Đọc file khóa học mỗi khi khởi chạy chương trình
void readCourseFile(listCourse& lst);
#endif