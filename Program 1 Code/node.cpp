#include "node.h"
#include <iostream>


node::node(){

}

node::node(std::string nodeName){
    this->nodeName = nodeName;
    this->isUsable = true;
}

void node::addDependency(node* dependencyNode){
    this->dependencies.push_back(dependencyNode);
}

void node::addParent(node* parentNode){
    this->parents.push_back(parentNode);
}

void node::print(){
    std::cout<<this->nodeName<<"--";
    for(int i =0; i< this->dependencies.size();i++){
        std::cout<<this->dependencies[i]->nodeName;
        if(i!=this->dependencies.size()-1){
            std::cout<<",";
        }
    }
    std::cout<<"\n";
}
