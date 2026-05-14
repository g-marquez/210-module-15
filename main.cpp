//*****************************************************************************
// COMSC-210 | Lab 37 | Gabriel Marquez
// Description: this program progressively creates a hash table using a std::map
// and std::list
//*****************************************************************************

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int sum_ascii(const string&);

const string FILE_NAME = "lab-37-data.txt";

int main() {
    string str = "bob";
    int sum = sum_ascii(str);

    cout << "The sum of the values in " << str << " is " << sum << endl;
    
    int total = 0;
    string input;
    ifstream fin(FILE_NAME);
    if (fin.good( )) {
        while (fin >> input) {
            total += sum_ascii(input);
        }
        fin.close( );
    }
    else {
        cout << "ERROR! Please verify file name/directory and restart program.";
        return 1;
    }

    cout << "Grand total of all ASCII values in the entire file: " << total;

    return 0;
}

/* 
These targets are present in the dataset and can be used for testing:
536B9DFC93AF
1DA9D64D02A0
666D109AA22E
E1D2665B21EA
*/

//description: sum_ascii() receives a single string and returns the sum of that
// string's character's ASCII values
//arguments: a string passed by constant reference
//returns: an int representng the sum of the string's character's ASCII values
int sum_ascii(const string &str) {
    int count = 0;
    for (auto &s : str) {
        count += (int) s;
    }
    return count;
}