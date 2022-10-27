/*
 * interact.cpp 
 * Nadim Barakat, [Partner Name]
 * 4/22/2022
 * CS 15 Proj 3 Gerp  
 * 
 * 
 * The interact.cpp implementation gives the user access to our 
 * Gerp program that allows the user to search for words through 
 * a directory of files. The interact class works with our hash_table 
 * class to make appropriate actions based on the type of search the 
 * user wants to conduct such as insensitive or sensitive search. 
 * Other uses such as quitting gerp can be accomplished by this 
 * class. 
 * 
 * The interact constructor takes in two arguments that are 
 * the directory and name of file to write to. This can then 
 * interact with a main program that can start the gerp program. 
 * 
 */


#include <iostream>
#include "DirNode.h"
#include "FSTree.h"
#include "hash_table.h"
#include "interact.h"
#include <vector>
#include <fstream>
#include <sstream> 
#include <list>
#include <functional>

using namespace std; 

/*
This is the constructor. It takes in a directory and an output file string
and initializes an FSTree, gets the filenames from that tree, initializes
the file vector and word structs, and opens the output file in the
hash table.
*/
interact::interact(std::string directory, std::string output_file) 
{
    //set up hash_table 
    FSTree my_tree(directory); 
    table.get_filenames(my_tree); 
    table.initialize_file_vec(); 
    table.initialize_word_structs(); 
    table.open_output_file(output_file); 
}

/*
interact:
    Takes in a reference to an istream and acts as the interface for the
    program. While the user doesn't call quit or reach the end of a file
    that the user puts in (which would print a message and end the program),
    "Query?" is printed out to the terminal and the user can input their
    query to be searched up in the directory. The results are then
    outputted to the output file, which the user can view using
    cat outputName.txt.

    The inputs the program can take are as follows:
    
    AnyString:
        Basically any string that the user types into the query, including
        random commands like jakdna, the, or THE. The program then performs
        a case-sensitive search and prints the results to the output file.

    @i or @insensitive:
        If the above is the first string, then it will take a second
        string that is the word the user wants to search up. It will
        perform a case insensitive search (meaning the and THE are
        the same word, for example) and print the results.

    @q or @quit:
        Exits the while loop, prints a goodbye message, and terminates
        the program.

    @f:
        Takes in a second input which is the new file name that the
        program will write the output to, and swaps the current output
        file with the new one.
*/
void interact::command_loop(istream &cmd) 
{
    string first_input; 
    cout << "Query? "; 

    while (cmd >> first_input)
    { 
        string second_input; 
        if (first_input == "@q" or first_input == "@quit") {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return; 
        } 
        if (first_input == "@i" or first_input == "@insensitive") {
            cmd >> second_input;
            table.insensitive_search(table.stripNonAlphaNum(second_input));  
        } else if (first_input == "@f") {
            cmd >> second_input; 
            table.swap_output_file(second_input); 
        } else {
            table.sensitive_search(table.stripNonAlphaNum(first_input));
        } 
        cout << "Query? "; 
    }
    cout << "Goodbye! Thank you and have a nice day." << endl;
    return; 
}