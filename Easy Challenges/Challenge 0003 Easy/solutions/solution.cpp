/** 
 *  @file    solution.cpp
 *  @author  Ibar Romay 
 *  @github  rowmatrix  
 *  @date    10/15/2016 
 *  
 *  @brief alphabetical cesar cipher to encrypt and decrypt messages
 *
 *  
 */

#include <iostream>
#include <string> 
#include <cstdlib>
using namespace std;

string encrypt(string, int);
string decrypt(string, int);


int main(int argc, char *argv[])
{
    /**
     *  options:
     *    e - encrypt message
     *    d - decrypt message
     *    k - key/shift for ceasar cipher
     */

    string message;
    int key;
    char *option;

    if( argc < 4 ){
        cerr << "Usage: ./solution <message/text> <e/d> <k>" << endl;
        return 1;
    } 

    message = argv[1]; 
    option  = argv[2];
    key     = atoi( argv[3] );

    if( option[0] == 'e' or option[0] == 'E' ){
        cout << "encryption" << " key = " << key << endl;
        cout << encrypt(message, key) << endl;
    }
    else if( option[0] == 'd' or option[0] == 'D' ){
        cout << "decryption" << " key = " << key << endl;
        cout << decrypt(message, key) << endl;
    }
    else {
        cout << "e or d was not accepted" << endl;
    }

    return 0;
}

string encrypt(string msg, int key){
    string result_str;
    
    for( string::size_type i = 0; i < msg.size(); i++ ){
        char letter = msg[i];
        letter = letter + key;
        if( letter > 122 ){
            int overlap_shift = letter - 122;
            letter = 97 + overlap_shift - 1;
        }
        result_str += letter;
    }

    return result_str;
}

string decrypt(string msg, int key){
    string result_str;
    
    for( string::size_type i = 0; i < msg.size(); i++ ){
        char letter = msg[i];
        letter = letter - key;
        if( letter < 97 ){
            int overlap_shift = 97 - letter;
            letter = 122 - overlap_shift + 1;
        }
        result_str += letter;
    }

    return result_str;
}