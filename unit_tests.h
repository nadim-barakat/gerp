/*
 * unit_tests.h 
 * Nadim Barakat, Iris Yang 
 * 4/22/2022
 * CS 15 Proj 3 GERP 
 * 
 * The unit_tests.h file contains tests that check 
 * for regular and edge cases for our week 1 phase 
 * of the gerp project. It mainly tests the function
 * that strips non-alphanumeric chars from the front
 * of back of strings. In doing so, we consider the 
 * many edge cases and verify the output in this file.   
 * 
 *
 */


#include <iostream>
#include <cstdlib> 
#include <cassert>
#include "stringProcessing.h"
#include "FSTree.h"
using namespace std;


/*
trailing_front_only()
    checks output for strings with symbols in front
*/
void trailing_front_only()
{
    std::string output = stripNonAlphaNum("!!!!!COMP-15");
    assert(output == "COMP-15");  

    output = stripNonAlphaNum("-!@hello"); 
    assert(output == "hello");  
}

/*
trailing_back_only()
    checks output for strings with symbols in back
*/
void trailing_back_only()
{
    std::string output = stripNonAlphaNum("jupiter!@#-"); 
    assert(output == "jupiter");

    output = stripNonAlphaNum("jupiter!is_21cool%$!@"); 
    assert("jupiter!is_21cool"); 
}
/*
no_trailing()
    checks output for strings with no symbols 
*/
void no_trailing()
{
    std::string output = stripNonAlphaNum("shrek");
    assert(output == "shrek"); 

    output = stripNonAlphaNum("shrek_2"); 
    assert(output == "shrek_2"); 
}
/*
both_trailing()
    checks output for strings with symbols in front and back  
*/
void both_trailing()
{
    std::string output = stripNonAlphaNum("!COMP-15#"); 
    assert(output == "COMP-15"); 
}

/*
empty_string()
    checks output for empty strings  
*/
void empty_string()
{
    std::string output = stripNonAlphaNum("       "); 
    assert(output == ""); 

    output = stripNonAlphaNum(""); 
    assert(output == ""); 
}








