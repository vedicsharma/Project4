#include <iostream>
#include "Student.h"
#include "Tree.h"

using namespace std;
//class Student;
/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

// stoi in Student and addName needs a catch funtion if string is in place of number

struct Tree{
    TreeNode* tree;
};

bool checkIfValid(string Name){
    for(int i = 0; i<Name.size(); i++){
        char a = Name[i];
        if (!isalpha(a) and a != ' '){
            return false;
        }
    }
    return true;
}

bool addName(string student, Tree* tree){
    string quotation = "\"";
    string name;
    string number;
    if (student.substr(0,1) != quotation){
        return false;
    }
    for(int i = 1; i < student.size(); i++) {
        string letter = student.substr(i,1);
        if (quotation == letter){
            name = student.substr(1,i-1);
            if (student.size() < i+2){
                number = "";
            }
            else {
                number = student.substr(i + 2, student.size() - (i));
            }
            break;
        }
    }
    if(name.empty()){
        return false;
    }
    if(!checkIfValid(name)){
        return false;
    }

    if (number.size() != 8){
        return false;
    }


    Student stu;
    stu.setName(name);
    if(!stu.setID(number)){
        return false;
    }
    int num = stu.getID();
    if (tree->tree->searchIDSilent(tree->tree, num) ){
        return false;
    }

    tree->tree =tree->tree->insert(tree->tree,stu);
    //cout <<"done";



    return true;
}

bool search(int stringID, Tree* tree){
    //int ID = stoi(stringID);
    if (tree->tree->searchID(tree->tree, stringID) ){
        return true;
    }
    else
        return false;
}

bool search(string student, Tree* tree) {
    string quotation = "\"";
    string name ="";
    //cout << "here";
    bool success;
    if (student.substr(0, 1) != quotation) {
        return false;
    }
    for (int i = 1; i < student.size(); i++) {
        string letter = student.substr(i, 1);
        if (quotation == letter) {
            name = student.substr(1, i - 1);
        }
    }
    if (name.empty()){
        return false;
    }
    //cout << name;
    success = tree->tree->searchName(tree->tree, name);
    return success;
}

bool deleteID(string stringID, Tree* tree){
    try {
        int ID = stoi(stringID);
        tree->tree = tree->tree->findAndDelete(tree->tree, ID);
    }
    catch(std::invalid_argument){
        cout << "unsuccessful" << endl;
    }

}

bool deleteInorder(string stringID, Tree* tree){
    try {
        int ID = stoi(stringID);
        tree->tree = tree->tree->inOrderDelete(tree->tree, ID);
    }
    catch(std::invalid_argument){
        cout << "unsuccessful" << endl;
    }
    return true;
}

int LevelCount(Tree* tree){
    int a = tree->tree->numberOfLevels(tree->tree);
    return a;
}

bool interpretCommand(string Input, Tree *tree){

    string space = " ";
    bool success = true;
    string commandString = Input;
    string remainingString = "";
    if (Input.empty()){
        cout <<"unsuccessful"<<endl;
        return false;
    }

    for(int i = 0; i < Input.size(); i++) {
        string letter = Input.substr(i,1);
        if (space == letter){
            commandString = Input.substr(0,i);
            remainingString = Input.substr(i+1, Input.size()-(i));
            break;
        }
    }

    if (commandString == "insert"){
        //cout << "yea";
        success = addName(remainingString, tree);
        if(!success){
            cout <<"unsuccessful"<<endl;
            return false;
        }
        cout <<"successful"<<endl;
        return true;
    }

    if (commandString == "search") {
        if(remainingString.size() == 8) {
            try {
                int ID = stoi(remainingString);
                success = search(ID, tree);
                if (!success) {
                    cout << "unsuccessful" << endl;
                    return false;
                }
                //cout << "successful" << endl;
                return true;
            }
            catch (std::invalid_argument) {
                success = search(remainingString, tree);
                if (!success) {
                    cout << "unsuccessful" << endl;
                    return false;
                } else {
                    return true;
                }
            }
        }
        else{
            success = search(remainingString, tree);
            if (!success) {
                cout << "unsuccessful" << endl;
                return false;
            } else {
                return true;
            }
        }
    }

    if (commandString == "printLevelCount"){
        int a = LevelCount(tree);
        cout << a << endl;
        return true;
    }

    if (commandString == "printPostorder"){
        tree->tree->postOrder(tree->tree);
        return true;
    }

    if (commandString == "printPreorder"){
        tree->tree->preOrder(tree->tree);
        cout << endl;
        return true;
    }

    if (commandString == "printInorder"){
        vector<string> values;
        values = tree->tree->inOrder(tree->tree);
        for(int i=0; i<values.size()-1; i++){
            cout << values[i] << ", ";
        }
        cout << values[values.size()-1] << endl;
        return true;
    }

    if (commandString == "remove"){
        deleteID(remainingString, tree);
        //tree->tree = tree->tree->findAndDelete(tree->tree, 20);
        //printPostOrder(tree);
        return true;
    }

    if (commandString == "removeInorder"){
        deleteInorder(remainingString, tree);
        //tree->tree = tree->tree->inOrderDelete(tree->tree, 20);
        //printPostOrder(tree);
        return true;
    }


    cout <<"unsuccessful"<<endl;
    return false;

}

void askQuestions(int numLines){
    string clearfield = "";
    getline(cin, clearfield);

    Tree tree;
    tree.tree = nullptr;

    //TreeNode* tree = nullptr;

    for (int i=0; i<numLines;i++){
        string nextInput = "";
        getline(cin, nextInput);
        bool success = interpretCommand(nextInput, &tree);

    }


    //int x = tree.tree->sumOfLevel(tree.tree,0);
    //cout << x;
}

int findLineNums(){
    int numLines = 0;
    cin >> numLines;
    cin.clear();
    return numLines;
}

int main(){
    int numLines = findLineNums();
    askQuestions(numLines);

    return 0;
}
