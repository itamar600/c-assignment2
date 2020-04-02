#pragma once

#include <string>
#include <iostream>
using namespace std;


namespace family {
  class Tree{
    string name;
    Tree* father;
    Tree* mother;
      
    public:
    Tree(){
        name="";  
        father=NULL;
        mother=NULL; 
      }
    Tree(string name){
        this->name=name;
        father=NULL;
        mother=NULL;
      }
    public:
    string getName() { return name;  }
    // Tree& getFather() { return father;  }
    // Tree& getMother() { return mother;  }
    Tree& addFather(string childName,string fatherName);
    Tree& addMother(string childName,string motherName);
    string relation(string relationName );
    string find(string relation);
    void remove(string name);
    void display();
  };
};