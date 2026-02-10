#include "Course.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

course* createCourse(string name, string location,  int credithrs, int sectionNum){
    //create the new course
    course* newcourse = new course;

    newcourse->name = name;
    newcourse->location = location;
    newcourse->num_credit_hrs = credithrs;
    newcourse-> num_sections = sectionNum;
    //section array
    newcourse ->sections = new string[sectionNum];
    
    //return the new course
    return newcourse;
}

void destroyCourse(course* myCourse){
    delete[] myCourse->sections;
    delete myCourse;
}

void printCourse(course* myCourse){
    //print all of the data
    cout << setw(25) << left <<  "\nCourse Name:" << right << myCourse->name;
    cout << setw(25) << left <<  "\nCourse Location:" << right << myCourse->location;
    cout << setw(25) << left <<  "\nCourse Hours:" << right << myCourse->num_credit_hrs;
    cout << setw(25) << left <<  "\nCourse Sections:" << endl;
    for(int i=0; i< myCourse->num_sections; i++){ // print each crn for the class
       cout << setw(27) << right << myCourse->sections[i] <<endl;
    }

}