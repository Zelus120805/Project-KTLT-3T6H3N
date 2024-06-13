﻿#ifndef _H_INCLUDE_H_
#define _H_INCLUDE_H_

#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int HEIGHT_CONSOLE = 28, WIDTH_CONSOLE = 118;
const int black = 0;
const int blue = 1;
const int green = 2;
const int aqua = 3;
const int red = 4;
const int purple = 5;
const int yellow = 6;
const int white = 7;
const int gray = 8;
const int lblue = 9;
const int lgreen = 10;
const int laqua = 11;
const int lred = 12;
const int lpurple = 13;
const int lyellow = 14;
const int lwhite = 15;

//----------------------------
struct courseInfo {
    string idCourse;
    string courseName;
    string className;
    string teacherName;
    int numberOfCredits;
    int numberOfCurrentStudent;
    int maxStudent = 50;
    string dayOfWeek;
    string session;
    // studentInformation* listOfStudent;
    // Score* listOfScore;
};

struct Course
{
    courseInfo info;
    //   listStudent* lstStudentInCourse;
    //   Score score;
};
struct nodeCourse
{
    Course crs;
    nodeCourse* Next;
};
struct listCourse
{
    nodeCourse* head;
};
//------------------------------------
struct Date {
    int day;
    int month;
    int year;
};
//--------------------------------------
struct studentInformation {
    long idStudent;
    string firstName;
    string lastName;
    string gender;
    Date d;
    string socialId;
    string inClass;
};
//-----------------------------------------
struct User {
    string userName;
    string passWord;
};
struct nodeUser {
    User user;
    nodeUser* next;
};
struct listUser {
    nodeUser* head;
};

//----------------------------------------
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
struct listStudent
{
    nodeStudent* head;
};

struct Class {
    string nameClass;
    listStudent lst;
};
struct nodeClass
{
    Class myClass;
    nodeClass* next;
};
struct listClass {
    nodeClass* head;
};

struct schoolYear
{
    int startYear, endYear;
    listClass listOfClass;
};
struct nodeSchoolYear
{
    schoolYear y;
    nodeSchoolYear* nextYear;
};
struct listOfSchoolYear
{
    nodeSchoolYear* head;
};


//Danh sach hoc sinh
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
//-----------------------------------
struct Score {
    float otherMark;
    float midtermMark;
    float finalMark;
    float totalMark;
};
//-------------------------------------
struct Semester {
    int noSemester;
    schoolYear SchoolYear;
    Date start;
    Date end;
};

extern listStudent lst;
extern listOfSchoolYear list;
extern listCourse listOfCourse;
extern listStaff lstStaff;

//------------------------------------------------
void createSchoolYear(listOfSchoolYear& lst);
void addTailSchoolYear(listOfSchoolYear& lst, schoolYear addition);
void readSchoolYear(listOfSchoolYear& lst);
void operateWithSchoolYear(listOfSchoolYear& lst);
void writeStudentToFileClass(Class a, const char fileName[]);
void createClass(listClass& lst);
void add1StudentToClass(Class& myClass, const char fileName[]);
void standardizeFile(const char fileName[]);
void deleteAllSchoolYear(listOfSchoolYear& lst);
//------------------------------------------------
//Thao tác của sinh viên
void studentRegister(listStudent& lst, const char fileName[], int x, int y);

void readFileStudent(listStudent& lst, const char fileName[]);

void studentLogIn(listStudent& lst, const char fileName[], listCourse list);

void workSessionOfStudent(nodeStudent*& node, listCourse list);

void viewInfo(nodeStudent* Student);

bool isStudentExisted(listStudent lst, string userName);

void writeStudentToFile(listStudent lst, const char fileName[]);

void changePasswordForStudent(nodeStudent*& student, const char fileName[]);
//Thao tác của nhân viên

void addTailStaff(listStaff& lst, staffUser newStaff);

void staffRegister(listStaff& lst, const char fileName[], int x, int y);

void readFileStaff(listStaff& lst, const char fileName[]);

void staffLogIn(listStaff& staff, listOfSchoolYear& lstSchoolYear, listCourse& lstCourse);

bool isStaffExisted(listStaff lst, string userName);

void viewInfoStaff(nodeStaff* staff);

void changePasswordForStaff(nodeStaff*& staff, const char fileName[]);

void workSessionOfStaff(nodeStaff*& staff, listOfSchoolYear& lstSchoolYear, listCourse& lstCourse);

//void staffLogin(list)

//--------------------
void viewListCourse(listCourse lst);
void viewListStudentsInCourse(listCourse lst);

//Ghi thông tin môn học ra file lưu trữ
void writeACourseToFile(nodeCourse* course, const string fileName);

//Tạo một khóa học mới
void createNewCourse(listCourse& lst);

//Thêm một học sinh vào khóa học
void addAStudentToCourse(nodeCourse*& course, nodeStudent* student);

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
void deleteAllStaff(listStaff& lst);

void deleteAllSchoolYear(listOfSchoolYear& lst);
/*-------------------------------------------------------------*/
void userRegister(listUser& lst, const char fileName[]);
void userLogIn(listUser& lst);
//void readAccountFile(listUser& lst);





// ---------------------- - DELETE A STUDENT-------------------------------------- - 
bool isInCourse(nodeStudent * student, nodeCourse * course);
void readListStudentOfACourse(listStudent& lst, const string fileName);
void deleteNodeStudent(listStudent& lst, nodeStudent* deletion);
nodeStudent* goToStudent(int No, listStudent lst);
void printStudent(listStudent lst);
void deleteAStudentFromCourse(nodeCourse*& course, nodeStudent* deletion);
//--------------------------------------------------------------------------------

//-----------------------DELETE A COURSE------------------------------------------
void deleteNodeCourse(listCourse& lst, nodeCourse* deletion);
void deleteACourse(listCourse& lst, nodeCourse* deletion);

//---------------------------------------------------------------------------------

//-----------------EXPORT .CSV FILE AND OPERATE WITH SCORE-------------------------
void exportCSVFile(const string address, nodeCourse* course);




//---------------------------------------------------------------------------------

// Menu
void ShowCur(bool showCursor);
void setBackgroundColor(int bg);
void setTextColor(int text);
void gotoXY(int x, int y);
void print(const char* fileName, int x, int y);
void printTwoLine(int x, int y, int height, int width);
void focus(int x, int y, int width, char c);
void drawBoxAndText(int x, int y, int width, int height, string option);
void drawBox(int x, int y, int width, int height);
void inputLogin(int x, int y);
void printMovingInstructions();
void drawNBoxByX(int x, int y, int width, int height, int nBox, int dis, std::string* option);
void drawNBoxByY(int x, int y, int width, int height, int nBox, int dis, std::string* option);
void drawLineByY(int x, int y, int height);


void menuRegister();
void menuLogIn();
void menuMain();



bool checkPassword(User p);
bool KiemTraHoTen(string hoTen);
void XoaKhoangCach(string& name);
void ChuanHoaHoTen(string& name);

void importScoreBoard(nodeCourse& course, const string fileName);
#endif
