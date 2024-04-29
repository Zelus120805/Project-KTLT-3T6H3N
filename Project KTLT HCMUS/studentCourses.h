#ifndef _H_STUDENT_COURSES_H_
#define _H_STUDENT_COURSES_H_

#include "studentInformation.h"
#include "Course.h"

struct studentCourses {
    studentInformation student;
    Course* listOfEnrolled;
    int* no;
};
/// Điểm của học sinh = listOfEnrolled[i]->listOfCourse[no[i] - 1]

#endif