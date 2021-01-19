/*
* Bret Elphick
* CSC 230
* 11/13/20
* DLL- Implementation for doubly linked list class,
* consists of constructor, getHeadPtr, copy constrcutor, destructor, 
* search, insert, remove, size, and display functions
*/

#include "DLL.h"
#include <iostream>
#include <string>

using namespace std;

// default constructor is already implemented
// do not modify the default constructor
DLL::DLL(){
    headPtr = nullptr;
    itemCount=0;
}

// return the head pointer of the list
// it is already implemented, do not modify it
Node* DLL::getHeadPtr(){
    return headPtr;
}

// copy construct, which copies an existing list n
// the new list is a different object from n
// the new list and object n have the same contents
// Please implement it
DLL::DLL(DLL& n){
    // copy value of itemCount
    itemCount = n.itemCount;
  
    // makes a deep copy of the linked list
    if (n.headPtr != nullptr){
        Node *tail; // points to last node in list
        Node *temp = n.headPtr;
        headPtr = new Node;

        Node *newNode = new Node;
        newNode->ssn = temp->ssn;
        newNode->name = temp->name;
        newNode->succ = nullptr;
        newNode->pred = nullptr;

        headPtr = newNode;
        tail = newNode;

        temp = temp->succ;
        while (temp != nullptr){
            Node *newNode = new Node;
            newNode->ssn = temp->ssn;
            newNode->name = temp->name;
            newNode->succ = nullptr;
            newNode->pred = nullptr;
            
            newNode->pred = tail;
            tail->succ = newNode;
            tail = newNode;
            
            temp = temp->succ;
        }
    }
} 

// destructor
// release every node of the list
// Please implement it
DLL::~DLL(){
    Node* temp1 = headPtr;
    while (temp1 != NULL){
        Node *temp2 = temp1->succ;
        delete temp1;
        temp1 = temp2;
    }
}

// if some node has SSN matcthes string ss
// return the index value of the node
// the index value of the first node is 0, the second node is 1, etc.
// if there is no node matching ss, return -1
int DLL::search(string ss)const{
    int index = 0;
    Node *temp;
    temp = headPtr;

    while(temp != NULL){
        if (ss == temp->ssn){
            return index;
        }
        index = index + 1;
        temp = temp->succ;
    }
    return -1;
}


// insert (ss, name) to the existing list
// the SSN values in each node are organized in INCREASING order
// if there is a node matching ss value, return false; otherwise true
// else create a node with (ss, name), insert the node to the proper position
// parameter count is the counter of number of valid insertion
// when you implement this method, consider the following situations:
// 1. list is empty
// 2. node should be inserted to the beginning of the list
// 3. node should be inserted to the middle of the list
// 4. node should be inserted to the end of the list
bool DLL::insert(string ss, string name, int & count){
    
    Node *newNode = new Node;
    newNode->name = name;
    newNode->ssn = ss;
    newNode->succ = nullptr;
    newNode->pred = nullptr;

    Node *temp1 = headPtr;

    // checks for case that the list is empty
    if (temp1 == nullptr){
        headPtr = newNode;
        count = count + 1;
        itemCount = itemCount + 1;
        return true;
    }
    // checks for case of inserting node at the beginning
    else if(temp1->ssn > newNode->ssn){
        newNode->succ = temp1;
        temp1->pred = newNode;
        headPtr = newNode;
        count = count + 1;
        itemCount = itemCount + 1;
        return true;

    }
    else{
        Node *temp2 = headPtr->succ;
        // check if headPtr is equal to the new node, if it is return false
        if (temp1->ssn == newNode->ssn){
            return false;
        }
        // parse through the linked list until an ssn is found that is greater than newNode ssn, leave loop when found
        // if at any point a node in the list has an equal ssn to newNode return false
        while(temp2 != nullptr){
            if (temp2->ssn == newNode->ssn){
                return false;
            }
            if (temp2->ssn > newNode->ssn){
                break;
            }
            temp1 = temp1->succ;
            temp2 = temp2->succ;
        }
        // temp1 is the predecessor to newNode and temp2 is the successor to newNode
        
        // update pointers (both of these pointers should be updated regardless if inserting in middle or end)
        temp1->succ = newNode;
        newNode->pred = temp1;

        // check for case of inserting node in the middle of two other nodes
        if (temp2 != nullptr){
            temp2->pred = newNode;
            newNode->succ = temp2;
            count = count + 1;
            itemCount = itemCount + 1;
            return true;
        }
        // checks for case of inserting the node at the end
        else{
            count = count + 1;
            itemCount = itemCount + 1;
            return true;
        }
    }
}


// remove node containing ss value
// if there is no node containing ss, return false; otherwise true
// consider the following situations:
// 1. list is empty
// 2. node containing ss value is the first node
// 3. node containing ss value is in the middle of the list
// 4. node containing ss value is the last node of the list
bool DLL::remove(string ss, int & count){
    Node *temp1 = headPtr;
     
    // case of removing node from an empty list
    if (temp1 == nullptr){
        return false;
    }
    // case of removing the first node of the list
    else if (temp1->ssn == ss){
        // case of removing a node from list of size 1 
        if (itemCount == 1){
            delete headPtr;
            headPtr = nullptr;
            count = count + 1;
            itemCount = itemCount - 1;
            return true;
        }
        delete headPtr;
        headPtr = temp1->succ;
        count = count + 1;
        itemCount = itemCount - 1;
        return true;
    }
    else{
        Node *temp2 = headPtr->succ;
        // parse through nodes in list until node is found with matching ssn
        while(temp2 != nullptr){
            if (temp2->ssn == ss){
                break;
            }
            temp1 = temp1->succ;
            temp2 = temp2->succ;
        }
        // if the entire list was searched and no matching node was found, return false
        if (temp2 == nullptr){
            return false;
        }
        else{
            // case of removing a node in the middle of the list
            if ((temp2->ssn == ss) && (temp2->succ != nullptr)){
                temp1->succ = temp2->succ;
                temp2->succ->pred = temp1;
                delete temp2;
                count = count + 1;
                itemCount = itemCount - 1;
                return true; 
            }
            // case of removing the last node in the linked list
            else{
                temp1->succ = nullptr;
                delete temp2; 
                count = count + 1;
                itemCount = itemCount - 1;
                return true;
            }
        }
    }
}


// return the number of the nodes
// it is already implemented, do not modify it
int DLL::size(){
    return itemCount;
}

// iterate through each node
// print out SSN and memory address of each node
// do not modify this method
void DLL::display(){
    Node* temp;
    temp = headPtr;
    while (temp!= nullptr) {
        cout << temp->ssn << "\t" << temp << endl;
        temp = temp->succ;
    }
}