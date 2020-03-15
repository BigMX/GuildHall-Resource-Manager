#include "resourcemanager.h"
#include "filemanager.h"
#include "node.h"
#include <iostream>

resourceManager::resourceManager(){
    const char* filename = "resources.txt";
    fileManager::readfile(filename,resources);
}

resourceManager::~resourceManager(){
    for(int i=0;i<this->resources.size();i++){
        delete resources[i];
    }
}

void resourceManager::print(){
    for(int i =0;i<resources.size();i++){
        this->resources[i]->print();
    }
}

void resourceManager::deleteResource(std::string resource){
    for(int i =0;i<resources.size();i++){
        if(resources[i]->nodeName==resource){
            resources[i]->isUsable=false;
            updateUsable(i);
            break;
        }
    }
    
//    std::cout<<"USABLE ITEM: ";
//    for(int i =0;i<resources.size();i++){
//        if(resources[i]->isUsable){
//            std::cout<<resources[i]->nodeName<<" ";
//        }
//    }
//    std::cout<<"\n";
}

void resourceManager::addLink(std::string resource, std::string dependency){
    int resourceIndex = -1;
    int dependencyIndex = -1;
    for(int i =0;i<resources.size();i++){
        if(resources[i]->nodeName==resource){
            resourceIndex = i;
        }
        if(resources[i]->nodeName==dependency){
            dependencyIndex = i;
        }
        if(resourceIndex != -1 && dependencyIndex != -1){
             break;
        }
    }
    if(resourceIndex == -1){
        resources.push_back(new node(resource));
        resourceIndex = resources.size()-1;
    }
    if(dependencyIndex == -1){
        resources.push_back(new node(dependency));
        dependencyIndex = resources.size()-1;
    }
    resources[resourceIndex]->addDependency(resources[dependencyIndex]);
    resources[dependencyIndex]->addParent(resources[resourceIndex]);
}

void resourceManager::updateUsable(int index){
//    std::cout<<index;
    for(int j = 0;j<resources[index]->parents.size();j++){
        if(resources[index]->parents[j]->isUsable){
            resources[index]->parents[j]->isUsable=false;
            int parentIndex = -1;
            for(int ind =0;ind<this->resources.size();ind++){
                if(resources[ind]->nodeName==resources[index]->parents[j]->nodeName){
                    parentIndex=ind;
                    break;
                }
            }
            std::cout<<parentIndex;
            updateUsable(parentIndex);
        }
    }
}

void resourceManager::displayMenu(){
    std::string menuChoice = "USER CHOICE";
    // while()
}

std::vector<node*>& resourceManager::getResources(){
    return this->resources;
}

void resourceManager::loadNewFile(std::string & newFile){
    for(int i=0;i<resources.size();i++){
        delete resources[i];
    }
    resources.clear();
    fileManager::readfile(newFile.c_str(),resources);
}
