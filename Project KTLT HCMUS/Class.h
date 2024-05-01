#ifndef _H_CLASS_H_
#define _H_CLASS_H_

#include "studentInformation.h"
#include "privateUser.h"
struct Class {
    string nameClass;
    listStudent lst;
};
struct nodeClass
{
    Class myClass;
    nodeClass* next;
};
struct listClass {
    nodeClass* head;
};

struct schoolYear
{
    int startYear, endYear;
    listClass listOfClass;
};
struct nodeSchoolYear
{
    schoolYear y;
    nodeSchoolYear* nextYear;
};
struct listOfSchoolYear
{
    nodeSchoolYear* head;
};
void createSchoolYear(listOfSchoolYear& lst);
void createClass(listClass &lst);
void add1StudentToClass(Class& myClass);
void operateWithSchoolYear(listOfSchoolYear& lst);
#endif