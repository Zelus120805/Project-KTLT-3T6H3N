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
void userRegister(listUser& lst);
void userLogIn(listUser& lst);
void changePassword(listUser& lst,User user1);
void workSession(listUser& lst,User& user);
void readAccountFile(listUser& lst);
#endif