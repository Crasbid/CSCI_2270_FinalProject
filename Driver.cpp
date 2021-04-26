#include<iostream>
#include<fstream>
#include<cstdlib>
#include<filesystem>
#include <string>
#include <vector>
#include <dirent.h>
#include "miniGit.hpp"

using namespace std;
namespace fs = std::filesystem;

void displayMenu() {
    cout << "==== Menu ====" << endl;
    cout << "1. Add Files to Current Commit" << endl;
    cout << "2. Remove Files from Current Commit"<< endl;
    cout << "3. Commit Changes"<< endl;
    cout << "4. Check Out Specific Version"<< endl;
    cout << "5. Quit"<< endl;
    cout << "> ";
}

int main(int argc, char** argv){

//create miniGit class
     miniGit mGit;
//variable initialization
bool Correct_Char=false;
char choice;
string userInput;
bool quit=false;
string fname;
int CommitNumber=0;

cout << "==== Welcome To Mini-Git ====" << endl;

while (Correct_Char==false){//loop through until given a valid input.
    cout << "Inititalize a new repository? [Y/N]"<< endl;
    
    cin>> choice;

    switch (toupper(choice))
    {

        case 'Y': //user wants to create a new REPO
            Correct_Char=true;
           
            fs::remove_all(".minigit");
            fs::create_directory(".minigit");
            cout << "New Directory Created '.minigit'"<< endl;
            break;
        case 'N': //user wants to use an existing REPO
            Correct_Char=true;
            break;
        default ://Invalid character is entered
            if (Correct_Char==false){cout<< "Please Enter a valid Character"<< endl;}
            break;
        }
}
while(!quit){
    displayMenu();
    cin>>userInput;

    switch (stoi(userInput)){

        case 1:
            bool result;
            result=false;
            while(!result){
            cout<<"Enter name of file to be added to commit"<< endl;

            cin>>fname;
            result= mGit.gitAdd(fname,CommitNumber);
           }
            break;

        case 2:     // Remove - Evan Hiemstra
            cout << "Enter name of file to be removed from commit" << endl;
            cin >> fname;
            mGit.gitRemove(fname,CommitNumber);
            break;

        case 3:     // Commit - Evan Hiemstra
            CommitNumber++;
            cout << "Committing changes..." << endl;
            mGit.gitCommit();
            break;

        case 5:
            quit=true;
            cout<< "Goodbye"<< endl;
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
    }
}
    return 0;
}