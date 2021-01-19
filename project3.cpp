/*
* Bret Elphick
* CSC 230
* 11/13/20
* Project 3 - Read data from file that contains leading char, SSN, and name,
* throughout program keep track of time, # of inserts, # of deletions, # of retreivals, and # of entries in doubly linked list
* when get to the end of the file close the fstream and display the values
*/


#include "DLL.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>


using namespace std;

int main(int argc, char* argv[]) {
  clock_t start, end;
  double duration;

  start = clock();

  int insertionCount; 
  int deletionCount;
  int retrievalCount;
  int index;
  string ssn; 
  string name;
  string tempName;
  char firstChar; 
  fstream input(argv[1]);
  DLL list;

  insertionCount = 0;
  deletionCount = 0;
  retrievalCount = 0;

  // Read in data from one of the files
  while(!input.eof()){
      input >> firstChar;
      input >> ssn;
      input >> name;
      input >> tempName;
      
      tempName = name + " " + tempName;
      
      if (firstChar == 'i'){
        list.insert(ssn, name, insertionCount);
      }
      else if (firstChar == 'd'){
        list.remove(ssn, deletionCount);
      }
      else{
        index = list.search(ssn);
        if (index != -1){
          retrievalCount = retrievalCount + 1;
        }
      }
  }
  input.close();

  cout << "The Number of Valid Insertion: " << insertionCount << endl;
  cout << "The Number of Valid Deletion: " << deletionCount << endl;
  cout << "The Number of Valid Retrieval: " << retrievalCount << endl;
  cout << "Item numbers in the list: " << list.size() << endl;

  end = clock();
  duration = ( end - start ) / (double) CLOCKS_PER_SEC;

  cout<<"elapsed time: "<< duration <<'\n';
}