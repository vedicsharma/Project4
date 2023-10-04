
#include <iostream>
#include <vector>
#include "Student.h"
#include <stack>
using namespace std;

class TreeNode
{
private:
    int height;
    Student stu;
    TreeNode* balanceTree(TreeNode* root);
    int findBfactor(TreeNode *root);
    TreeNode* rightRotation(TreeNode* root);
    TreeNode* leftRotation(TreeNode* root);
    int sumOfLevel(TreeNode* root, int level);
    TreeNode* twoNodeReplacer(TreeNode* root);
    void postOrderR(TreeNode* root);
    void preOrderR(TreeNode* root);
    vector<string> inOrderR(TreeNode* root);
    vector<int> inOrderInt(TreeNode* root);

public:
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(Student stu) : stu(stu.getID(), stu.getName()), left(nullptr), right(nullptr), height(1) {}


    TreeNode* findAndDelete(TreeNode* root, int ID);
    TreeNode* insert(TreeNode* root, Student data);
    bool searchID(TreeNode* root, int ID);
    bool searchIDSilent(TreeNode* root, int ID);
    int numberOfLevels(TreeNode* root);
    void postOrder(TreeNode* root);
    void preOrder(TreeNode* root);
    bool searchName(TreeNode* root, string name);
    vector<string> inOrder(TreeNode* root);
    TreeNode* inOrderDelete(TreeNode* root, int number);

};

// This will be called in main to construct the tree
TreeNode*TreeNode::insert(TreeNode* root, Student data)
{
    if (root == nullptr)
        return new TreeNode(data);
    if (root->stu.getID() < data.getID()) {
        root->right = insert(root->right, data);
        if(root->left == nullptr) {
            root->height = root->right->height + 1;
        }
        else{
            if(root->left->height < root->right->height){
                root->height = root->right->height + 1;
            }
        }
    }
    else {
        root->left = insert(root->left, data);
        if(root->right == nullptr) {
            root->height = root->left->height + 1;
        }
        else{
            if(root->right->height < root->left->height){
                root->height = root->left->height + 1;
            }
        }
    }
    //In balance tree, one thing to do is update the heights
    root = balanceTree(root);

    return root;
}

// This will be called in main to deallocate memory
void destruct(TreeNode* root)
{
    if (root->left)
        destruct(root->left);
    if (root->right)
        destruct(root->right);
    delete root;
}

int TreeNode::sumOfLevel(TreeNode* root, int level)
{
    int total = 0;
    int levelValue;
    std::vector<int> levelSums;

    if (level == 0){
        return root->stu.getID();
    }
    else {
        if (root->right != nullptr) {
            levelValue = sumOfLevel(root->right, level - 1);
            if (levelValue!=-1){
                total = total+levelValue;
            }
            //cout << total<<endl;
        }
        if (root->left != nullptr) {
            levelValue = sumOfLevel(root->left, level - 1);
            if (levelValue!=-1){
                total = total+levelValue;
            }
            //cout << total<<endl;

        }

    }
    if (total == 0){
        return -1;
    }
    //cout << total;
    return total;



    //code here
    return 0;
}

bool TreeNode::searchID(TreeNode* root, int ID) {
    bool nameFound;
    if (root == nullptr){
        return false;
    }

    if (root->stu.getID() == ID){
        nameFound = true;
        cout << root->stu.getName()<<endl;

    }

    else if (root->stu.getID() < ID)
        nameFound = searchID(root->right, ID);
    else
        nameFound = searchID(root->left, ID);

    return nameFound;
}

bool TreeNode::searchIDSilent(TreeNode* root, int ID) {
    bool nameFound;
    if (root == nullptr){
        return false;
    }

    if (root->stu.getID() == ID){
        nameFound = true;
        //cout << root->stu.getName()<<endl;

    }

    else if (root->stu.getID() < ID)
        nameFound = searchID(root->right, ID);
    else
        nameFound = searchID(root->left, ID);

    return nameFound;
}


