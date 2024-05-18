#ifndef _H_COURSE_H_
#define _H_COURSE_H_

#include "studentInformation.h"
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

//Them mot hoc sinh vao danh sach hoc sinh, ghi ra file "Monhoc.txt", them vao enrolledList cua sinh vien do


//Tao mot khoa hoc
//S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)).
 
//struct listOfCourse {
//    Course* listOfCourses;
//};

#endif