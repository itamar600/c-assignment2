#include <string>
#include <bits/stdc++.h>
#include "FamilyTree.hpp"
#define COUNT 10
using namespace family;


Tree& Tree::addFather(string childName,string fatherName){

    // if(this->relation(childName)==string("unrelated"))
    //     throw std::runtime_error("child not exists"); 
    bool *f= new bool();
    *f=false;
    recAddF(childName,fatherName, f);
    if(*f==false)
        throw std::runtime_error("child not exists");
    delete f;
    return *this;
}
void Tree::recAddF(string childName,string fatherName,bool* f){

    //the child was found
    if(this->name == string(childName)){
        *f=true;
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
                char rela[pos];
                this->rel.copy(rela,pos,0);
                this->father->rel="great-";
                for(int i=0; i<pos; i++)
                    this->father->rel+=rela[i];
                this->father->rel+="grandfather";
        }
        return;

    }
    if(this->father != NULL)
        this->father->recAddF(childName,fatherName, f);
    if(this->mother != NULL)
        this->mother->recAddF(childName,fatherName, f);
    return ;

}
Tree& Tree::addMother(string childName,string motherName){

    // if(this->relation(childName)==string("unrelated"))
    //     throw std::runtime_error("child not exists");
     bool *f=new bool();
    *f=false;
    recAddM(childName,motherName, f);
    if(*f==false)
        throw std::runtime_error("child not exists");
    delete f;
    return *this;
}
void Tree::recAddM(string childName,string motherName, bool* f){

    if(this->name == string(childName)){
        *f=true;
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

                this->mother->rel="great-"+this->rel;

        else if(this->rel.find("grandfather")!=this->rel.npos){
                size_t pos=this->rel.find("grandfather");
                char rela[pos];
                this->rel.copy(rela,pos,0);
                this->mother->rel="great-";
                for(int i=0; i<pos; i++)
                    this->mother->rel+=rela[i];
                this->mother->rel+="grandmother";
        }
        return;
    }
    if(this->father != NULL)
        this->father->recAddM(childName,motherName,f);
    if(this->mother != NULL)
        this->mother->recAddM(childName,motherName,f);

    return;
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
    if(root->getMother()!=NULL){
        Tree* temp=findToRelation(root->getMother(), name);
        if(temp!=NULL)
            return temp;
    }
        // return findToRelation(root->getMother(), name);
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
    if(node->getFather()== NULL && node->getMother()== NULL )
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
    if(childRemove->getFather()!=NULL && childRemove->getFather()->getName() == string(name)){
        // if(childRemove->getFather()->getMother()!= NULL
        // || childRemove->getFather()->getFather()!= NULL)
        //     isLeaf=false;
        Tree * temp=childRemove->getFather();
        childRemove->father=NULL;
        recRemove(temp);
        // if(!isLeaf)
        //     delete(childRemove->getFather());
        
        return;
    }
    //If is the mother.. 
    if(childRemove->getMother()!=NULL && childRemove->getMother()->getName() == string(name)){
        // if(childRemove->getMother()->getMother()!= NULL
        // || childRemove->getMother()->getFather()!= NULL)
        //     isLeaf=false;
        Tree* temp1=childRemove->getMother();
        childRemove->mother=NULL;
        recRemove(temp1);
        // if(!isLeaf)
        //     delete(childRemove->getMother());
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
