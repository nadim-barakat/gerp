/*
 * testing_main.cpp  
 * Nadim Barakat, Iris Yang 
 * 4/22/2022
 * CS 15 Proj 3 GERP 
 * 
 * The main.cpp function is where all the classes meet
 * to interact and give the full functionality to our gerp
 * program. This allows for the use of gerp which allows
 * the user to search for specific words under certain 
 * conditions from files in a given directory.  
 * 
 * This makes an instance of both the hash_table and
 * interact class which the user can then use to send
 * their inputs and actually use the gerp program. 
 * 
 * Of importance to note is that the name of directory
 * and output file must come from the command line. Therefore
 * if a person doesn't provide this information, the program 
 * will not run and will exit. 
 */
#include <iostream>
#include <cstdlib> 
#include <cassert>
#include "stringProcessing.h"
#include "FSTree.h"
#include "hash_table.h"
#include <list>
#include "interact.h"

using namespace std;

/*
check_argc_num: 
    Checks the number of arguments when ./gerp is called. If the
    number of arguments is not 3, then it prints an error message
    and terminates the program.
*/
void check_argc_num(int argc)
{
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl; 
        exit(EXIT_FAILURE); 
    }
}

/*
main: 
    Runs the overall program. Checks the number of arguments, calls
    interact on the second and third argument, then runs the command loop.
*/
int main(int argc, char *argv[])
{
    hash_table table; 
    check_argc_num(argc); 
    interact gerp(argv[1], argv[2]); 
    gerp.command_loop(cin); 

    return 0; 
}