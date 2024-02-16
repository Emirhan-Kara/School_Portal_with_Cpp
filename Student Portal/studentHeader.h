#ifndef StudentHeader_H
#define StudentHeader_H
#include "userHeader.h"
#define allowedMaxCourses 3
using namespace std;

class Student : public User
{
private:
    // max amount of courses a student can enroll is decided as 3
    string enrolledCourses[allowedMaxCourses] = {"Empty", "Empty", "Empty"}; // courses are set to "Empty" as default
    double notesOfCourses[allowedMaxCourses] = {0.0, 0.0, 0.0}; // to calculate GPA
    double GPA;
    short currentCourseNumber;

public:
    Student()
    {
        // default contructor does nothing
    }
    Student(string &username, string &password, string &role, string &courseLog0, string &courseLog1, string &courseLog2) : User(username, password, role)
    {
        // when the object is created in afterLogin function in main.cpp, data is provided through file.
        // Accoring to that data, object's parameters are updated too in here.
        this->currentCourseNumber = 0;
        this->enrolledCourses[0] = courseLog0;
        this->enrolledCourses[1] = courseLog1;
        this->enrolledCourses[2] = courseLog2;
    }
    void setCurrentCourseNumber() // if the course name is not emtpy, increase counter and set it.
    {
        short set = 0;
        for(int i = 0; i < allowedMaxCourses; i++)
        {
            if(enrolledCourses[i] != "Empty")
                set++;
        }
        this->currentCourseNumber = set;
    }

    void displayEnrolledCourses()
    {
        cout << "\nEnrolled courses for " << getUserName() << " are:\n";
        for(int i = 0; i < allowedMaxCourses; i++)
        {
            cout << i+1 << ") " << enrolledCourses[i] << endl;
        }
    }
    
    void setNotes() // user writes their notes to calculate GPA
    {
        for(int i = 0; i <currentCourseNumber; i++)
        {
            cout << endl << "Note for " << enrolledCourses[i] << ": "; 
            cin >> notesOfCourses[i];
        }
    }

    void calculateGPA()
    {
        double temp = 0.0;
        for(int i = 0; i < currentCourseNumber; i++)
        {
            temp += notesOfCourses[i] / currentCourseNumber;
        }
        if (temp == 0.0)
            this->GPA = 0.0;
        this->GPA = temp;
    }

    double getGPA()
    {
        return this->GPA;
    }

    short getCurrentCourseNumber()
    {
        return this->currentCourseNumber;
    }

    void updateCourses(short curCourseNum, string courseName) // to update the wanted numbered course
    {
        this->enrolledCourses[curCourseNum] = courseName;
    }
    
    string getEnrolledCourse(short i) // to get the wanted numbered course
    {
        return this->enrolledCourses[i];
    }
};
#endif