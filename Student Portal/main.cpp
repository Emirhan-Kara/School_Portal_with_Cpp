#include <iostream>
#include <string>
#include <fstream>
#include "userHeader.h"
#include "studentHeader.h"
#include "professorHeader.h"
#include "date.h"
#include "courses.h"
#define course_num 6
using namespace std;
string courseNames[course_num] = {"CMPE201", "CMPE241", "CMPE243", "CMPE263", "FENS201", "HST101"};
// we will use this array to get the names of the courses in the decided order

string toLowerCase(string &s);
void registeration();
void login();
void afterLogin(string &username, string &password, string &role, string &courseLog0, string &courseLog1, string &courseLog2);

int main()
{
    setCourses(); // creates the courses data structrue and set courses
    short choice;
    cout << "\n---------------------------\n~\tMAIN PAGE\t~\n---------------------------";
    cout << "\nPlease select your choice\n\n";
    cout << "1) Register\n2) Login\n3) Remove all the data\n4) EXIT\n";
    cin >> choice;

    switch (choice)
    {
    case (1):
    {
        registeration();
        break;
    }
    case (2):
    {
        login();
        break;
    }
    case (3):
    {
        string adminUsername = "admin123";
        string adminPassword = "admin";
        string checkUsername, checkPassword;
        system("cls");
        cout << "ADMIN USERNAME: ";
        cin >> checkUsername;
        cout << "\nADMIN PASSWORD: ";
        cin >> checkPassword;
        
        system("cls");
        if (checkPassword == adminPassword && checkUsername == adminUsername)
        {
            ofstream file("users.txt", ios::trunc); // to clear the previous registerations
            if (file.is_open())
            {
                cout << "Logged in as ADMIN\nData has been deleted. Thanks for joining!\n";
                file.close();
            }
        }
        else
            cout << "You don't have permisson!!!\n";
        main();
    }
    case (4):
    {     
        exit(0);
    }
    default:
        system("cls");
        cout << "\nEnter valid number!\n\n\n";
        main();
    }
}

string toLowerCase(string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}
// registeration function: When it is called, it allows users to register with their usernames, passwords and roles.
//The data is stored in a txt file ("users.txt")
void registeration()
{
    system("cls");
    string enteredUsername, enteredPassword, controlUsername, controlPassword, role;

    cout << "\nCreate a username: ";
    cin >> enteredUsername;
    cout << "\nCreate a password: ";
    cin >> enteredPassword;
    cout << "\nEnter your role (student, professor): ";
    cin >> role;
    role = toLowerCase(role); // role is stored as all lowercased into the file.
    cout << "\n\t\t" << role << "\n\t\t";

    ofstream f1("users.txt", ios::app);
    if (f1.is_open())
    {
        f1 << enteredUsername << " " << enteredPassword << " " << role << " "
           << "Empty "
           << "Empty "
           << "Empty\n";
    // a user (both professors and students) has max 3 courses to enroll or give according to the role.
    //So, while registering, its courses are set as Empty into the file. Later on, it will be updated accrdingly throughout the process
        system("cls");
        cerr << "\nRegisteration is SUCCESSFUL!\n";
        f1.close();
        main();
    }
    else
    {
        cerr << "\nRegisteration is FAILED!\n";
        main();
    }
}

