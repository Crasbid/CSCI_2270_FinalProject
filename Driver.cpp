#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <unistd.h>
#include "miniGit.hpp"

using namespace std;
namespace fs = std::filesystem;

void displayMenu();

int main(){

//create miniGit class
// miniGit mGit;

//variable initialization
// bool Correct_Char=false;
// char choice;
// string userInput;
// bool quit=false;
// string fname;
// int CommitNumber=0;

//cout << "==== Welcome To Mini-Git ====" << endl;

// while (Correct_Char==false){//loop through until given a valid input.
//     cout << "Inititalize a new repository? [Y/N]"<< endl;
    
//     cin>> choice;

//     switch (toupper(choice))
//     {

//         case 'Y': //user wants to create a new REPO
//             Correct_Char=true;
           
//             fs::remove_all(".minigit");
//             fs::create_directory(".minigit");
//             cout << "New Directory Created '.minigit'"<< endl;
//             break;
//         case 'N': //user wants to use an existing REPO
//             Correct_Char=true;
//             break;
//         default ://Invalid character is entered
//             if (Correct_Char==false){cout<< "Please Enter a valid Character"<< endl;}
//             break;
//         }
// }
// while(!quit){
//     displayMenu();
//     cin>>userInput;

//     switch (stoi(userInput)){

//         case 1:
//             bool result;
//             result=false;
//             while(!result){
//             cout<<"Enter name of file to be added to commit"<< endl;

//             cin>>fname;
//             result= mGit.gitAdd(fname,CommitNumber);
//            }
//             break;

//         case 2:     // Remove - Evan Hiemstra
//             cout << "Enter name of file to be removed from commit" << endl;
//             cin >> fname;
//             mGit.gitRemove(fname,CommitNumber);
//             break;

//         case 3:     // Commit - Evan Hiemstra
//             CommitNumber++;
//             cout << "Committing changes..." << endl;
//             mGit.gitCommit();
//             break;

//         case 5:
//             quit=true;
//             cout<< "Goodbye"<< endl;
//             break;
//         default:
//             cout << "Invalid Input" << endl;
//             break;
//     }
// }

    string opt, filename;
    bool init = false;

    cout << "==== Welcome To Mini-Git ====" << endl;
    cout << "Initialize new repository? (Y/N) > ";

    getline(cin, opt);

    while(init == false) {
        if(opt == "Y") {
            fs::remove_all(".minigit");
            fs::create_directory(".minigit");
            init = true;
        }
        else if(opt == "N") {
            init = true;
        }
        else {
            cout << "Please enter valid input: ";
            getline(cin, opt);
            cout << endl;
        }
    }

    miniGit git;

    displayMenu();

    while(true) {
        getline(cin, opt);

        if(opt == "1") {
            cout << "Enter the name of the file you would like to add: ";
            getline(cin, filename);
            cout << endl;
            git.gitAdd(filename);

            displayMenu();
        }
        else if(opt == "2") {
            cout << "Enter the name of the file you would like to remove: " << endl;
            getline(cin, filename);
            cout << endl;
            git.gitRemove(filename);

            displayMenu();
        }
        else if(opt == "3") {
            git.gitCommit();

            displayMenu();
        }
        else if(opt == "4") {
            
        }
        else if(opt == "5") {
            return 0;
        }
        else {
            cout << "Please enter a valid input" << endl;
        }
    }
}

void displayMenu() {
    cout << "==== Menu ====" << endl;
    cout << "1. Add Files to Current Commit" << endl;
    cout << "2. Remove Files from Current Commit"<< endl;
    cout << "3. Commit Changes"<< endl;
    cout << "4. Check Out Specific Version"<< endl;
    cout << "5. Quit"<< endl;
    cout << "> ";
}