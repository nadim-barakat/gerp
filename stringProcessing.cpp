/*
 * stringProcessing.cpp 
 * Nadim Barakat, Iris Yang 
 * 4/22/2022
 * CS 15 Proj 3 GERP 
 * 
 * The stringProcesssing.cpp file contains a function
 * that removes all nonalphanumeric characters from the
 * front or back of the given string. Note: 
 * this does not remove these symbols that may be present in
 * in the middle of a string. 
 * 
 * To call the function, a person should needs to provide
 * an input string and the stripped version will be returned.
 * Also note that if a string does not contain these symbols, 
 * the same string will be returned.  
 */
#include <iostream>
#include <cstdlib> 
#include <vector>
using namespace std;

/*
stripNonAlphaNum:
    Takes in a string and loops through the front and back of the
    string, erasing characters until it hits an alphanumeric character.
*/
std::string stripNonAlphaNum(std::string input)
{
    for (size_t i = 0; i < input.length() and not isalnum(input[i]);)
    {
        input.erase(i, 1); //erase first char until hit alphanum
    }
    for (int j = input.size() - 1; j > - 1 and not isalnum(input[j]); j--)
    {
        input.erase(j, 1); //erase last char until hit alphanum 
    } 
    return input; 
}