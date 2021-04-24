#include<iostream>
#include<filesystem>
#include <string>
using namespace std;


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
cout << "==== Welcome To Mini-Git ====" << endl;

cout << "Inititalize a new repository? [Y/N]"<< endl;
char choice;
cin>> choice;

switch (toupper(choice))
{

    case 'Y': //user wants to create a new REPO


    case 'N': //user wants to use an existing REPO


}
    return 0;
}