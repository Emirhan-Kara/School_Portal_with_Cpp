#ifndef ProfessorHeader_H
#define ProfessorHeader_H
#include "userHeader.h"
#define allowedMaxLecturesForProf 3
using namespace std;

class Professor : public User
{
private:
    // max amount of courses a student can enroll is decided as 3
    string givenCourses[allowedMaxLecturesForProf] = {"Empty", "Empty", "Empty"}; // courses are set to "Empty" as default
    short currentLectureNumber;
public:
    Professor()
    {
        // default contructor does nothing
    }
    Professor(string &username, string &password, string &role, string &courseLog0, string &courseLog1, string &courseLog2) : User(username, password, role)
    {
        // when the object is created in afterLogin function in main.cpp, data is provided through file.
        // Accoring to that data, object's parameters are updated too in here.
        this->currentLectureNumber = 0;
        this->givenCourses[0] = courseLog0;
        this->givenCourses[1] = courseLog1;
        this->givenCourses[2] = courseLog2;
    }

    short getCurrentLectureNumber()
    {
        return this->currentLectureNumber;
    }
    void setCurrentLectureNumber() // if the course name is not emtpy, increase counter and set it.
    {
        short set = 0;
        for(int i = 0; i < allowedMaxCourses; i++)
        {
            if(givenCourses[i] != "Empty")
                set++;
        }
        this->currentLectureNumber = set;
    }

    void updateCourses(short currentCourseNum, string courseName) // to update the wanted numbered course
    {
        this->givenCourses[currentCourseNum] = courseName;
    }

    void displayGivenCourses()
    {
        cout << "\nEnrolled courses for " << getUserName() << " are:\n";
        for(int i = 0; i < allowedMaxLecturesForProf; i++)
        {
            cout << i+1 << ") " << givenCourses[i] << endl;
        }
    }
    
    string getGivenCourse(short i) // to get the wanted numbered course
    {
        return this->givenCourses[i];
    }
};
#endif