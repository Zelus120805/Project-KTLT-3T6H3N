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
void changePassword(const string userName, const string newPass);
void workSession(User& user);
//void readAccountFile(listUser& lst);
#endif