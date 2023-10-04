//
// Created by Vinod Sharma on 1/30/23.
//
#include <iostream>
#ifndef PROJECT1_STUDENT_H
#define PROJECT1_STUDENT_H
using namespace std;

class Student {
private:
    int StudentID;
    string name;

public:
    Student();
    Student(int StudentID, string name);
    void setName(string inputName);
    bool setID(string Inputname);
    int getID();
    string getName();
    //bool Failure = false;
};


#endif //PROJECT1_STUDENT_H

