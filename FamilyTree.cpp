#include <string>
#include <bits/stdc++.h>
#include "FamilyTree.hpp"
#define COUNT 10
using namespace family;

Tree& Tree::addFather(string childName,string fatherName){
    //the child was found
    if(this->name == string(childName)){
        //cant changing father name
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
    //came to leaf
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
    //searching the child of who we want to remove
    //for changing the iterator for the parent to NULL
    if((root->getFather() != NULL && root->getFather()->getName() == string(name)) || 
    (root->getMother() != NULL && root->getMother()->getName() == string(name)))
        return root;
    if(root->getFather()!= NULL)
        return findToRemove(root->getFather(), name);
    if(root->getMother()!=NULL)
        return findToRemove(root->getMother(), name);
    // The name not in the family tree
    return NULL;
}
void Tree::remove(string name){
    if(this->getName() == string(name)){
        throw std::runtime_error("Can't delete root!");
    }
    Tree* childRemove= findToRemove(this, name);
    if(childRemove == NULL)
        throw std::runtime_error("The name not found!");
    //This variable is for deletion, because if the name that need 
    //to remove is a leaf, so recRemove delete him, but if not we
    //need to delete him hear.
    bool isLeaf=true;
    //If is the father that need to be deleted
    if(childRemove->getFather()->getName() == string(name)){
        if(childRemove->getFather()->getMother()!= NULL
        || childRemove->getFather()->getFather()!= NULL)
            isLeaf=false;
        recRemove(childRemove->getFather());
        if(!isLeaf)
            delete(childRemove->getFather());
        childRemove->father=NULL;
        return;
    }
    //If is the mother.. 
    if(childRemove->getMother()->getName() == string(name)){
        if(childRemove->getMother()->getMother()!= NULL
        || childRemove->getMother()->getFather()!= NULL)
            isLeaf=false;
        recRemove(childRemove->getMother());
        if(!isLeaf)
            delete(childRemove->getMother());
        childRemove->mother=NULL;
        return;
    }

}
//This algorithm i took from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
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
}

