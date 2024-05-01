#ifndef _H_COURSE_H_
#define _H_COURSE_H_

#include "studentInformation.h"
#include "Score.h"
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
struct inCourse
{
    studentInformation student;
    courseInfo course;
    Score scoreOfCourse;
    inCourse* nextCourse;
    inCourse* nextPerson;
};

struct Course
{
    courseInfo course;
    inCourse* headOfList;
};
//S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)).

//struct listOfCourse {
//    Course* listOfCourses;
//};

#endif