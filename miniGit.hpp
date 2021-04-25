#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

struct doublyNode{
    int commitNumber;
    singlyNode * head;
    doublyNode * previous;
    doublyNode * next;
};

struct singlyNode {
    std::string fileName;    // Name of local file
    std::string fileVersion; // Name of file in .minigit folder
    singlyNode * next;
};

class miniGit {
    public:
    miniGit();  // Constructor

    ~miniGit(); // Destructor
};