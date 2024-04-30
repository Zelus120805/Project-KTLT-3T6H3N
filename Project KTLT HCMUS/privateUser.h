#ifndef _H_PRIVATEUSER_H_
#define _H_PTIVATEUSER_H_

#include "User.h"
#include "studentInformation.h"

struct studentUser {
    User account;
    studentInformation info;
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
struct managerUser {
    User account;
    string name;
};
void studentRegister(listStudent&lst,const char fileName[]);
#endif