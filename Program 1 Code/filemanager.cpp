
#include "filemanager.h"
#include <fstream>
#include <iostream>
#include "node.h"

// std::map<char, char> my_map = {
//     { 'A', '1' },
//     { 'B', '2' },
//     { 'C', '3' }
// };

fileManager::fileManager(){
}

fileManager::fileManager(char s){
}

void fileManager::readfile(const char* filename, std::vector<node*>& resources){
    std::ifstream file(filename);
    if (file) {
        std::string resource,dependency;
        while(!file.eof()){
            file>>resource>>dependency;
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
            // if (resourceMap.find(resource) == resourceMap.end() )
            // {
            //     std::vector<std::string> dependencies;
            //     dependencies.push_back(dependency);
            //     resourceMap[resource] = dependencies;
            // }else{
            //     resourceMap[resource].push_back(dependency);
            // }
            std::cout<<resource<<dependency<<std::endl;
        }
    }
    else {
        std::cerr << "Couldn't open " << filename << " for reading\n";
    }

    file.close();

}