int TreeNode::numberOfLevels(TreeNode *root) {
    if(root == nullptr){
        return 0;
    }
    else {
        return root->height;
    }
}

TreeNode *TreeNode::findAndDelete(TreeNode *root, int ID) {
    //TreeNode* nameRoot = root;
    if (root == nullptr){
        cout<<"unsuccessful"<<endl;
        return nullptr;
    }

    if (root->stu.getID() == ID){
        cout<<"successful"<<endl;
        if(root->left == nullptr and root->right == nullptr)
            return nullptr;
        else if (root->left != nullptr and root->right == nullptr){
            return root->left;
        }
        else if (root->right != nullptr and root->left == nullptr){
            return root->right;
        }
        else if (root->right != nullptr and root->left != nullptr){
            root = twoNodeReplacer(root);
            return root;
        }

        //root = deleteNode(root->left);
        return root;
    }

    else if (root->stu.getID() < ID)
        root->right = findAndDelete(root->right, ID);
    else
        root->left = findAndDelete(root->left, ID);

    return root;
}

TreeNode* TreeNode::twoNodeReplacer(TreeNode *root) {
    stack<TreeNode*> nodeStack;
    if(root->right->left == nullptr){
        root->stu = root->right->stu;
        if(root->right->right == nullptr){
            return nullptr;
        }
        else {
            TreeNode* temp = root->right->right;
            root->right->right = nullptr;
            root->right = temp;
            return root;
        }
    }
    nodeStack.push(root);
    nodeStack.push(root->right);
    //TreeNode* replacerNode = root->right;
    while(nodeStack.top()->left != nullptr){
        nodeStack.push(nodeStack.top()->left);
    }
    Student replacer = nodeStack.top()->stu;
    if(nodeStack.top()->right != nullptr){
        TreeNode* temp = nodeStack.top()->right;
        nodeStack.pop();
        nodeStack.top()->left = temp;
    }
    else{
        nodeStack.pop();
        nodeStack.top()->left= nullptr;
    }
    while (nodeStack.size() != 1){
        nodeStack.pop();
    }
    nodeStack.top()->stu = replacer;
    return nodeStack.top();
}

void TreeNode::postOrder(TreeNode *root) {
    stack<TreeNode*> treeStack;
    if (root == nullptr){
    }
    else{
        treeStack.push(root);
        while(treeStack.top()->left != nullptr){
            treeStack.push(treeStack.top()->left);
        }



        while (!treeStack.empty()) {
            if (treeStack.top()->right != nullptr) {
                postOrderR(treeStack.top()->right);
            }
            //cout << treeStack.top()->stu.getID() << ", height: " << treeStack.top()->height << endl;

            if(treeStack.size()>1) {
                cout << treeStack.top()->stu.getName() << ", ";
            }
            treeStack.pop();
        }

        cout << root->stu.getName() << endl;

    }

}

void TreeNode::postOrderR(TreeNode *root) {
    stack<TreeNode*> treeStack;
    if (root == nullptr){
    }
    else{
        treeStack.push(root);
        while(treeStack.top()->left != nullptr){
            treeStack.push(treeStack.top()->left);
        }


        while (!treeStack.empty()) {
            if (treeStack.top()->right != nullptr) {
                postOrderR(treeStack.top()->right);
            }
            //cout << treeStack.top()->stu.getID() << ", height: " << treeStack.top()->height << endl;


            cout << treeStack.top()->stu.getName() << ", ";
            treeStack.pop();
        }


    }

}

int TreeNode::findBfactor(TreeNode *root) {
    int rightBalance;
    int leftBalance;
    int balanceFactor;
    if(root->left == nullptr){
        leftBalance = 0;
    }
    else{
        leftBalance = root->left->height;
    }

    if(root->right == nullptr){
        rightBalance = 0;
    }
    else{
        rightBalance = root->right->height;
    }
    balanceFactor = leftBalance-rightBalance;
    return balanceFactor;
}

