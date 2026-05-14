//*****************************************************************************
// COMSC-210 | Lab 37 | Gabriel Marquez
// Description: this program progressively creates a hash table using a std::map
// and std::list
//*****************************************************************************

#include <iostream>
using namespace std;

int sum_ascii(const string&);

int main() {
    string str = "bob";
    int sum = sum_ascii(str);

    cout << "The sum of the values in " << str << " is " << sum;    

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