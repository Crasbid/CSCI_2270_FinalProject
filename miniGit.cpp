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
    dhead=NULL;
    
}
miniGit::~miniGit() {
    // TODO
}

void printCommit(doublyNode *Commit){// helper function that prints current list of commits
    cout<< "Staged Changes: "<< endl;
    while(Commit != NULL){
        cout<< Commit->head->fileName<< endl;
        Commit=Commit->next;
    }

}

bool miniGit::gitAdd(string fileName){ //Created by: COLLIN Rasbid
    bool found=false;
    bool addedAlready=false;
    int fileIndex=-1;
    
    doublyNode *myCommit =new doublyNode;
    singlyNode *myFile= new singlyNode;

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
           
            if(files[i] == fileName){ // if file is contained within local directory
                fileIndex=i;
                found=true;
                
                if(dhead==NULL){//if dhead is null repository is empty and no commits have been made yet
                    dhead= new doublyNode;
                    dhead->next=NULL;
                    dhead->previous=NULL;
                    dhead->commitNumber=0;//initial commit of repository is set as zeroth commit
                    dhead->committed=false;
                    
                    dhead->head=myFile;
                    myFile->fileName=fileName;
                }
                else{
                    //find how many commits have been made already




                    //check to see if file has been added to commit already:
                    while(myCommit->head=NULL){
                        if(myCommit->head->fileName==fileName){
                            addedAlready=true;
                            cout <<"File has been added to Commits already"<< endl;
                            break;
                        }
                    }
                    
                    if( !addedAlready){// if file has not been added already
                        

                    }

                    break;
                }
            }
        }
        if (found==true){//if the filename is included in the directory
            printCommit(dhead);
        }
        else{
            cout<< "Filename Not Found please enter a valid filename"<< endl << endl;
            return false;
        }
    
    return true;
}