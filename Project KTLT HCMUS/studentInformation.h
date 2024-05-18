#ifndef _H_STUDENT_INFORMATION_H_
#define _H_STUDENT_INFORMATION_H_

#include "Date.h"

struct studentInformation {
    int idStudent;
    string fullName;
    string firstName;
    string lastName;
    string gender;
    Date d;
    string socialId;
    string inClass;
};

#endif