#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

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
    doublyNode* head;
    public:
    miniGit();  // Constructor
    ~miniGit(); // Destructor
    
};