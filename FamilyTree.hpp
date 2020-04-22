#pragma once

#include <string>
#include <iostream>
using namespace std;


namespace family {
  class Tree{
    string name;
    string relation;
    Tree* father;
    Tree* mother;
      
    public:
    Tree(){
        name="";
        relation="";  
        father=NULL;
        mother=NULL; 
      }
    Tree(string name){
        this->name=name;
        relation="";
        father=NULL;
        mother=NULL;
      }
    public:
    string getName() { return this->name;  }
    Tree* getFather() { return this->father;  }
    Tree* getMother() { return this->mother;  }
    Tree& addFather(string childName,string fatherName);
    Tree& addMother(string childName,string motherName);
    void setRelation(string relation);
    string relation(string relationName );
    string find(string relation);
    void remove(string name);
    void display();
  };
};