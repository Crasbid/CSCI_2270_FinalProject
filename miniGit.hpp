#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <unistd.h>

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
};


class miniGit {
    private:
    doublyNode* dhead;
    public:
    miniGit();  // Constructor
    void gitAdd(string fileName); //function to add a file to repository
    void gitRemove(string filename);
    void gitCommit();
    ~miniGit(); // Destructor

};