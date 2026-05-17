//*****************************************************************************
// COMSC-210 | Lab 38 | Gabriel Marquez
// Description: this program progressively creates a hash table using a std::map
// and std::list
//*****************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <algorithm> //for find() (line 211)
using namespace std;

int gen_hash_index(const string&);
int main_menu();
bool key_check(const map<int, list<string>> &, string);
void print_entries(const map<int, list<string>> &);
void search_key(const map<int, list<string>> &);
void add_key(map<int, list<string>> &);
void remove_key(map<int, list<string>> &);
void modify_key(map<int, list<string>> &);

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

    //display main menu for program
    int choice = main_menu();
    while (choice != 6) {
        //input vaidated in main_menu() function
        switch (choice) {
            case 1: print_entries(hash_table); break;
            //will get updated with each milestone
            case 2: search_key(hash_table); break;
            case 3: add_key(hash_table); break;
            case 4: remove_key(hash_table); break;
            case 5: modify_key(hash_table); break;
        }
        choice = main_menu();
    }
    cout << "Goodbye" << endl;

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

//description: main_menu() displays the menu options that give the user options
// of what do do in the program
//arguments: N/A
//returns: an integer used as the user's choice for what operation to perform
int main_menu() {
    //read choice as a string, then convert to help with input validation
    string choice;
    cout << "Hash Table Main Menu" << endl
         << "====================" << endl;
    cout << "1. Print First 100 Entries/300 Strings" << endl
         << "2. Search for Key" << endl
         << "3. Add Key" << endl
         << "4. Remove Key" << endl
         << "5. Modify Key" << endl
         << "6. Exit" << endl;
    cout << "Choice --> ";
    cin >> choice;
    //check if input string is anything except for numbers 1-6
    while (choice != "1" && choice != "2" && choice != "3" && 
           choice != "4" && choice != "5" && choice != "6") {
        cout << "Invalid choice, try again --> ";
        cin >> choice;
    }
    //convert to int and return if input is valid
    return stoi(choice);
}

//description: key_check() checks if an entry exists in the passed hash table
//arguments: a hash table passed by constant reference, a string
//returns: true or false, depending on if the key was found or not
//note: created to not copy/paste same logic in multiple functions
bool key_check(const map<int, list<string>> &ht, string entry) {
    //get hash index of user entry and see if it exists using .find()
    int index = gen_hash_index(entry);
    auto it = ht.find(index);

    //if hash index exists, traverse its list to search for the key
    bool result = false; //default to false
    if (it != ht.end()) {
        for (auto &key : it->second) {
            if (key == entry) { //if key found, result true
                result = true;
                return result;
            }
        }
        return result; //result stays false if end of list is reached
    }
    return result; //result stays false if iterator reaches .end()
}

//description: print_entries() prints the first 100 entries/300 strings
// to the console
//arguments: a hash table implemented with an int for the key and a std::list
// of strings for its value, passed by constant reference
//returns: void
void print_entries(const map<int, list<string>> &hash_table) {
    //output first 100 map entries/first 300 strings
    int count = 0;
    for (const auto &pair : hash_table) {
        cout << "Hash index: " << pair.first << endl;
        cout << "\t";
        for (const string &code : pair.second) {
            cout << code << " ";
            count++;
            if (count >= 300)
                break;
        }
        cout << endl << endl;
    }
}

//description: search_key() checks if a key exists in the passed hash table
//arguments: a hash table passed by constant reference
//returns: void
void search_key(const map<int, list<string>> &ht) {
    cout << "Please enter a key to search for:" << endl;
    cout << "--> ";
    string entry;
    cin >> entry;
    cout << "Searching for " << entry << "..." << endl;
    bool result = key_check(ht, entry);

    //output result
    cout << entry;
    if (result)
        cout << " found!" << endl << endl;
    else
        cout << " not found!" << endl << endl;
}

//description: add_key() adds a key to the passed hash table
//arguments: a hash table passed by reference
//returns: void
void add_key(map<int, list<string>> &ht) {
    cout << "Please enter a key to add:" << endl;
    cout << "--> ";
    string entry;
    cin >> entry;

    //check if key already exists
    bool result = key_check(ht, entry);
    if (result) {
        cout << entry << " already exists." << endl;
        cout << "To modify existing key, select option 5." << endl << endl;
    }
    else { //add key if it doesn't already exist
        int index = gen_hash_index(entry);
        ht[index].push_back(entry);
        cout << entry << " added!" << endl << endl;
    }
}

//description: remove_key() deletes a key from the passed hash table
//arguments: a hash table passed by reference
//returns: void
void remove_key(map<int, list<string>> &ht) {
    cout << "Please enter a key to remove:" << endl;
    cout << "--> ";
    string entry;
    cin >> entry;

    //check if key exists
    bool result = key_check(ht, entry);
    if (result) { //erase key if found
        int index = gen_hash_index(entry);
        auto it = find(ht.at(index).begin(), ht.at(index).end(), entry);
        ht.at(index).erase(it); //no need to check for .end() since already found
        cout << entry << " removed!" << endl << endl;
    }
    else { //else no changes made
        cout << entry << " not found." << endl;
        cout << "No changes made." << endl << endl;
    }
}

//description: modify_key() removes a key entered by the user (if found) and
// inserts the modified version into the passed hash table
//arguments: a hash table passed by reference
//returns: void
void modify_key(map<int, list<string>> &ht) {
    cout << "Please enter a key to modify:" << endl;
    cout << "--> ";
    string entry;
    cin >> entry;

    //check if key exists
    bool result = key_check(ht, entry);
    if (result) { //modify entry if found
        //new modification
        cout << "Please enter the modification:" << endl;
        cout << "--> ";
        string mod;
        cin >> mod;

        //check if mod already exists before removing anything
        bool result = key_check(ht, mod);
        if (result) {
            cout << mod << " already exists." << endl;
            cout << "Please try again by select option 5." << endl << endl;
        }
        else { //remove entry and add mod if mod does not exist
            //first remove old key
            int index = gen_hash_index(entry);
            auto it = find(ht.at(index).begin(), ht.at(index).end(), entry);
            ht.at(index).erase(it); //no need to check for .end() since already found

            //now safe to add mod
            int mod_index = gen_hash_index(mod);
            ht[mod_index].push_back(mod);
            cout << entry << " successfully modified to " << mod << endl << endl;
        }
    }
    else { //else no changes made
        cout << entry << " not found." << endl;
        cout << "No changes made." << endl << endl;
    }
}