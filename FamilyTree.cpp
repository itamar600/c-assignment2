#include <string>
#include<bits/stdc++.h>
#include "FamilyTree.hpp"
#define COUNT 10
using namespace family;

Tree& Tree::addFather(string childName,string fatherName){
    if(this->name == string(childName)){
        Tree* father = new Tree(fatherName);
        this->father= father;
        return *this;
    }
    if(this->father != NULL)
        this->father->addFather(childName,fatherName);
    if(this->mother != NULL)
        this->mother->addFather(childName,fatherName);
    return *this;
}
Tree& Tree::addMother(string childName,string motherName){
    if(this->name == string(childName)){
        Tree* mother = new Tree(motherName);
        this->mother= mother;
        return *this;
    }
    if(this->father != NULL)
        this->father->addMother(childName,motherName);
    if(this->mother != NULL)
        this->mother->addMother(childName,motherName);
    return *this;
}
string Tree::relation(string relationName ){
    return "Part A";
}
string Tree::find(string relation){
    return "Part A";
}
void Tree::remove(string name){
    
}
void recDisplay(Tree* root, int space){
    if(root == NULL)
        return;
    space+=COUNT;
    cout << endl;
    recDisplay(root->getFather(), space);
    for(int i=COUNT; i< space; i++)
        cout << " ";
    cout << root->getName() << "\n";
    recDisplay(root->getMother(), space);

}

void Tree::display(){
    recDisplay(this, 0);
    // string display= string(this->name);
    // Tree* iter=this;
    // while(iter->father!=NULL){
    //     display+="\n   |\n   |\n"+ iter->father->name;
    //     iter=this->father;
    // }
    // cout << display << endl;  
}

