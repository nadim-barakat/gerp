/*
 * hash_table.cpp
 * Nadim Barakat, [Partner Name]
 * 4/22/2022
 * CS 15 Proj 3 Gerp
 *
 *
 *
 * The hash_table.cpp implementation gives functionality to our Gerp
 * program because it allows for the insertion of words into the table,
 * searching for those words, and getting the output as the user needs.
 * It interacts with the interact.cpp class where it can be called and used
 * to its full functionality. This allows the user to search for a certain
 * word under certain constraints like case sensitivity/ insensitivity
 * from a directory of files.
 *
 * The default parameter takes no arguments and initiates an
 * empty hash table. Of importance is that
 * the user does not need to worry about expanding as that is
 * all handled by the implementation. An instance can be created
 * by simply calling the hash_table default constructor.
 *
 */

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "DirNode.h"
#include "FSTree.h"
#include "hash_table.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include <functional>

/*
This template was taught to us by Nick.
He showed us how to use std::hash to hash
a struct that we defined
(in this case, a word struct.)
*/
using namespace std;
namespace std {
template <>
    struct std::hash<hash_table::word_struct> {
        size_t operator()(const hash_table::word_struct& w ) const noexcept {
            return std::hash<std::string>{}(w.word);
        }
    };
}

/*
The constructor of the hash_table class. Sets the
number of total elements to 0 and the length of the hash_table
array to 0. Also makes the chained_table (a pointer to a list
of word structs) the actual hash table (by declaring a new
list of word structs).
*/
hash_table::hash_table()
{
    total_elems = 0;
    length_chained_table = 500; // selected size as found to be
                                // good intermediate
                                // between large and small data sets.
    chained_table = new list<word_struct>[length_chained_table];
}

/*
The destructor of the hash_table class. Frees up the
chained_table.
*/
hash_table::~hash_table()
{
    delete [] chained_table;
}

/*
get_filenames:
    Gets the root of the directory (of type FSTree and prints out
    its conetents, then checks to see if the root has subdirectories
    and/or files, and then recursively prints the files inside the
    subdirectories out.
    If the root is empty, then it returns.
    It pushes the name of each file to a vector filenames which
    holds the name of each vector.
*/
void hash_table::get_filenames(FSTree my_tree)
{
    DirNode *root = my_tree.getRoot();
    string full_path = root->getName() + "/";

    if (root->isEmpty()) {
        return;
    }

    if (root->hasSubDir()) {
        for (int i = 0; i < root->numSubDirs(); i++) {
            string pathed_sub_dir = full_path + root->getSubDir(i)->getName();
            FSTree sub_tree(pathed_sub_dir);
            get_filenames(sub_tree);
        }
    }

    if (root->hasFiles()) {
        for (int i = 0; i < root->numFiles(); i++) {
            string pathed_file = full_path + root->getFile(i);
            filenames.push_back(pathed_file);
        }
    }
}

/*
initialize_file_vec:
    Opens each file and create a
    file_struct; filenames[i] becomes the name of the file_struct.
    Then, it reads in each line of the file, creating a line_struct
    in the process. Each line_struct contains the actual line and
    is pushed to a vector called line_vec. Once all the lines
    in that file are stored in line_vec, the file struct is
    pushed to the back of a vector containing file structs.
    Next, filenames gets rid of that file.
*/
void hash_table::initialize_file_vec()
{
    for (size_t i = 0; i < filenames.size(); i++) {
        ifstream my_file;
        my_file.open(filenames[i]);
        file_struct a_file_struct;

        a_file_struct.file_name = filenames[i];
        std::string line;

        while (getline(my_file, line)) {
            line_struct a_line_struct;
            a_line_struct.line = line;
            a_file_struct.line_vec.push_back(a_line_struct);
        }

        file_vec.push_back(a_file_struct);
    }
    //we don't need this vector anymore so clear its contents
    //and reduce its size
    filenames.clear();
    filenames.shrink_to_fit();
}