// login function: When it is called, it allows users to login with their usernames, passwords and roles.
// The function controls every user that has been registered (data inside the "users.txt" file)
// when there is a full match (same username, password and role (there could be a professor and a student with the same username and password)),
//that user logs in to the system
void login()
{
    bool check;
    system("cls");
    string enteredUsername, enteredPassword, enteredRole, controlUsername, controlPassword, controlRole;
    // would fill with the records taken from the file until the end(always store the last user from the file. Thats why we would create another array and store the logged in users courses there)
    string courseLogs_Control[3] = {"1", "2", "3"}; 
    string courseLogs_Loggedin[3]; //this is the array that mentioned above

    cout << "\nUSERNAME: ";
    cin >> enteredUsername;
    cout << "\nPASSWORD: ";
    cin >> enteredPassword;
    cout << "\nROLE: ";
    cin >> enteredRole;
    enteredRole = toLowerCase(enteredRole); // because the role is stored as all lowercased in the file, we cast it here too

    ifstream f2("users.txt");
    if (f2.is_open())
    {
        while (f2 >> controlUsername >> controlPassword >> controlRole >> courseLogs_Control[0] >> courseLogs_Control[1] >> courseLogs_Control[2])
        {
            // if there is a full match (mean successful login), assign its courses from txt file into the courseLogs_Loggedin array and turn check to true
            if (enteredUsername == controlUsername && enteredPassword == controlPassword && enteredRole == controlRole)
            {
                // assign the logged in users courses to the array 
                courseLogs_Loggedin[0] = courseLogs_Control[0];
                courseLogs_Loggedin[1] = courseLogs_Control[1];
                courseLogs_Loggedin[2] = courseLogs_Control[2];
                check = true;
                system("cls");
            }
        }
        f2.close();

        if (check)
        {
            system("cls");
            cout << enteredUsername << " LOGGED IN SUCCESSFULY!\n";
            // we pass the entered username/password/role and the logged in user's courses (courseLogs_Loggedin array in order) into the after login function
            afterLogin(enteredUsername, enteredPassword, enteredRole, courseLogs_Loggedin[0], courseLogs_Loggedin[1], courseLogs_Loggedin[2]);
        }
        else
        {
            cerr << "\nLOGIN FAILED!\n";
            main();
        }
    }
}

