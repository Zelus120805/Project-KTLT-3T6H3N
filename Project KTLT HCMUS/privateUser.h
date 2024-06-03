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

struct staffUser {
    User account;
    int IDofStaff;
    string firstName;
    string lastName;
    string gender;
    Date d;
    string socialId;

};
struct nodeStaff
{
    staffUser staff;
    nodeStaff* next;
};
struct listStaff
{
    nodeStaff* head;
};
//Thao tác của sinh viên
void studentRegister(listStudent&lst,const char fileName[], int x, int y, int height);

void readFileStudent(listStudent& lst, const char fileName[]);

void studentLogIn(listStudent &lst,const char fileName[],listCourse list);

void workSessionOfStudent(nodeStudent*& node, listCourse list);

void viewInfo(nodeStudent* Student);

bool isStudentExisted(listStudent lst, string userName);

void writeStudentToFile(listStudent lst, const char fileName[]);
//Thao tác của nhân viên
void addTailStaff(listStaff& lst, staffUser newStaff);

void staffRegister(listStaff& lst, const char fileName[], int x, int y, int height);

void readFileStaff(listStaff& lst, const char fileName[]);

//void staffLogin(list)

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

void addTailStudent(listStudent& lst, nodeStudent* newNode);
//Đọc sinh viên từ .CSV
void readStudentFromCSV(listStudent& lst, const string fileName);
//Thêm N sinh viên từ file .CSV
void addNStudentFromFile(nodeCourse*& course, const string fileName);
//Giải phóng bộ nhớ sinh viên
void deleteAllStudent(listStudent& lst);
//Giải phóng bộ nhớ khóa học
void deleteAllCourse(listCourse& lst);
//Giải phóng bộ nhớ năm học
//void deleteAllSchoolYear(listOfSchoolYear& lst);

#endif