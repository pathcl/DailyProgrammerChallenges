/** 
 *  @file    solution1.cpp
 *  @author  Ibar Romay 
 *  @github  rowmatrix  
 *  @date    10/15/2016 
 *  
 *  @brief ask user for name, age, and reddit username; log information in file
 *
 *
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string name, reddit_username;
    int age;

    //prompt user for inputs
    cout << "Please enter your name: ";
    cin >> name;

    cout << "Please enter your age: ";
    cin >> age;
    //check if age is an integer
    if( cin.fail() ){
        cout << "Not an integer" << endl;
        return 1;
    }

    cout << "Please enter your reddit username: ";
    cin >> reddit_username;

    //print results to terminal
    cout << "your name is " << name;
    cout << ", you are " << age << " years old, ";
    cout << "and your username is " << reddit_username << endl;

    //store results in file
    ofstream ofile ("results.txt");
    if( ofile.is_open() ){
        ofile << name << "\n";
        ofile << age << "\n";
        ofile << reddit_username << "\n";
        ofile.close();
    }
    else {
        cout << "Unable to open file" << endl;
        return 1;
    }

    return 0;
}