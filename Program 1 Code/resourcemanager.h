#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <string>
#include <vector>

class node;

class resourceManager
{
public:
    resourceManager();
    ~resourceManager();
    std::vector<node*>& getResources();
    void deleteResource(std::string);
    void addLink(std::string,std::string);
    void print();
    void displayMenu();
    void loadNewFile(std::string&);
    
    void updateUsable(int);

private:
    // std::map<std::string,std::vector<std::string> > resourceMap;
    std::vector<node*> resources;
};

#endif
