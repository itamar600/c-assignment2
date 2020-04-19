#include <string>
#include <bits/stdc++.h>
#include "FamilyTree.hpp"
#define COUNT 10
using namespace family;

Tree& Tree::addFather(string childName,string fatherName){
    if(this->name == string(childName)){
        if(this->father != NULL)
            throw std::runtime_error("Father exists");
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
        if(this->mother != NULL)
            throw std::runtime_error("Mother exists");
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
void recRemove(Tree* node){
    if(node->getFather()== NULL && node->getMother() == NULL){
        delete node;
        return;
    }
    if(node->getFather()!= NULL)
        recRemove(node->getFather());
    if(node->getMother()!= NULL)
        recRemove(node->getMother());
    return;
}
Tree* findToRemove(Tree* root ,string name){
    if((root->getFather() != NULL && root->getFather()->getName() == string(name)) || 
    (root->getMother() != NULL && root->getMother()->getName() == string(name)))
        return root;
    if(root->getFather()!= NULL)
        return findToRemove(root->getFather(), name);
    if(root->getMother()!=NULL)
        return findToRemove(root->getMother(), name);
    return NULL;
}
void Tree::remove(string name){
    if(this->getName() == string(name)){
        throw std::runtime_error("Can't delete root!");
    }
    Tree* sunRemove= findToRemove(this, name);
    if(sunRemove == NULL)
        throw std::runtime_error("The name not found!");
    if(sunRemove->getFather()->getName() == string(name)){
        recRemove(sunRemove->getFather());
        sunRemove->father=NULL;
        return;
    }
    if(sunRemove->getMother()->getName() == string(name)){
        recRemove(sunRemove->getMother());
        sunRemove->mother=NULL;
        return;
    }

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

