#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <dirent.h>

using namespace std;

struct singlyNode {
    std::string fileName;    // Name of local file
    std::string fileVersion; // Name of file in .minigit folder
    singlyNode * next;
};
struct doublyNode{
    int commitNumber;
    singlyNode * head;
    doublyNode * previous;
    doublyNode * next;
    bool committed;// tracks weather or not commit is being staged or has been fully committed
};



class miniGit {
    private:
    doublyNode* dhead;
    public:
    miniGit();  // Constructor
    bool gitAdd(string fileName,int CommitNumber); //funciton to add a file to repository
    ~miniGit(); // Destructor

};