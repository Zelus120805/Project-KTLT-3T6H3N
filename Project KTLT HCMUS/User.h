#ifndef _H_USER_H_
#define _H_USER_H_

#include "Include.h"

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
void userRegister(listUser& lst,const char fileName[]);
void userLogIn(listUser& lst);
//void readAccountFile(listUser& lst);
#endif