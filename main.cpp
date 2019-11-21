#include<iostream>
#include<fstream>
#include<iomanip>
#include <cstring>
#include <sstream>
#include <string>
#include "StudentClasse.h"

using namespace std;

/*
* This file is part of {{ StudentDB project }}.
*
* Developed for: University of Alberta Department of Drama
*
* By Tim M. M. Williamson
* cad491@shaw.ca 780-920-6498
* Date: November 2019
* Feature: Student project marks record keeping and reporting
* Version: 01
*
* Based on C++ software by Sulabh Agrawal of ASN Engineering College
*
* <copyright notice>
* This code is (c)  COPYRIGHT protected 2020 by Tim M. M. Williamson ALL RIGHTS RESERVED
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the-----
* GNU General Public License. See <https://www.gnu.org/licenses/>.
*
*Date 		      | Change
*----------------|-------------------------------------------------
*Nov8-19    | Version 01 start
* Nov20-19 | 01 code completion
*                    |
*                    |
*/

//***************************************************************
//    	function declaration
//****************************************************************

void writeStudentData();	//write the record in binary file
void displayAllStudentData();	//read all records from binary file
void displayOneStudentsData(int);	//accept studentIDNumber and read record from binary file
void modifyOneStudentsData(int);	//accept studentIDNumber and update record of binary file
void deleteOneStudent(int);	//accept studentIDNumber and delete selected records from binary file
void classDisplayAllTabular(course *);	//display all records in tabular format from binary file
void introTitlePage();		//display welcome screen
void readSchoolData(course *) ; // read the data from School.txt
void mainMenu(course *);    // Display the main Menu
void entryMenu(course *);	//display entry menu on screen
void resultMenu(course *);		//display result menu
void sortOptionsMenu(course *);   // place to enter info on the school and the class
void entryProjectSetup(student *);	//setup project names
void classSortAll(course *courseD); // sort all students
void bubbleSortByID( student *studentA, int n, int countOfRecords); // Sort all students by ID number
void bubbleSortByGrade( student *studentA, int n, int countOfRecords);  // sort all students by grade
void bubbleSortByName( student *studentA, int n, int countOfRecords);  // Sort all students by name
bool compareTwoNames(student *studentA, student *studentB); // used in the Name bubble sort
void swap(int *xp, int *yp); // used in all bubble sorts to flip the order of two students

//***************************************************************
//    	Course Private Functions
//****************************************************************

    course::course(int initialValue)
    {
        course::setSort(initialValue);
    }

    char* course::getSchoolName()
    {
        return(schoolName);
    }
    char* course::getcourseName()
    {
        return(courseName);
    }
    char* course::getcourseNumber()
    {
        return(courseNumber);
    }

    void course::setSchoolName()
    {
        cout<<"\nEnter the name of the institution ";
        cin.getline(schoolName,LENGTHOFNAMES);
    }
    void course::setcourseName()
    {
        cout<<"\n\nEnter the name of the course ";
        cin.getline(courseName,LENGTHOFNAMES);
    }
    void course::setcourseNumber()
    {
        cout<<"\n\nEnter the number designation of the course ";
        cin.getline(courseNumber,LENGTHOFNAMES);
    }

    int course::getSort() const
    {
        return typeOfSort;
    }
    void course::setSort(int sType)
    {
        typeOfSort = sType;
    }

//***************************************************************
//    	Student Private Functions
//****************************************************************

void student::calculateLetterGrade()
{
    percentageMark = 0; // start with a clean slate...

    for (int counter = 0; counter < numberOfProjects; counter++) {
        percentageMark = percentageMark + projectMarks[counter];
    }// for

    if(percentageMark >= 90)
        strcpy(letterGrade, "A+");
    else if(percentageMark >= 85)
        strcpy(letterGrade,"A");
    else if(percentageMark >= 80)
        strcpy(letterGrade,"A-");
    else if(percentageMark >= 76)
        strcpy(letterGrade, "B+");
    else if(percentageMark >= 72)
        strcpy(letterGrade, "B");
    else if(percentageMark >= 68)
        strcpy(letterGrade, "B-");
    else if(percentageMark >= 64)
        strcpy(letterGrade,"C+");
    else if(percentageMark >= 60)
        strcpy(letterGrade,"C");
    else if(percentageMark >= 56)
        strcpy(letterGrade, "C-");
    else if(percentageMark >= 52)
        strcpy(letterGrade, "D+");
    else if(percentageMark >= 50)
        strcpy(letterGrade, "D");
    else
        strcpy(letterGrade, "F(R)");
}

