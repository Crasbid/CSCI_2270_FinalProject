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

void printCommit(doublyNode *head,int CommitNumber){// helper function that prints current list of commits
    cout<< "====================================="<< endl;
    cout<< endl << "Staged Changes: "<< endl;
    
    singlyNode *Commit;
    doublyNode *myCommit=head;
    while(myCommit !=NULL){//loop through doubly linked list to get to the correct commit number
        if(myCommit->commitNumber==CommitNumber){
            Commit=myCommit->head;
        }
        myCommit=myCommit->next;
    }


    while(Commit != NULL){
        cout<< Commit->fileName<< " ver: " << Commit->fileVersion<< endl;
        Commit=Commit->next;
    }
    cout<< endl<< "====================================="<< endl ;
}

int findVersionNumber(doublyNode *CommitSet, string filename, int CommitNumber){//helper function to find the version number of our commit
bool versionFound=false;
int prevVersion=0;
singlyNode * myFiles;

for(int i=0; i< CommitNumber;i++)
    while(CommitSet!=NULL){//loop through all of our previous commits
        myFiles=CommitSet->head;

        while(myFiles!=NULL){// loop through the files contained within a specific commit

            if(myFiles->fileName == filename){
                prevVersion = stoi(myFiles->fileVersion); 
                break;
            }
            else{
                myFiles=myFiles->next;
            }
        }
    }
    return prevVersion+1;
}

bool miniGit::gitAdd(string fileName,int CommitNumber){ //Created by: COLLIN Rasbid
    bool found=false;
    bool addedAlready=false;
    int fileIndex=-1;
    int version;
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
                    myFile->fileVersion="1";
                }
                else{

                    //check to see if file has been added to commit already:
                    myCommit=dhead;

                    while(myCommit !=NULL){//loop through doubly linked list to get to the correct commit number
                        

                        if(myCommit->commitNumber==CommitNumber){//if the DLL is the same commit number that we are on
                                myFile=myCommit->head; //sll starts at the head pointed to in dll
                                
                                while(myFile!=NULL){ // while sll is not null
                                    if(myFile->fileName==fileName){ //if filename in sll is the same as one staged for commmits mark it as added already
                                       
                                        addedAlready=true;
                                        break;
                                    }
                                    else{// otherwise keep looking for duplicate filename until we reach the end of our sll
                                        myFile=myFile->next; 
                                    }
                                }

                                break;     
                        }  
                         
                        else{// if we arent on the correct commit number iterate to the next one
                            myCommit=myCommit->next;
                        }

                    }
                    
                    if( !addedAlready){// if file has not been added already
                        myFile=dhead->head; // set sll as the head from the dll
                        singlyNode *newNode = new singlyNode;
                        
                        
                        if(myFile->next!=NULL){ // if the file isnt the last one in the sll
                            myFile=myFile->next; //iterate to the next file in the sll
                        }
                        // once last file has been found set the next one as our new entry
                        myFile->next=newNode;
                        newNode->fileName=fileName;
                        version=findVersionNumber(dhead,fileName,CommitNumber);
                        newNode->fileVersion=to_string(version);
                        // cout<< newNode->fileName << " Has been Committed "<< endl;
                    }   
                    else{cout<< endl<< "****File Already Commited****"<< endl<< endl;}

                    break;
                }
            }
        }
        if (found==true){//if the filename is included in the directory
           
           printCommit(dhead,CommitNumber);


        }
        else{
            cout<< "Filename Not Found please enter a valid filename"<< endl << endl;
            return false;
        }
    
    return true;
}