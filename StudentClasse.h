#pragma once

#include <iostream>
#include <string>

using namespace std;


static const int NUMBEROFMARKS = 50;
static const int LENGTHOFNAMES = 50;
static const int LENGTHOFSTRING = 10;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class student {
private:
    int studentIDNumber;
    char studentName[LENGTHOFNAMES];
    float projectMarks[NUMBEROFMARKS];
    float percentageMark;
    char letterGrade[LENGTHOFSTRING];
    void calculateLetterGrade();	//function to calculate grade
public:
    char projectName[NUMBEROFMARKS][LENGTHOFNAMES];
    int projectValue[NUMBEROFMARKS];
    int numberOfProjects;

    void getStudentDataFromUser();		//function to accept data from user
    void showOneStudentsData() const;	//function to show data on screen
    void entryProjectSetup();
    void showTabular() const;
    int getStudentIDNumber() const;
    float getPercentageMark() const;
    char* getStudentName();
}; //class ends here

class course {
public:
    course(int initialValue);  // set initial sort type
    ~course();  // destructor

    // getters
    char* getSchoolName();
    char* getcourseName();
    char* getcourseNumber();
    int getSort() const;

    // setters
    void setSchoolName();
    void setcourseName();
    void setcourseNumber();
    void setSort(int sType);

    char schoolName[LENGTHOFNAMES];
    char courseName[LENGTHOFNAMES];
    char courseNumber[LENGTHOFNAMES];

private:
    int typeOfSort;

}; //class ends here







