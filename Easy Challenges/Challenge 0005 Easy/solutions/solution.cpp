/** 
 *  @file    solution.cpp
 *  @author  Ibar Romay 
 *  @github  rowmatrix  
 *  @date    10/15/2016 
 *  
 *  @brief password protected program
 *
 *
 */

#include <iostream>
#include <string>
using namespace std;

bool check(string username, string password)
{
    string correct_username = "hot";
    string correct_password = "dog";

    return (username == correct_username) && (password == correct_password);
}

int main(int argc, char const *argv[])
{
    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    while( !check(username,password) )
    {
        cout << "Incorrect! Try again." << endl;
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;
    }

    cout << "Correct!" << endl;

    return 0;
}