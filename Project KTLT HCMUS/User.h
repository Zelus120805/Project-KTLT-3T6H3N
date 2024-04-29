#ifndef _H_USER_H_
#define _H_USER_H_

#include "Include.h"

struct User {
    string userName;
    string passWord;
};
void userRegister();
void userLogIn();
#endif