void student::getStudentDataFromUser()
{
    cout<<"\nEnter the student's ID number ";
    cin>>studentIDNumber;

    cout<<"\n\nEnter the name of student (last name first) ";
    cin.ignore();
    cin.getline(studentName,LENGTHOFNAMES);

    for (int counter = 0; counter < numberOfProjects; counter++) {
        cout << "Enter mark in " <<  projectName[counter] << " out of  : " << projectValue[counter]  <<  "\t" ;
        cin>>projectMarks[counter];
    }// for

    calculateLetterGrade();
    cout << "\nGrade = " << letterGrade << endl;
}

void student::showOneStudentsData() const
{
    cout<<"\nID \t"<< studentIDNumber;
    cout<<"\nName\t"<<studentName << "\n" << endl;

    for (int counter = 0; counter < numberOfProjects; counter++) {
        cout<< projectMarks[counter]  << "\t "<< projectName[counter] << endl;
    }// for

    cout<<"\nPercentage\t"<<percentageMark;
    cout<<"\nLetter Grade\t" << letterGrade << endl;
}

void student::showTabular() const
{
    cout<<"\t"<< letterGrade <<"\t" << percentageMark <<"\t\t" <<  studentIDNumber<< "\t\t"<< studentName  << endl;
}

int  student::getStudentIDNumber() const
{
    return studentIDNumber;
}

 float student::getPercentageMark() const
 {
    return percentageMark;
 }

 char* student::getStudentName()
 {
    return(studentName);
 }

//***************************************************************
//    	THE MAIN FUNCTION
//****************************************************************

int main()
{

    course* courseData = new course(2);  // sort type by grade

    cout.setf(ios::fixed|ios::showpoint);
    cout<<setprecision(2); // program outputs decimal number to two decimal places

    introTitlePage();  // advertising

    system("clear"); // clear for Linux - substitute "cls" for Windows

    readSchoolData(courseData);  // look in a file or ask for school & class info

    mainMenu(courseData); // the big loop starts here

    return 0;
}

//***************************************************************
//    Read School and Class Data from a file
//****************************************************************

void readSchoolData(course *courseD)
{
    int numberOfLines = 0;

    ifstream infile("School.txt");
    string line = "";

    while (getline(infile, line)){
        stringstream strstr(line);
        string word = "";
        while (getline(strstr,word, ',')) {
            if (!numberOfLines){
               strcpy(courseD->schoolName,word.c_str());
                numberOfLines++;
            } else if (numberOfLines < 2){
                strcpy(courseD->courseName, word.c_str());
                numberOfLines++;
            } else {
                strcpy(courseD->courseNumber, word.c_str());
                numberOfLines++;
            }// if else
        } // while
    }// while

    infile.close();

    if (numberOfLines == 0){
        cout << "==================================================================" << endl;
        cout << " If you would prefer not to have to fill this in every time: " << endl;
        cout << " Create a text file called School.txt that contains three lines: " << endl;
        cout << " School Name \t\t[i.e. University of Alberta] \n Class Name \t\t[i.e. AutoCAD for the Theatre]" << endl;
        cout << " Class Designation \t[i.e T-DES 672]" << endl;
         cout << "===================================================================\n" << endl;
        courseD->setSchoolName();
        courseD->setcourseName();
        courseD->setcourseNumber();
    } // if else
}

//***************************************************************
//    	Write to file
//****************************************************************