// afterLogin function: When it is called, it means there is successful login. From login function, the logged in user's data is passed to here.
// In this function, according to the role, proper menu is given to the user and proper objects are created.
void afterLogin(string &username, string &password, string &role, string &courseLog0, string &courseLog1, string &courseLog2) // these are the informatons of the logged in user
{
    // must be loged in here, dont go back to main, give the proper menu according to the role
    if (role == "student")
    {
        // we create our student object here. we have assigned its courses by reading them from the file first (between line 139-155), then passing that data to this function(afterLogin) from login function
        Student student(username, password, role, courseLog0, courseLog1, courseLog2); 

        while (true)
        {
            student.setCurrentCourseNumber(); // we first set the current course number by calling a method from its class
            short currentCourseNumber = student.getCurrentCourseNumber(); // then we get the current course number
            short choice;
            cout << "Please select your choice\n\n";
            cout << "1)Enroll to a course" << endl
                 << "2)Show enrolled courses" << endl
                 << "3)Calculate GPA" << endl
                 << "4)Show deadlines for the final projects" << endl
                 << "5)EXIT" << endl;
            cin >> choice;

            switch (choice) // proper menu will be provided to the user accoring to the choice they make
            {
            case (1):
            {
                system("cls");
                if (currentCourseNumber < allowedMaxCourses) // if the student still has room to chose a course (max allowed courses are determined as 3 in this system)
                {
                    string course_choice; // to represent the chosen course (as string)
                    short course_num_choice; // to choose from the menu (as number)
                    // prints out possible courses
                    cout << endl
                         << "Select a course\n";
                    cout << "1)" << courseNames[0];
                    for (int i = 1; i < course_num; i++)
                    {
                        cout << "\t" << i + 1 << ")" << courseNames[i];
                    } // panel would look like
                      // Select a course
                      // 1)CMPE201  2)CMPE241   3)CMPE243   4)CMPE263   5)FENS201   6)HST101
                      // YOUR CHOICE:
                    cout << endl
                         << "YOUR CHOICE: ";
                    cin >> course_num_choice;
                    course_choice = courseNames[course_num_choice - 1]; // assign the name of the course to the string course_choice

                    //  now lets check if the chosen course is already been chosen
                    short control = 0;
                    for (int i = 0; i < currentCourseNumber; i++)
                    {
                        if (course_choice == student.getEnrolledCourse(i))
                        {
                            system("cls");
                            cout << "\nYou have already chosen that course!\n";
                            control++;
                        }
                    }

                    // if it is not already chosen, then we can assign that course_choice into the enrolledCourses of student
                    if (control == 0)
                    {
                        system("cls");
                        cout << "\nYou have successfuly enrolled\n";
                        student.updateCourses(currentCourseNumber, course_choice); // we update the object's courses here

                        // we have to update the user.txt file
                        ifstream f3("users.txt");
                        if (f3.is_open())
                        {
                            string controlUsername, controlPassword, controlRole;
                            string controlCourses[3] = {"Empty", "Empty", "Empty"};
                            ofstream tempfile("temp.txt", ios::app); // app mode, because we write to the end (just in case actually)
                            if (tempfile.is_open())
                            {
                                while (f3 >> controlUsername >> controlPassword >> controlRole >> controlCourses[0] >> controlCourses[1] >> controlCourses[2])
                                { // if it is not the logged in user, write the data into the temp file.
                                    if (!(username == controlUsername && password == controlPassword && role == controlRole))
                                    {
                                        tempfile << controlUsername << " " << controlPassword << " " << controlRole << " " << controlCourses[0] << " "
                                                 << controlCourses[1] << " " << controlCourses[2] << endl;
                                    }
                                    else //if it is the logged in user, write its updated data into the temp file
                                    {
                                        tempfile << username << " " << password << " " << role << " " << student.getEnrolledCourse(0) << " "
                                                 << student.getEnrolledCourse(1) << " " << student.getEnrolledCourse(2) << endl;
                                    }
                                }
                                tempfile.close();
                                f3.close();
                                remove("users.txt"); // remove the previous userx.txt file (with the old data)
                                rename("temp.txt", "users.txt"); // update the temp.txt file's name as users.txt. Now we have updated userx.txt                  
                            }
                        }
                    }
                    break;
                }
                else
                {
                    system("cls");
                    cout << "You have reached the max limit to choose a course!\n\n";
                }
            }
            case (2):
            {
                system("cls");
                student.displayEnrolledCourses();
                break;
            }
            case (3):
            {
                system("cls");
                student.setNotes();
                student.calculateGPA();
                system("cls");
                cout << "Your GPA is: " << student.getGPA() << endl;
                break;
            }
            case (4):
            {
                system("cls");
                student.displayEnrolledCourses();

                short answer; // index for the list of enrolled courses for the student
                cout << endl
                     << "\nFor which course you want to see the date: ";
                cin >> answer;

                if (answer <= student.getCurrentCourseNumber()) //  if the answer is valid
                {
                    string selectedCourse = student.getEnrolledCourse(answer - 1); // assign the name of the selected course into a string

                    short index = 0; // index in the array of courseNames (that includes all courses)
                    for (int i = 0; i < course_num; i++)
                    {
                        if (courseNames[i] == selectedCourse)
                            index = i; // it is set to the main order (for example "CMPE263" is the fourth member in the courseNames array, index is set to 3)
                    }

                    system("cls");
                    cout << "\nDeadline for the final project of " << courseNames[index] << " is: ";

                    if (courses[index].finalDate.isDefault()) // if the date is 1/1/1900 which is set by default constructor in date.h
                    {
                        cout << "Not decided by the professor yet\n";
                        break;
                    }
                    else
                    {
                        courses[index].finalDate.display();
                        cout << endl;
                        break;
                    }
                }
                else
                {
                    system("cls");
                    cout << "Invalid Entry!\n\n";
                    break;
                }
            }
            case (5):
            {
                system("cls");
                main();
            }
            default:
            {
                break;
            }
            }
        }
    }

    if (role == "professor")
    {
        // we create our professor object here. we assign its courses by reading them from the file first (between line 139-155), then passing that data to this(afterLogin) function from login function
        Professor professor(username, password, role, courseLog0, courseLog1, courseLog2);
        while (true)
        {
            professor.setCurrentLectureNumber(); // we first set the current lecture number by calling a method from its class
            short currentLectureNumber = professor.getCurrentLectureNumber(); // then we get the current lecture number
            short choice;
            cout << "Please select your choice\n\n";
            cout << "1)Select a course" << endl
                 << "2)Show given courses" << endl
                 << "3)Set final project submission date" << endl
                 << "4)EXIT" << endl;
            cin >> choice;

            switch (choice) // proper menu will be provided to the user accoring to the choice they make
            {
            case (1):
            {
                system("cls");
                if (currentLectureNumber < allowedMaxLecturesForProf) // if the professor still has room to give a lecture (max allowed lectures are determined as 3 in this system)
                {
                    string courseChoice;
                    short course_number;
                    // prints out possible courses
                    cout << endl
                         << "Select a course\n";
                    cout << "1)" << courseNames[0];
                    for (int i = 1; i < course_num; i++)
                    {
                        cout << "\t" << i + 1 << ")" << courseNames[i];
                    } // panel would look like
                      // Select a course
                      // 1)CMPE201  2)CMPE241   3)CMPE243   4)CMPE263   5)FENS201   6)HST101
                      // YOUR CHOICE:
                    cout << endl
                         << "YOUR CHOICE: ";
                    cin >> course_number;
                    courseChoice = courseNames[course_number - 1]; // assign the name of the course to the string courseChoice

                    //  now lets check if the chosen course is already been chosen
                    short control = 0;
                    for (int i = 0; i < currentLectureNumber + 1; i++)
                    {
                        if (courseChoice == professor.getGivenCourse(i))
                        {
                            system("cls");
                            cout << "\nYou have already chosen that course!\n";
                            control++;
                        }
                    }

                    // if not, then we can assign that courseChoice into the enrolledCourses of student
                    if (control == 0)
                    {
                        system("cls");
                        cout << "\nYou have successfuly selected a course\n";
                        professor.updateCourses(currentLectureNumber, courseChoice); // we update the object's courses here

                        // we have to update the user.txt file
                        fstream f3("users.txt");
                        if (f3.is_open())
                        {
                            string controlUsername, controlPassword, controlRole;
                            string controlCourses[3] = {"Empty", "Empty", "Empty"};
                            ofstream tempfile("temp.txt", ios::app);
                            if (tempfile.is_open())
                            {
                                while (f3 >> controlUsername >> controlPassword >> controlRole >> controlCourses[0] >> controlCourses[1] >> controlCourses[2])
                                { // if it is not the logged in user, write the data into the temp file.
                                    if (!(username == controlUsername && password == controlPassword && role == controlRole))
                                    {
                                        tempfile << controlUsername << " " << controlPassword << " " << controlRole << " " << controlCourses[0] << " "
                                                 << controlCourses[1] << " " << controlCourses[2] << endl;
                                    }
                                    else //if it is the logged in user, write its updated data into the temp file
                                    {
                                        tempfile << username << " " << password << " " << role << " " << professor.getGivenCourse(0) << " "
                                                 << professor.getGivenCourse(1) << " " << professor.getGivenCourse(2) << endl;
                                    }
                                }
                                tempfile.close();
                                f3.close();
                                remove("users.txt"); // remove the previous userx.txt file (with the old data)
                                rename("temp.txt", "users.txt"); // update the temp.txt file's name as users.txt. Now we have updated userx.txt                        
                            }
                        }
                    }
                    break;
                }
                else
                {
                    system("cls");
                    cout << "You have reached the max limit to give a lecture!\n\n";
                }
            }
            case (2):
            {
                system("cls");
                professor.displayGivenCourses();
                break;
            }
            case (3):
            {
                system("cls");
                professor.displayGivenCourses();

                short answer; // index for the list of given courses for the professor
                cout << endl
                     << "\nFor which course, you want to set the date: ";
                cin >> answer;

                if (answer <= professor.getCurrentLectureNumber()) // if the answer is valid
                {
                    string selectedCourse = professor.getGivenCourse(answer - 1); // assign the name of the selected course into a string

                    short index = 0; // index in the array of courseNames (that includes all courses)
                    for (int i = 0; i < course_num; i++)
                    {
                        if (courseNames[i] == selectedCourse)
                            index = i; // it is set to the main order (for example "CMPE263" is the fourth member in the courseNames array, index is set to 3)
                    }

                    unsigned short day, month, year;
                    cout << "\nSet the day: ";
                    cin >> day;
                    cout << "\nSet the month: ";
                    cin >> month;
                    cout << "\nSet the year: ";
                    cin >> year;

                    courses[index].finalDate = Date(day, month, year);
                    system("cls");
                    if (!courses[index].finalDate.isDefault())
                    {
                        cout << "\nSubmission date is set as ";
                        courses[index].finalDate.display();
                        cout << endl;
                    }
                    else
                    {
                        cout << "\nINVALID DATE!\nDate couldn't be set!\n";
                    }
                    break;
                }
                else
                {
                    system("cls");
                    break;
                }
            }
            case (4):
            {
                system("cls");
                main();
            }
            default:
            {
                break;
            }
            }
        }
    }
}