TreeNode *TreeNode::balanceTree(TreeNode *root) {
    TreeNode * balancedTree = root;
    int balanceFactor = findBfactor(root);
    //if balanceFactor positive then left skewed
    if(balanceFactor > 1){
        //find if trees right subtree is right heavy or left heavy
        int childBalance = findBfactor(root->left);
        if(childBalance > 0){
            balancedTree = rightRotation(root);
        }
        else if(childBalance < 0){
            balancedTree->left = leftRotation(root->left);
            balancedTree = rightRotation(balancedTree);
        }
        else{
            //cout<< "big problem!"<<endl;
            balancedTree = rightRotation(root);
        }
    }
    else if (balanceFactor < -1){
        //find if trees right subtree is right heavy or left heavy
        int childBalance = findBfactor(root->right);
        if(childBalance < 0){
            balancedTree = leftRotation(root);
        }
        else if(childBalance > 0){
            balancedTree->right = rightRotation(root->right);
            balancedTree = leftRotation(balancedTree);
        }
        else{
            //cout<< "big problem!"<<endl;
            balancedTree = leftRotation(root);
        }
    }
    else{
        return root;
    }

    return balancedTree;

}

TreeNode *TreeNode::leftRotation(TreeNode *root) {
    TreeNode * grandChild;
    TreeNode * newHead = root->right;
    if(root->right->left == nullptr){
        grandChild = nullptr;
        if(root->left == nullptr){
            root->height = 1;
        }
        else{
            root->height = root->left->height +1;
        }
    }
    else{
        grandChild = root->right->left;
        root->height = max(root->left->height, grandChild->height) +1;
    }
    newHead->left = root;
    root->right = grandChild;

    if(newHead->right == nullptr){
        newHead->height = newHead->left->height +1;
    }
    else {

        newHead->height = max(newHead->right->height, newHead->left->height) + 1;
    }
    return newHead;

}

TreeNode *TreeNode::rightRotation(TreeNode *root) {
    TreeNode * grandChild;
    TreeNode * newHead = root->left;
    if(root->left->right == nullptr){
        grandChild = nullptr;
        if(root->right == nullptr){
            root->height = 1;
        }
        else{
            root->height = root->right->height +1;
        }
    }
    else{
        grandChild = root->left->right;
        root->height = max(root->left->height, grandChild->height) +1;

    }
    newHead->right = root;
    root->left = grandChild;
    if(newHead->left == nullptr){
        newHead->height = newHead->right->height +1;
    }
    else {

        newHead->height = max(newHead->left->height, newHead->right->height) + 1;
    }
    return newHead;
}

void TreeNode::preOrder(TreeNode *root) {
    stack<TreeNode*> treeStack;
    if (root == nullptr){
    }
    else{
        treeStack.push(root);
        cout << treeStack.top()->stu.getName();
        while(treeStack.top()->left != nullptr){
            treeStack.push(treeStack.top()->left);
            cout <<", "<< treeStack.top()->stu.getName();
        }


        while (!treeStack.empty()) {
            if (treeStack.top()->right != nullptr) {
                preOrderR(treeStack.top()->right);
            }


            //cout << treeStack.top()->stu.getName() << ", ";
            treeStack.pop();
        }


    }
}

void TreeNode::preOrderR(TreeNode *root) {
    stack<TreeNode*> treeStack;
    if (root == nullptr){
    }
    else{
        treeStack.push(root);
        cout << ", " << treeStack.top()->stu.getName();
        while(treeStack.top()->left != nullptr){
            treeStack.push(treeStack.top()->left);
            cout <<", "<< treeStack.top()->stu.getName();
        }


        while (!treeStack.empty()) {
            if (treeStack.top()->right != nullptr) {
                preOrderR(treeStack.top()->right);
            }


            //cout << treeStack.top()->stu.getName() << ", ";
            treeStack.pop();
        }


    }
}

