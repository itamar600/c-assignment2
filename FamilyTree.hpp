#pragma once

#include <string>
#include <iostream>
using namespace std;


namespace family {
  class Tree{
    string name;
    string rel;
    Tree* father;
    Tree* mother;
      
    public:
    Tree(){
        name="";
        rel="";  
        father=NULL;
        mother=NULL; 
      }
    Tree(string name){
        this->name=name;
        rel="me";
        father=NULL;
        mother=NULL;
      }
    public:
    string getName() { return this->name;  }
    Tree* getFather() { return this->father;  }
    Tree* getMother() { return this->mother;  }
    Tree& addFather(string childName,string fatherName);
    Tree& addMother(string childName,string motherName);
    void recAddF(string childName,string fatherName, bool* f);
    void recAddM(string childName,string motherName, bool* f);
    string getRelation(){return this->rel;};
    string relation(string relationName );
    string find(string relation);
    void remove(string name);
    void display();
  };
  #pragma once

#include <string>
#include <iostream>
using namespace std;


namespace family {
  class Tree{
    string name;
    string rel;
    Tree* father;
    Tree* mother;
      
    public:
    Tree(){
        name="";
        rel="";  
        father=NULL;
        mother=NULL; 
      }
    Tree(string name){
        this->name=name;
        rel="me";
        father=NULL;
        mother=NULL;
      }
    public:
    string getName() { return this->name;  }
    Tree* getFather() { return this->father;  }
    Tree* getMother() { return this->mother;  }
    Tree& addFather(string childName,string fatherName);
    Tree& addMother(string childName,string motherName);
    void recAddF(string childName,string fatherName, bool* f);
    void recAddM(string childName,string motherName, bool* f);
    string getRelation(){return this->rel;};
    string relation(string relationName );
    string find(string relation);
    void remove(string name);
    void display();
  };
};
