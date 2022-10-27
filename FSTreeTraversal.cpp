/*
 * FSTreeTraversal.cpp 
 * Nadim Barakat, [Partner name]
 * 4/22/2022
 * CS 15 Proj 3 Gerp  
 * 
 * This file contains a program that is able to traverse through a 
 * directory and print out the full file paths of that directory. 
 * To use this function, the user only needs to know the name of the
 * directory they want to call it on. Currently, this program only 
 * prints out the names of the file paths and does so in no 
 * particular order. A modified version of this function was 
 * used in the hash_table class. 
 * 
 */

#include <iostream>
#include <cstdlib> 
#include <cassert>
#include "DirNode.h"
#include "FSTree.h"
using namespace std;

/*
print_tree_contents: 
    Gets the root of the directory and prints out its conetents, 
    then checks to see if the root has subdirectories and/or files,
    and then recursively prints the files inside the subdirectories 
    out.  
    If the root is empty, then it returns. 
*/
void print_tree_contents(FSTree my_tree)
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
            print_tree_contents(sub_tree); 
        }
    }
    if (root->hasFiles()) {
        for (int i = 0; i < root->numFiles(); i++) {
            string pathed_file = full_path + root->getFile(i); 
            cout << pathed_file << endl; 
        }
    }
}

