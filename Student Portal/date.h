#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <string>
using namespace std;

class Date
{
private:
    unsigned short day, month, year;

public:

    int isLeapYear() // checks if it is a leap year or not
    {
        if (((this->year % 4 == 0) && (this->year % 100 != 0)) || (this->year % 400 == 0))
            return 1;
        return 0;
    }

    bool isValid()
    {
        // if it is a leap year, February has 29 days
        int days_in_months[12] = {31, 28 + isLeapYear(), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
        // checking year
        if (this->year < 1)
            return false;

        // checking month
        if (this->month > 12 || this->month < 1)
            return false;

        // checking day
        if (this->day > days_in_months[(this->month) - 1] || this->day < 1)
            return false;

        return true;
    }

    string monthToStr() // converts month number to the name of the month as string
    {
        string monthNames[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        return monthNames[(this->month) - 1];
    }

    void display()
    {
        cout << monthToStr() << " " << this->day << ", " << this->year << endl;
    }

    // default constructor
    Date()
    {
        this->day = 1;
        this->month = 1;
        this->year = 1900;
    }
    // overload constructor
    Date(unsigned short day, unsigned short month, unsigned short year)
    {
        this->day = day;
        this->month = month;
        this->year = year;

        if (!isValid())
        {
            this->day = 1;
            this->month = 1;
            this->year = 1900;
            cerr << "Invalid Date!" << endl;
        }
    }

    bool isDefault() // if the date is set as default, return true
    {
        if (this->day == 1 && this->month == 1 && this->year == 1900)
            return true;
        return false;
    }
};
#endif