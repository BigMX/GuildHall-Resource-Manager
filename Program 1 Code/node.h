#ifndef NODE_H
#define NODE_H

#include <map>
#include <vector>
#include <string>

class node
{
public:
    node();
    node(std::string);

    std::vector<node*> dependencies;
    std::vector<node*> parents;
    std::string nodeName;
    void print();
    void addDependency(node*);
    void addParent(node*);
    bool isUsable;
private:
};

#endif // DIJKSTRASEARCH_H
