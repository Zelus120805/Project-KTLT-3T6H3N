#ifndef _H_PRIVATEUSER_H_
#define _H_PTIVATEUSER_H_

#include "User.h"
#include "studentInformation.h"

struct studentUser {
    User account;
    studentInformation info;
};

struct managerUser {
    User account;
    string name;
};

#endif