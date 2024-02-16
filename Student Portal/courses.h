#ifndef courses_H
#define courses_H
#include <iostream>
#include "Date.h"
using namespace std;

struct Course
{
    string name;
    Date finalDate;
}CMPE201, CMPE241, CMPE243, CMPE263, FENS201, HST101;

Course courses[6] = {CMPE201, CMPE241, CMPE243, CMPE263, FENS201, HST101};
// we use this array while professors are assiging the courses.

void setCourses()
{
    CMPE201.name = "CMPE201";
    CMPE241.name = "CMPE241";
    CMPE243.name = "CMPE243";
    CMPE263.name = "CMPE263";
    FENS201.name = "FENS201";
    HST101.name = "HST101";
}

#endif