/*
stripNonAlphaNum:
    Takes in an input of type string and erases all the
    nonalphanumeric characters from the beginning and the end of
    the input like $, ?, and (), then returns the stripped string.
*/
std::string hash_table::stripNonAlphaNum(std::string input)
{
    for (size_t i = 0; i < input.length() and not isalnum(input[i]);) {
        input.erase(i, 1);
    }

    for (int j = input.size() - 1; j > - 1 and not isalnum(input[j]); j--) {
        input.erase(j, 1);
    }
    return input;
}

/*
initialize_word_structs:
    Goes through each line struct vector inside each file struct vector
    and reads in each word from the line using stringstream, stripping
    its nonalphanumeric contents and initializing a word_struct. The
    word_struct is then inserted into the hash_table and the number of
    total elements increases.
*/
void hash_table::initialize_word_structs()
{
    for (size_t i = 0; i < file_vec.size(); i++) {
        for (size_t j = 0; j < file_vec[i].line_vec.size();
            j++) {
            string word;
            //actual line from file
            stringstream ss(file_vec[i].line_vec[j].line);
            //go through line word by word
            while (ss >> word) {
                word = stripNonAlphaNum(word);
                word_struct a_word_struct;
                a_word_struct.word = word;
                a_word_struct.file_index = i;
                a_word_struct.line_index = j;
                a_word_struct.line_number = j + 1;
                insert(a_word_struct); //put into hash table
                total_elems++;
            }
        }
    }
}

/*
need_expand:
    Checks the load factor by dividing the total elements by the length
    of the hash table. If the load factor is over 0.7, then it returns true;
    else false. 
*/
bool hash_table::need_expand()
{
    double load_factor = double(total_elems) / double(length_chained_table);

    if (load_factor >= 0.7) { //value from lecture
        return true;
    } else {
        return false;
    }
}

/*
get_hash:
    Takes in a word_struct and an integer that will compress the
    word_struct's word. Then, using C++'s built-in hash function, it
    computes a hash_value and returns it.
*/
int hash_table::get_hash(word_struct the_word_struct, int size_to_hash)
{
    word_struct temp_word_struct;
    temp_word_struct.word = to_lowercase(the_word_struct.word);

    // hash and compress
    int hash_value = hash<word_struct>{}(temp_word_struct) % size_to_hash;

    return hash_value;
}

/*
to_lowercase:
    Takes in a word and using C++'s tolower function,
    makes all the letters in that word lowercase, then returns it.
*/
std::string hash_table::to_lowercase(std::string word)
{
    string lowercase_word = "";

    for (size_t i = 0; i < word.length(); i++) {
        lowercase_word += tolower(word[i]);
    }

    return lowercase_word;
}

/*
insert:
    Takes in a word and gets its hash value. Checks the load factor and
    expands if over .7, then pushes the word at its location (computed by
    the hash value) in the hash table.
*/
void hash_table::insert(word_struct word)
{
    int hash_value = get_hash(word, length_chained_table);

    if (need_expand()) {
        expand();
    }

    chained_table[hash_value].push_back(word);
}

/*
expand:
    Makes a new hash table where its size is 3 times + 2 of the hash
    table's original length. Then it loops through the hash table's
    elements, getting a new hash based on the new size and pushing the
    elements in the new hash table. It deletes the old hash table and
    updates the capacity at the end. 
*/
void hash_table::expand()
{
    int new_size = length_chained_table * 3 + 2;
    std::list <word_struct> *temp_chained_table;
    temp_chained_table = new list<word_struct>[new_size];

    for (int i = 0; i < length_chained_table; i++) {
        for (auto list_elem : chained_table[i]) {
            //rehash everything
            int hash_value = get_hash(list_elem, new_size);
            temp_chained_table[hash_value].push_back(list_elem);
        }
    }

    delete [] chained_table;
    chained_table = temp_chained_table;
    length_chained_table = new_size;
}

/*
insensitive_search:
    Takes in a string query and calls search with the keyword
    "insensitive" and the query.
*/
void hash_table::insensitive_search(std::string query)
{
    search("insensitive", query);
}

/*
sensitive_search:
    Takes in a string query and calls search with the keyword
    "sensitive" and the query.
*/
void hash_table::sensitive_search(std::string query)
{
    search("sensitive", query);
}

