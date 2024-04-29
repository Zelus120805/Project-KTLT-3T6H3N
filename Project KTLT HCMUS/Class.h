#ifndef _H_CLASS_H_
#define _H_CLASS_H_

#include "studentInformation.h"

struct Class {
    string nameClass;
    studentInformation* listOfStudent;
};

struct listClass {
    Class* listOfClass;
};

#endif