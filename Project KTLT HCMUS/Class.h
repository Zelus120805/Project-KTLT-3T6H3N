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
void addTailSchoolYear(listOfSchoolYear& lst, schoolYear addition);
void readSchoolYear(listOfSchoolYear& lst);
void operateWithSchoolYear(listOfSchoolYear& lst);
void writeStudentToFileClass(Class a,const char fileName[]);
void createClass(listClass &lst);
void add1StudentToClass(Class& myClass,const char fileName[]);
void standardizeFile(const char fileName[]);
void deleteAllSchoolYear(listOfSchoolYear& lst);
//void assignClassToStudent(listClass lst,)
#endif