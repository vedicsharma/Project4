//
// Created by Vinod Sharma on 1/30/23.
//

#include "Student.h"



void Student::setName(string inputName)
{
    //cout << inputName<<endl;
    name = inputName;
}

bool Student::setID(string inputID)
{
    //cout << inputID;

    int size = inputID.size();
    int id;
    for(int i =0; i<size; i++) {

        try {
            id = stoi(inputID.substr(i,1));
            StudentID = id;
        }
        catch (std::invalid_argument) {
            return false;
        }
    }
    id = stoi(inputID);
    StudentID = id;
    return true;

}

int Student::getID() {
    return StudentID;
}

string Student::getName() {
    return name;
}

Student::Student(int ID, string name) {
    StudentID=ID;
    setName(name);

}

Student::Student() {

}
