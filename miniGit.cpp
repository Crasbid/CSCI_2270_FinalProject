#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <dirent.h>
#include "miniGit.hpp"
using namespace std;

miniGit::miniGit() {
    doublyNode* head = NULL;
}

miniGit::~miniGit() {
    // TODO
}

bool miniGit::gitAdd(string fileName){
    bool found=false;
    int fileIndex=-1;
    DIR *dir; struct dirent *diread;
    vector<string> files;

    if ((dir = opendir("/mnt/d/OneDrive/Collin/School/CSCI 2270 Data Structures/FinalProject/CSCI_2270_FinalProject")) != nullptr) {//to work correctly on local machine, must change this to your directory
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir (dir);
    }
        for (int i=0;i< files.size();i++){
            // cout << "File: "<< files[i] <<" Input Filename: "<< fileName<< "| "<< endl;
           
            if(files[i] == fileName){
                fileIndex=i;
                cout<< "Enter TRUE"<< endl;
                found=true;
                break;
            }
        }
        if (found==true){//if the filename is included in the directory
            cout<< "Filename Found"<< endl;
        }
        else{
            cout<< "Filename Not Found please enter a valid filename"<< endl << endl;
            return false;
        }
    
    return true;
}