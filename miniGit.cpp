#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <dirent.h>
#include <unistd.h>
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

string VersionNameCreate(int Version, string fileName){
    string versionName;

    if(Version < 10){
        versionName="0"+to_string(Version)+"_"+fileName;
    }
    else{
        versionName=to_string(Version)+"_"+fileName;
    }

    return versionName;
}


string getVersion(doublyNode*root, string filename){
    cout<< "==========Entered GetVersion==========="<< endl<< endl;
    //traverse through previous dll to find any previous versions
    doublyNode * current;
    singlyNode * commitFile;
    string fileVer;
    int Ver;
    current=root;
    // cout<< "Flag1"<< endl;
    while(current->previous!=NULL){// if there is no previous dll node to begin with then version will always be 00_
        // cout<< "flag2"<< endl;
        current=root->previous;
        commitFile=current->head;// set to first file in commit
        if (commitFile->fileName==filename){//file found in previous commit
            // cout<< "flag3"<< endl;
            fileVer.append(commitFile->fileVersion,0,2);
            
            Ver=stoi(fileVer)+1;
            

            if (Ver<10){
                fileVer="0"+to_string(Ver)+"_";
                // cout<< "Ver: "<< Ver<< endl;
            }
            else{
                
                fileVer=to_string(Ver)+"_";
                // cout<< "Ver: "<< Ver<< endl;
            }
            // cout<< "fileVer: "<< fileVer<<endl;
            return fileVer;
        }
        else{
            // cout<< "flag4"<< endl;
            if(commitFile->next!=NULL){
            commitFile=commitFile->next;
            }
            else break;

        }
        current=current->previous;//decrement to a previous commit
    }   



    return fileVer="00_";
}


void miniGit::gitAdd(string filename) {     // Adds/stages files WIP - Evan Hiemstra
    ifstream fin(filename);
    if(fin.is_open()) { // check if file exists
        fin.close();

    DIR *dir; struct dirent *diread;
    vector<string> files;

    //get_current_dir_name()
    char tmp[256];
    if ((dir = opendir(getcwd(tmp, 256))) != nullptr) {// FIXED - EH
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
                    myFile->fileVersion="01_"+fileName;
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

            // check if in SLL
            if(dpres->head != NULL) {
                // cout<<"Flag1"<< endl;
                singlyNode* pres = dpres->head;
                while(pres->next != NULL) {
                    // cout<<"Flag2 pres Filename: "<< pres->fileName<< "filename of add: "<<filename<< endl;
                    if(pres->fileName == filename) {
                        // cout<< "Flag3"<< endl;
                        cout << "File with same name cannot be added twice" << endl;
                        return;
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
                        newNode->fileVersion = VersionNameCreate(version,fileName);
                        // cout<< newNode->fileName << " Has been Committed "<< endl;
                    }   
                    else{cout<< endl<< "****File Already Commited****"<< endl<< endl;}

                    break;
                }
            }
        }
        if (found==true){//if the filename is included in the directory
           
           printCommit(dhead,CommitNumber);

                if(pres->fileName == filename) {
                    // cout<< "Flag3"<< endl;
                    cout << "File with same name cannot be added twice" << endl;
                    return;
                }

                // otherwise add to end of SLL
                singlyNode* nn = new singlyNode;
                nn->fileName = filename;
                nn->fileVersion = "00_" + filename;
                nn->fileVersion = getVersion(dpres,filename) + filename; 
                nn->next = NULL;

                pres->next = nn;
            }
            else {  // if after commit 0
                singlyNode* nn = new singlyNode;
                nn->fileName = filename;
                nn->fileVersion = "00_" + filename;
                nn->fileVersion = getVersion(dpres,filename) + filename; 
                nn->next = NULL;

                dpres->head = nn;
            }
            printSL(dpres->head);
        }
        else{
            cout<< "Filename Not Found please enter a valid filename"<< endl << endl;
            return false;
        }
    
    return true;
}

void miniGit::gitRemove(string filename, int Commitnumber) {
    if(dhead == NULL || dhead->head == NULL) {
        cout << "No files to remove" << endl;
        return;
    }

    singlyNode* trav = dhead->head;

    while(trav != NULL) {
        if(trav->fileName == filename) {
            cout << "File found, deleting..." << endl;
            
            // Deleting the node
            if(dhead->head->fileName == filename) {     // head case
                singlyNode* temp = new singlyNode;
                temp = trav;
                dhead->head = trav->next;

                delete temp;
                temp = nullptr;
            }
            else {
                singlyNode* prev = new singlyNode;
                singlyNode* pres = new singlyNode;
                prev = dhead->head;
                pres = prev->next;

                while(pres != trav) {
                    prev = prev->next;
                    pres = pres->next;
                }
                prev->next = pres->next;

                delete pres;
                pres = nullptr;
            }
            printCommit(dhead,Commitnumber);
            cout << "File deleted" << endl;
            return;
        }
        trav = trav->next;
    }
    cout << "File not found" << endl;
}

void miniGit::gitCommit() {
    if(dhead == NULL) {
        return;
    }
    doublyNode* travCommit = dhead;
    while(travCommit->next != NULL) {    // traverse to end of commit list
        travCommit = travCommit->next;
    }

    chdir(".minigit");

    // taverse the SLL
    singlyNode* trav = travCommit->head;
    while(trav != NULL) {

        ifstream fin(trav->fileVersion);
        if(fin.is_open()) {
            cout << "file is already there" << endl;
            ostringstream ss;
            ss << fin.rdbuf();
            string str1 = ss.str();
            fin.close();

            chdir("..");
            ifstream fin(trav->fileName);
            ss << fin.rdbuf();
            string str2 = ss.str();
            fin.close();
            chdir(".minigit");


        }
        else {
            cout << "file needs to be created" << endl;
            ofstream fout(trav->fileVersion);

            chdir("..");
            ifstream fin(trav->fileName);
            chdir(".minigit");

            fout << fin.rdbuf();

            fin.close();
            fout.close();
        }

        trav = trav->next;
    }

    chdir("..");
}