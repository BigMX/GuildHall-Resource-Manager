#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <map>
#include <vector>
#include <string>

class node;

class fileManager
{
public:
    fileManager();
    fileManager(char);
    static void readfile(const char*,std::vector<node*>&);
    static void writefile(const char*);
private:
};

#endif // DIJKSTRASEARCH_H