/*
get_word_to_search:
    Takes in a word and a keyword, both strings. If the keyword
    is "insensitive", then it returns the lowercase version of the word.
    Otherwise, it returns the word as is. 
*/

std::string hash_table::get_word_to_search
    (std::string word, std::string keyword)
{
    if (keyword == "insensitive") {
        return to_lowercase(word);
    } else {
        return word;
    }
}

/*
search:
    Takes in two parameters: a keyword and a string original_query.
    We create a new string variable query to get the right word based on
    whether it's insensitive or sensitive, then create a new word struct
    and hash it. If, for some reason, the original_query is stripped to
    just an empty string, we print the correct output message and return.

    Setting is_printed to false, we search through the table for the user's
    word at the right hash index. If we find a word and is_printed is false,
    we write the line to the output file and set is_printed to true to
    account for duplicates. If we don't find a word, we call print_not_found
    for the proper message and reset_printed_bools so we can print again
    if the same word is called.
*/
void hash_table::search(string keyword, std::string original_query)
{
    string query = get_word_to_search(original_query, keyword);
    word_struct temp_word_struct;
    temp_word_struct.word = query; //use right word and get its hash
    int hash_value = get_hash(temp_word_struct, length_chained_table);

    if (original_query == "") { //edge case of empty string
        print_not_found(keyword, query);
        return;
    }
    bool is_found = false;
    //search table for user's word at hash index
    for (auto list_elem: chained_table[hash_value]) {
        string word = get_word_to_search(list_elem.word, keyword);
        int f_idx = list_elem.file_index;
        int l_idx = list_elem.line_index;

        if (word == query and not file_vec[f_idx].line_vec[l_idx].is_printed) {
            is_found = true;
            write_to_file(list_elem);
            // This accounts for duplicates
            file_vec[f_idx].line_vec[l_idx].is_printed = true;
        }
    }
    if (not is_found) {
        print_not_found(keyword, original_query);
        return;
    }
    reset_printed_bools(hash_value); // so can print again if same word called
}

/*
write_to_file:
    Takes in a word struct and correctly formats the search results
    of that word struct to the output file after search is called on a word.
*/
void hash_table::write_to_file(word_struct &list_elem)
{
    int f_idx = list_elem.file_index;
    int l_idx = list_elem.line_index;
    int l_number = list_elem.line_number;
    output_file << file_vec[f_idx].file_name << ":" 
                << l_number << ": " << 
                file_vec[f_idx].line_vec[l_idx].line << endl;
}

/*
reset_printed_bools:
    Takes in a hash_value (to determine the location in the hash table)
    and resets the elements' is_printed boolean at that location to be false
    so it can print again if the same word is called.
*/
void hash_table::reset_printed_bools(int hash_value)
{
    for (auto list_elem: chained_table[hash_value]) {
        int f_idx = list_elem.file_index;
        int l_idx = list_elem.line_index;
        file_vec[f_idx].line_vec[l_idx].is_printed = false;
    }
}

/*
print_not_found:
    Takes in a keyword and a reference to a query (to save memory).
    If the keyword is "insensitive", then it will print the message
    for when an insensitive query is searched and not found to the output 
    file. Otherwise, it prints the message for a sensitive search.
*/
void hash_table::print_not_found(std::string keyword, std::string &query)
{
    if (keyword == "insensitive") {
        output_file << query << " Not Found." << endl;
    } else {
        output_file << query << " Not Found. Try with @insensitive or @i."
                    << endl;
    }
}

/*
open_output_file: 
    Takes in the name of an output file string and opens the output
    file. Used in swapping the output file when the user enters
    @f in the command line to write to a new output file.
*/
void hash_table::open_output_file(std::string output_file_name)
{
    output_file.open(output_file_name);
}

/*
swap_output_file: 
    Closes the current output file, then takes in the name of
    a new output file to open it. Used when the user types
    @f in the command line to write to a new output file.
*/
void hash_table::swap_output_file(std::string output_file_name)
{
    output_file.close();
    open_output_file(output_file_name);
}
