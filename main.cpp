//*****************************************************************************
// COMSC-210 | Lab 37 | Gabriel Marquez
// Description: this program progressively creates a hash table using a std::map
// and std::list
//*****************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <list>
using namespace std;

int gen_hash_index(const string&);

const string FILE_NAME = "lab-37-data.txt";

int main() {
    //declare hash table
    //key = int, the hash index
    //value = list<string>, the hexadecimal strings from lab-37-data.txt
    map<int, list<string>> hash_table;

    int index = 0;
    string input;
    ifstream fin(FILE_NAME);
    if (fin.good( )) {
        while (fin >> input) {
            index = gen_hash_index(input);
            //add index & string to hash table
            hash_table[index].push_back(input);
        }
        fin.close( );
    }
    else {
        cout << "ERROR! Please verify file name/directory and restart program.";
        return 1;
    }

    //output first 100 map entries
    for (int i = 0; i < 100; i++) {
        
    }

    return 0;
}

/* 
These targets are present in the dataset and can be used for testing:
536B9DFC93AF
1DA9D64D02A0
666D109AA22E
E1D2665B21EA
*/

//description: gen_hash_index() receives a string and returns the sum of that
// string's character's ASCII values, used as a hash index for a hash table
//arguments: a string passed by constant reference
//returns: an int representng the sum of the string's character's ASCII values
int gen_hash_index(const string &str) {
    int count = 0;
    for (auto &s : str) {
        count += (int) s;
    }
    return count;
}