bool TreeNode::searchName(TreeNode * root, string name) {
    bool NameFound = false;
    stack<TreeNode*> treeStack;
    if (root == nullptr){
    }
    else{
        treeStack.push(root);
        if(treeStack.top()->stu.getName() == name) {
            cout << treeStack.top()->stu.getID() << endl;
            NameFound = true;
        }
        while(treeStack.top()->left != nullptr){
            treeStack.push(treeStack.top()->left);
            if(treeStack.top()->stu.getName() == name) {
                cout << treeStack.top()->stu.getID() << endl;
                NameFound = true;
            }
        }


        while (!treeStack.empty()) {
            if (treeStack.top()->right != nullptr) {
                bool NameFoundTemp = NameFound;
                NameFound = searchName(treeStack.top()->right, name);
                if (NameFoundTemp){
                    NameFound = true;
                }
            }


            //cout << treeStack.top()->stu.getName() << ", ";
            treeStack.pop();
        }


    }
    return NameFound;


}

vector<string> TreeNode::inOrder(TreeNode *root) {
    vector <string> values;
    stack<TreeNode*> treeStack;
    if (root == nullptr){
    }
    else{
        treeStack.push(root);
        while(treeStack.top()->left != nullptr){
            treeStack.push(treeStack.top()->left);
        }



        while (!treeStack.empty()) {
            if(treeStack.size()>0) {
                //cout << treeStack.top()->stu.getName() << ", ";
                values.push_back(treeStack.top()->stu.getName());
            }

            if (treeStack.top()->right != nullptr) {
                vector<string> temp = inOrder(treeStack.top()->right);
                for(int i=0; i<temp.size(); i++){
                    values.push_back(temp[i]);
                }
            }
            //cout << treeStack.top()->stu.getID() << ", height: " << treeStack.top()->height << endl;


            treeStack.pop();
        }

        //cout << root->stu.getName() << endl;

    }
    return values;
}

vector<int> TreeNode::inOrderInt(TreeNode *root) {
    vector <int> values;
    stack<TreeNode*> treeStack;
    if (root == nullptr){
    }
    else{
        treeStack.push(root);
        while(treeStack.top()->left != nullptr){
            treeStack.push(treeStack.top()->left);
        }



        while (!treeStack.empty()) {
            if(treeStack.size()>0) {
                //cout << treeStack.top()->stu.getName() << ", ";
                values.push_back(treeStack.top()->stu.getID());
            }

            if (treeStack.top()->right != nullptr) {
                vector<int> temp = inOrderInt(treeStack.top()->right);
                for(int i=0; i<temp.size(); i++){
                    values.push_back(temp[i]);
                }
            }
            //cout << treeStack.top()->stu.getID() << ", height: " << treeStack.top()->height << endl;


            treeStack.pop();
        }

        //cout << root->stu.getName() << endl;

    }
    return values;
}

vector<string> TreeNode::inOrderR(TreeNode *root) {

    vector<string> values;
    stack<TreeNode*> treeStack;
    if (root == nullptr){
    }
    else{
        treeStack.push(root);
        while(treeStack.top()->left != nullptr){
            treeStack.push(treeStack.top()->left);
        }


        while (!treeStack.empty()) {
            //cout << treeStack.top()->stu.getName() << ", ";
            values.push_back(treeStack.top()->stu.getName());

            if (treeStack.top()->right != nullptr) {
                vector<string> temp = inOrderR(treeStack.top()->right);
                for(int i=0; i<temp.size(); i++){
                    values.push_back(temp[i]);
                }
            }
            //cout << treeStack.top()->stu.getID() << ", height: " << treeStack.top()->height << endl;



            treeStack.pop();
        }


    }
    return values;
}

TreeNode *TreeNode::inOrderDelete(TreeNode *root, int number) {
    vector<int> inOrderArray = inOrderInt(root);
    if (inOrderArray.size()<= number){
        cout << "unsuccessful" << endl;
        return root;
    }
    else {
        int deleteValue = inOrderArray[number];
        TreeNode *result = findAndDelete(root, deleteValue);
        return result;
    }
}