void writeStudentData()
{
    student studentData;

    ofstream outFile;

    outFile.open("student.dat",ios::binary|ios::app);
    entryProjectSetup(&studentData); // Pre load the Project Names and values
    studentData.getStudentDataFromUser();
    outFile.write(reinterpret_cast<char *> (&studentData), sizeof(student));
    outFile.close();
    cout<<"\n\nStudent record Has Been Created ";

    cin.ignore();
    cin.get();
}

//***************************************************************
//    	Read all records from file
//****************************************************************

void displayAllStudentData()
{
    student studentData;

    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile) {
        cout<<"File could not be open !! Press any Key...";

        cin.ignore();
        cin.get();
        return;
    }// if
    cout<<"\n\n\tDISPLAY ALL STUDENT'S RECORDS\n\n";

    while(inFile.read(reinterpret_cast<char *> (&studentData), sizeof(student))) {
        studentData.showOneStudentsData();
        cout<<"\n====================================";
        cin.ignore();
        cin.get();
    }// while

    inFile.close();
}

//***************************************************************
//    	Read specific record from file
//****************************************************************

void displayOneStudentsData(int n)
{
    student studentData;

    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile) {
        cout<<"File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    } // if

    bool flag=false;

    while(inFile.read(reinterpret_cast<char *> (&studentData), sizeof(student))) {
        if(studentData.getStudentIDNumber()==n) {
            studentData.showOneStudentsData();
            flag=true;
        }// if
    }//while

    inFile.close();
    if(flag==false)
        cout<<"\n\nrecord does not exist";

    cin.ignore();
    cin.get();
}

//***************************************************************
//    	Modify record of file
//****************************************************************

void modifyOneStudentsData(int n)
{
    bool found=false;
    student studentData;
    fstream File;
    File.open("student.dat",ios::binary|ios::in|ios::out);
    if(!File) {
        cout<<"File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }// if

    while(!File.eof() && found==false) {
        File.read(reinterpret_cast<char *> (&studentData), sizeof(student));

        if(studentData.getStudentIDNumber()==n) {
            studentData.showOneStudentsData();
            cout<<"\n\nPlease Enter The New Details of student"<<endl;
            entryProjectSetup(&studentData); // Pre load the Project Names and values
            studentData.getStudentDataFromUser();
            int pos=(-1)*static_cast<int>(sizeof(studentData));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&studentData), sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=true;
        }// if
    }// while

    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";

    cin.ignore();
    cin.get();
}

//***************************************************************
//    	Delete record of file
//****************************************************************

