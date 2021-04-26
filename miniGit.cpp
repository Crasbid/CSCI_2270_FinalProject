#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <unistd.h>
#include "miniGit.hpp"

using namespace std;

miniGit::miniGit() {    // Constructor - Evan Hiemstra
    dhead=NULL;
}
miniGit::~miniGit() {       // Destructor - Evan Hiemstra
    if(dhead != NULL) {
        doublyNode* dnode = dhead;

        while(dnode != NULL) {
            doublyNode* dnext = dnode->next;

            if(dnode->head != NULL) {
                singlyNode* prev = dnode->head;
                singlyNode* pres = prev->next;

                while(pres != NULL) {
                    delete prev;
                    prev = nullptr;

                    prev = pres;
                    pres = pres->next;
                }

                delete prev;
                prev = nullptr;
                dnode->head = NULL;
            }

            delete dnode;
            dnode = nullptr;

            dnode = dnext;
        }

        dhead = NULL;
    }
}

void printSL(singlyNode* root) {    // Prints the current SLL - Evan Hiemstra
    cout << "Current SL:" << endl;
    while(root != NULL) {
        cout << root->fileName << endl;
        root = root->next;
    }
    cout << endl;
}

void miniGit::gitAdd(string filename) {     // Adds/stages files WIP - Evan Hiemstra
    ifstream fin(filename);
    if(fin.is_open()) { // check if file exists
        fin.close();

        if(dhead == NULL) { // If this is first file to be staged
            doublyNode* dn = new doublyNode;
            dn->commitNumber = 0;
            dn->next = NULL;
            dn->previous = NULL;
            dhead = dn;

            singlyNode* nn = new singlyNode;
            nn->fileName = filename;
            nn->fileVersion = "00_" + filename;
            nn->next = NULL;

            dhead->head = nn;

            printSL(dhead->head);
        }
        else {

            doublyNode* dpres = dhead;

            // check if in SLL
            if(dpres->head != NULL) {
                singlyNode* pres = dpres->head;
                while(pres->next != NULL) {
                    if(pres->fileName == filename) {
                        cout << "File with same name cannot be added twice" << endl;
                        return;
                    }

                    pres = pres->next;
                }

                // otherwise add to end of SLL
                singlyNode* nn = new singlyNode;
                nn->fileName = filename;
                nn->fileVersion = "00_" + filename;
                //nn->fileVersion = getVersion(dpres,pres) + filename;  NEED TO IMPLEMENT
                nn->next = NULL;

                pres->next = nn;
            }
            else {  // if after commit 0
                singlyNode* nn = new singlyNode;
                nn->fileName = filename;
                nn->fileVersion = "00_" + filename;
                nn->next = NULL;

                dpres->head = nn;
            }
            printSL(dpres->head);
        }
    }
    else {
        cout << "Invalid file name, please enter valid name: " << endl;
        getline(cin, filename);
        cout << endl;
        gitAdd(filename);
    }
}

void miniGit::gitRemove(string filename) {      // Remove file from staging - Evan Hiemstra
    if(dhead == NULL || dhead->head == NULL) {
        cout << "No files to remove" << endl;
        return;
    }

    doublyNode* dpres = dhead;

    singlyNode* trav = dpres->head;

    while(trav != NULL) {
        if(trav->fileName == filename) {
            cout << "File found, deleting..." << endl;
            
            // Deleting the node
            if(dpres->head->fileName == filename) {     // head case
                singlyNode* temp = new singlyNode;
                temp = trav;
                dpres->head = trav->next;

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
            cout << "File deleted" << endl << endl;
            printSL(dpres->head);
            return;
        }
        trav = trav->next;
    }
    cout << "File not found" << endl;
}

void miniGit::gitCommit() {     // Commit staged files & versioning WIP - Evan Hiemstra
    if(dhead == NULL || dhead->head == NULL) {
        cout << "nothing to commit yet" << endl;
        return;
    }

    doublyNode* travCommit = dhead;

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

    // Create new commit DLL node and set as new head
    doublyNode* dn = new doublyNode;
    dn->commitNumber = travCommit->commitNumber + 1;
    dn->head = NULL;
    dn->next = NULL;
    dn->previous = travCommit;
    dhead = dn;
}