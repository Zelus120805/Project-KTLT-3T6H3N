#ifndef _H_MENU_H_
#define _H_MENU_H_

#include "include.h"

void drawBox(int x, int y, int width, int height, std::string option);
void drawNBox(int x, int y, int width, int height, int nBox, std::string* option);
void focus(int x, int y, int width, char c);
void menuLogin(int x, int y, int width, int height, int nBox);
void chooseOptionMenuLogin(listStaff &listS,listStudent& listST, listOfSchoolYear& listSY, listCourse& listOfCourse);
void menuStudentRegister(int x, int y, int width, int height, int nBox);
void menuStaffRegister(int x, int y, int width, int height, int nBox);
#endif