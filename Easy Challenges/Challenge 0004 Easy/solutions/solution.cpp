/** 
 *  @file    solution.cpp
 *  @author  Ibar Romay 
 *  @github  rowmatrix  
 *  @date    10/15/2016 
 *  
 *  @brief random password generator
 *              - allow user to specify the amount of passwords to generate
 *              - allow user to specify the length of strings
 *
 *
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

/** 
 *  @param  len: length of password to generate
 */ 
string password_generator(int len)
{
    string password;
    for( int i=0; i < len; i++ )
    {
        char letter;
        letter = char(rand() % 26 + 97); // letter in range 97-122
        password += letter; 
    }
    return password;
}

int main(int argc, char const *argv[])
{
    srand( time(NULL) ); // initialize random seed

    int num_passwords;
    cout << "Number of passwords to generate: ";
    cin >> num_passwords;

    int password_length;
    cout << "Length of each password: ";
    cin >> password_length;

    for( int i=0; i < num_passwords; i++ )
    {
        cout << password_generator(password_length) << endl;
    }

    return 0;
}