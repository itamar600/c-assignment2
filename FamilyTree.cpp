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
        if(this->rel==string("me"))
            this->father->rel="father";
        else if(this->rel==string("father"))
                this->father->rel="grandfather";
        else if(this->rel==string("mother"))
                this->father->rel="grandfather";
        else if(this->rel==string("grandfather"))
                this->father->rel="great-grandfather";
        else if(this->rel==string("grandmother"))
                this->father->rel="great-grandfather";
        else if(this->rel.find("grandfather")!=this->rel.npos)
                this->father->rel="great-"+this->rel;
        else if(this->rel.find("grandmother")!=this->rel.npos){
                size_t pos=this->rel.find("grandmother");
                char rela[pos+1];
                this->rel.copy(rela,pos+1,pos);
                this->father->rel="great-";
                for(int i=0; i<pos+1; i++)
                    this->rel+=rela[i];
                this->father->rel+="grandfather";
        }
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
        if(this->rel==string("me"))
            this->mother->rel="mother";
        else if(this->rel==string("father"))
            this->mother->rel="grandmother";
        else if(this->rel==string("mother"))
            this->mother->rel="grandmother";
        else if(this->rel==string("grandfather"))
            this->mother->rel="great-grandmother";
        else if(this->rel==string("grandmother"))
            this->mother->rel="great-grandmother";
        else if(this->rel.find("grandmother")!=this->rel.npos)
                this->father->rel="great-"+this->rel;
        else if(this->rel.find("grandmfather")!=this->rel.npos){
                size_t pos=this->rel.find("grandfather");
                char rela[pos+1];
                this->rel.copy(rela,pos+1,pos);
                this->father->rel="great-";
                for(int i=0; i<pos+1; i++)
                    this->rel+=rela[i];
                this->father->rel+="grandmother";
        }
    }
    if(this->father != NULL)
        this->father->addMother(childName,motherName);
    if(this->mother != NULL)
        this->mother->addMother(childName,motherName);
    return *this;
}

// void Tree::setRelation(string relation){
//     this->re=relation;
// }

Tree* findToRelation(Tree* root ,string name){

    if(root->getName() == string(name)) 
        return root;
    if(root->getFather()!= NULL){
        Tree* temp=findToRelation(root->getFather(), name);
        if(temp!=NULL)
            return temp; 
    }
    if(root->getMother()!=NULL)
        return findToRelation(root->getMother(), name);
    // The name not in the family tree
    return NULL;
}


string Tree::relation(string relationName ){
    Tree* temp=findToRelation(this, relationName);
    if(temp==NULL)
        return "unrelated";
    return temp->rel;
}
Tree* findToFind(Tree* root ,string relation){

    if(root->getRelation() == string(relation)) 
        return root;
     if(root->getFather()!= NULL){
        Tree* temp=findToFind(root->getFather(), relation);
        if(temp!=NULL)
            return temp; 
    }
    if(root->getMother()!=NULL)
        return findToFind(root->getMother(), relation);
    // The name not in the family tree
    return NULL;
}
string Tree::find(string relation){
    Tree* temp=findToFind(this,relation);
    if(temp == NULL)
        throw std::runtime_error("the relation doesnt exist!");
    return temp->name;
}
void recRemove(Tree* node){
    //came to leaf
    // if(node->getFather()== NULL && node->getMother() == NULL){
    //     delete node;
    //     return;
    // }
    if(node->getFather()!= NULL)
        recRemove(node->getFather());
    if(node->getMother()!= NULL)
        recRemove(node->getMother());
    //return;
    delete node;
}
Tree* findToRemove(Tree* root ,string name){
    //searching the child of who we want to remove
    //for changing the iterator for the parent to NULL
    if((root->getFather() != NULL && root->getFather()->getName() == string(name)) || 
    (root->getMother() != NULL && root->getMother()->getName() == string(name)))
        return root;
    if(root->getFather()!= NULL){
        Tree* temp=findToRemove(root->getFather(), name);
        if(temp!=NULL)
            return temp;
    }
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
    // bool isLeaf=true;
    //If is the father that need to be deleted
    if(childRemove->getFather()->getName() == string(name)){
        // if(childRemove->getFather()->getMother()!= NULL
        // || childRemove->getFather()->getFather()!= NULL)
        //     isLeaf=false;
        recRemove(childRemove->getFather());
        // if(!isLeaf)
        //     delete(childRemove->getFather());
        childRemove->father=NULL;
        return;
    }
    //If is the mother.. 
    if(childRemove->getMother()->getName() == string(name)){
        // if(childRemove->getMother()->getMother()!= NULL
        // || childRemove->getMother()->getFather()!= NULL)
        //     isLeaf=false;
        recRemove(childRemove->getMother());
        // if(!isLeaf)
        //     delete(childRemove->getMother());
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