void deleteOneStudent(int n)
{
    student studentData;

    ifstream inFile;
    inFile.open("student.dat",ios::binary);

    if(!inFile) {
        cout<<"File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }// if

    ofstream outFile;
    outFile.open("Temp.dat",ios::out);
    inFile.seekg(0,ios::beg);

    while(inFile.read(reinterpret_cast<char *> (&studentData), sizeof(student))) {
        if(studentData.getStudentIDNumber()!=n) {
            outFile.write(reinterpret_cast<char *> (&studentData), sizeof(student));
        }// if
    }// while

    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout<<"\n\n\tRecord Deleted ..";

    cin.ignore();
    cin.get();
}

//***************************************************************
//    	Display all students letter Grade report
//****************************************************************

void classDisplayAllTabular(course *courseD)
{
    student studentData;

    ifstream inFile;
    inFile.open("student.dat",ios::binary);

    if(!inFile) {
        cout<<"File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }// if

    cout <<'\t' << courseD->getSchoolName()<< endl;
    cout << '\t' << courseD->getcourseNumber() << " : " << courseD->getcourseName() << endl;

    cout<<"\n\n\tALL STUDENT'S RESULTS \n\n";
    cout<<"========================================================================\n";
    cout<<"\tGrade\tPrecentage\tID#\t\tName "<<endl;
    cout<<"========================================================================\n";

    while(inFile.read(reinterpret_cast<char *> (&studentData), sizeof(student))) {

        studentData.showTabular();
        cout<<"------------------------------------------------------------------------\n";
    }// while

    inFile.close();

    cin.ignore();
    cin.get();
 }

//***************************************************************
//    	INTRODUCTION TITLE PAGE
//****************************************************************

void introTitlePage()
{
    cout<<"\n\n\n\t\t  STUDENT REPORT DATABASE";
    cout<<"\n\n\n\tBY  : Tim M. M. Williamson";
    cout<<"\n\tFOR : University of Alberta - Department of Drama\n\n";

    cin.get();
}

//***************************************************************
//    	MENU FUNCTIONS
//****************************************************************

void mainMenu(course *courseD)
{
   char userMenuChoice;

    do {
        system("clear"); // clear for Linux - substitute cls for Windows


         cout <<'\t' << courseD->getSchoolName()<< endl;
         cout << '\t' << courseD->getcourseNumber() << " : " << courseD->getcourseName() << endl;

        cout<<"\n\tMAIN MENU";
        cout<<"\n\t==========";
        cout<<"\n\n\t1. Student Entry/Edit";
        cout<<"\n\n\t2. Raw Results Printout";
        cout<<"\n\n\t3. Tabular Sorted Results";
        cout<<"\n\n\t4. Exit";
        cout<<"\n\n\n\tPlease Select Your Option (1-4) ";

        cin>>userMenuChoice;

        switch(userMenuChoice) {
        case '1':
            entryMenu(courseD);
            break;
        case '2':
            resultMenu(courseD);
            break;
        case '3':
            sortOptionsMenu(courseD);
            break;
        case '4':
            break;
        default :
            cout<<"\a";
        }// switch
    } while(userMenuChoice != '4'); // do while loop
    system("clear"); // clear for Linux - substitute cls for Windows
}

void resultMenu(course *courseD)
{
    char userMenuChoice;
    int rno;

    system("clear"); // clear for Linux - substitute cls for Windows

    cout <<'\t' << courseD->getSchoolName()<< endl;
    cout << '\t' << courseD->getcourseNumber() << " : " << courseD->getcourseName() << endl;

    cout<<"\n\tRESULT MENU";
    cout<<"\n\t=============";
    cout<<"\n\n\t1. Class Raw Result";
    cout<<"\n\n\t2. Display All Student Records";
    cout<<"\n\n\t3. Student Report Card";
    cout<<"\n\n\t4. Back to Main Menu";
    cout<<"\n\n\n\tEnter Choice (1/2/3/4)? ";
    cin>>userMenuChoice;

    system("clear"); // clear for Linux - substitute cls for Windows

    switch(userMenuChoice) {
    case '1' :
        classDisplayAllTabular(courseD);
        break;
    case '2' :
        displayAllStudentData();
        break;
    case '3' :
        cout<<"\n\n\tEnter Student ID Number : ";
        cin>>rno;
        displayOneStudentsData(rno);
        break;
    case '4' :
        break;
    default:
        cout<<"\a";
    }// switch
}

void entryMenu(course *courseD)
{
    char userMenuChoice;
    int userEnteredID = 0;

    system("clear"); // clear for Linux - substitute cls for Windows

    cout <<'\t' << courseD->getSchoolName()<< endl;
    cout << '\t' << courseD->getcourseNumber() << " : " << courseD->getcourseName() << endl;

    cout<<"\n\tDATA ENTRY & MODIFY MENU";
    cout<<"\n\t==========================";
    cout<<"\n\n\t1. Create Student Record";
    cout<<"\n\n\t2. Display All Student Records";
    cout<<"\n\n\t3. Search Student Records";
    cout<<"\n\n\t4. Modify Student Record";
    cout<<"\n\n\t5. Delete Student Record";
    cout<<"\n\n\t6. Back To Main Menu";
    cout<<"\n\n\n\tPlease Enter Your Choice (1-6) ";
    cin>>userMenuChoice;

    system("clear"); // clear for Linux - substitute cls for Windows

    switch(userMenuChoice) {
    case '1':
        writeStudentData();
        break;
    case '2':
        displayAllStudentData();
        break;
    case '3':
        cout<<"\n\n\tPlease Enter The Student's ID number ";
        cin>>userEnteredID;
        displayOneStudentsData(userEnteredID);
        break;
    case '4':
        cout<<"\n\n\tPlease Enter Student's ID Number ";
        cin>>userEnteredID;
        modifyOneStudentsData(userEnteredID);
        break;
    case '5':
        cout<<"\n\n\tPlease Enter The Student's ID Number ";
        cin>>userEnteredID;
        deleteOneStudent(userEnteredID);
        break;
    case '6':
        break;
    default:
        cout<<"\a";
        entryMenu(courseD);
    }// switch
}

void sortOptionsMenu(course *courseD)
 {
   char userMenuChoice;

    system("clear"); // clear for Linux - substitute cls for Windows

    cout <<'\t' << courseD->getSchoolName()<< endl;
    cout << '\t' << courseD->getcourseNumber() << " : " << courseD->getcourseName() << endl;


    cout<<"\n\tTABULAR SORT OPTIONS MENU";
    cout<<"\n\t============================";
    cout<<"\n\n\t1. Name Sort";
    cout<<"\n\n\t2. By Grade";
    cout<<"\n\n\t3. By ID #";
    cout<<"\n\n\t4. Exit";
    cout<<"\n\n\n\tPlease Select Your Option (1-4) ";

    cin>>userMenuChoice;

    switch(userMenuChoice) {
        case '1':
            courseD->setSort(1);
            classSortAll(courseD);
            break;
        case '2':
            courseD->setSort(2);
            classSortAll(courseD);
            break;
        case '3':
            courseD->setSort(3);
            classSortAll(courseD);
            break;
        case '4':
            break;
        default :
            cout<<"\a";
            sortOptionsMenu(courseD);
    }// switch
 }

 //***************************************************************
//    	Student initial setup of Projects
//****************************************************************


void entryProjectSetup(student* projectList)	//set some things before we begin
{
    projectList->numberOfProjects = 0;

    // Project .txt file contains the name of the project and the value seperated by a coma per line
    // Formatting of this file is critical as there is NO error checking (yet):
    //"Stock Door",5
    //"Parallel Riser",5
    //"ISO Riser",20
    //"Two Flats",5

    int numberOfLines = 0;
    bool counter = 0;

    ifstream infile("Projects.txt");
    string line = "";

    while (getline(infile, line)){
        stringstream strstr(line);
        string word = "";
        while (getline(strstr,word, ',')) {
            if (!counter){
                strcpy(projectList->projectName[numberOfLines], word.c_str());
                counter = 1;
            } else{
                projectList->projectValue[numberOfLines] = stoi(word, nullptr, 10);
                counter = 0;
            }
        } // while
        numberOfLines ++;
    }// while

    infile.close();

    if (numberOfLines == 0){
        cout << "ERROR Unable to read the Projects.txt file" << endl;
        cout << "\tProject .txt file contains the name of the project and the value seperated by a coma per line." << endl;
        cout << "\tFormatting of this file is critical as there is NO error checking (yet):" << endl;
        cout << "\tStock Door,5" << endl;
        cout << "\tParallel Riser,5" << endl;
        cout << "\tISO Riser,20" << endl;
        cout << "\tTwo Flats,5" << endl;
        exit (EXIT_FAILURE);
    } else {
        projectList->numberOfProjects = numberOfLines;
    } // if else

}

 //***************************************************************
//    	SORTING TABULAR DATA
//****************************************************************


void classSortAll(course *courseD)
{
    system("clear"); // clear for Linux - substitute cls for Windows

    bool found = false;

    int countOfRecords = 0;
    int arrayCounter = 0;

    student studentData;

    fstream File;
    File.open("student.dat",ios::binary|ios::in|ios::out);
    if(!File) {
        cout<<"File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
    }// if

    while(!File.eof() && found==false) {
        File.read(reinterpret_cast<char *> (&studentData), sizeof(student));
        countOfRecords++;
    }// while
    countOfRecords--;

    File.clear();
    File.seekg(0, ios::beg);

    student* studentArray = new student[ countOfRecords * sizeof(student) ];

    while(!File.eof() && found==false && arrayCounter <  countOfRecords) {
        File.read(reinterpret_cast<char *> (&studentArray[arrayCounter]), sizeof(student));
        arrayCounter++;
    }// while

    File.close();

    int n = sizeof(student) * countOfRecords;

    arrayCounter = 0;
    cout <<'\t' << courseD->getSchoolName()<< endl;
    cout << '\t' << courseD->getcourseNumber() << " : " << courseD->getcourseName() << endl;

    cout<<"\n\n\tALL STUDENT'S RESULTS SORTED BY ";
    switch(courseD->getSort()){
    case 1:
        cout << "NAME.\n\n" ;
        bubbleSortByName( &studentArray[0], n, countOfRecords);
        break;
    case 2:
         cout << "GRADE PERCENTAGE\n\n" ;
         bubbleSortByGrade( &studentArray[0], n, countOfRecords);
        break;
    case 3:
        cout << "ID #\n\n" ;
        bubbleSortByID( &studentArray[0], n, countOfRecords);
        break;
    }// switch

    cout<<"========================================================================\n";
    cout<<"\tGrade\tPrecentage\tID#\t\tName "<<endl;
    cout<<"========================================================================\n";

    File.clear();
    File.seekg(0, ios::beg);

    while(!File.eof() && found==false && arrayCounter <  countOfRecords) {
        File.read(reinterpret_cast<char *> (&studentArray[arrayCounter]), sizeof(student));
        studentArray[arrayCounter].showTabular();
        cout<<"------------------------------------------------------------------------\n";
        arrayCounter++;
    }// while

    cin.ignore();
    cin.get();

    delete [] studentArray;

 }

 //***************************************************************
//    	BUBBLE SORTS - ID - GRADE - NAME
//****************************************************************


 void bubbleSortByID( student *studentA, int n, int countOfRecords)
 {
  int i, j;
    for (i = 0; i < countOfRecords; i++){
        for (j = 0; j < n-i-1; j++){
            if (studentA[j].getStudentIDNumber() > studentA[j+1].getStudentIDNumber()){
                if (studentA[j+1].getStudentIDNumber() == 0 ){
                    break;
                }// if
                swap(studentA[j], studentA[j+1]);
            }// if
         }// for j
    }// for i
}

 void bubbleSortByGrade( student *studentA, int n, int countOfRecords)
 {
  int i, j;
    for (i = 0; i < countOfRecords; i++){
        for (j = 0; j < n-i-1; j++){
            if (studentA[j].getPercentageMark() < studentA[j+1].getPercentageMark()){
                if (studentA[j+1].getPercentageMark() == 0 ){
                    break;
                }// if
                swap(studentA[j], studentA[j+1]);
            }// if
         }// for j
    }// for i
}

 void bubbleSortByName( student *studentA, int n, int countOfRecords)
 {
  int i, j;

    for (i = 0; i < countOfRecords; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if(compareTwoNames(&studentA[j], &studentA[j+1]))
            {
                if (studentA[j+1].getStudentIDNumber() == 0 )
                    break;
                swap(studentA[j], studentA[j+1]);
            }// if
         }// for j
    }// for i
}

bool compareTwoNames(student *xp, student *yp)
{
    int counter = 0;  //  used for the length of the for loop below

    int a = strlen(xp->getStudentName());
    int b = strlen(yp->getStudentName());
    counter = (a < b) ? a : b; // set counter to the shortest string

    for(int i = 0; i < counter; i++)    {
        if ( (int)toupper(xp->getStudentName()[i]) > (int)toupper(yp->getStudentName()[i]) ) {
            return true;
        } else if ( (int)toupper(xp->getStudentName()[i]) == (int)toupper(yp->getStudentName()[i]) )
        {
             if ( (int)toupper(xp->getStudentName()[i+1]) > (int)toupper(yp->getStudentName()[i+1]) )
                return true;
        } else if ( (int)toupper(xp->getStudentName()[i+1]) == (int)toupper(yp->getStudentName()[i+1]) )
        {
             if ( (int)toupper(xp->getStudentName()[i+2]) > (int)toupper(yp->getStudentName()[i+2]) )
                return true;
        } else
            return false;
    }// for
    return false;
}

void swap(student *xp, student *yp)
{
    student temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************

