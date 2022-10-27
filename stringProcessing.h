/*
 * stringProcessing.h 
 * Nadim Barakat, Iris Yang 
 * 4/22/2022
 * CS 15 Proj 3 GERP 
 * 
 * The stringProcesssing.h file contains the declaration
 * that allows the user to remove all nonalphanumeric 
 * characters from the
 * front or back of the given string. Note: 
 * this does not remove these symbols that may be present in
 * in the middle of a string. 
 * 
 * To call the function, a person should needs to provide
 * an input string and the stripped version will be returned.
 * Also note that if a string does not contain these symbols, 
 * the same string will be returned.  
 * 
 * While this function may be used as a standalone function, 
 * it interacts with the other classes becauase it is used by
 * the hash_table class. 
 * 
 */


#include <iostream>
#include <cstdlib> 
using namespace std;
 
std::string stripNonAlphaNum(std::string input); 