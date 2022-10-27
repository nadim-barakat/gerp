/*
 * hash_table.h
 * Nadim Barakat, [Partner Name]
 * 4/22/2022
 * CS 15 Proj 3 GERP 
 * 
 * The hash_table class allows for users to search for words 
 * from a given directory. The hash table class takes care of 
 * everything that allows a user to index the files and then 
 * be able to search through the contents of those files. It 
 * allows the user to also specify whether they want to search 
 * in case sensitive or insensitve. This is similar to grep 
 * and is instead gives function to our similar program called 
 * gerp. 
 * 
 * This class is best used when paired with the interact.h class
 * as that class can handle asking for user input. Every hash_table
 * begins empty with a certain size then gets populated with the 
 * from the files using the functions. This allows the user to then 
 * search through using the other functions in the class. 
 * 
 * The most important thing of this class is that it allows for 
 * constant or nearly constant access to the words stored in the hash
 * table. While it may take some time to index large directories, 
 * the search time is fast. 
 *
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <list>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>

class hash_table {

public:
    hash_table();
    ~hash_table();

    //needed to initialize hash table 
    void get_filenames(FSTree my_tree); 
    void initialize_file_vec();
    void initialize_word_structs(); 
    
    std::string stripNonAlphaNum(std::string input);

    //commands to interact with hash_table  
    void swap_output_file(std::string output_file_name); 
    void open_output_file(std::string output_file_name); 
    void insensitive_search(std::string original_query);
    void sensitive_search(std::string keyword);

    //needs to be public because of way hash function 
    //is declared inside hash_table.cpp 
    struct word_struct {
        std::string word; 
        int line_index;
        int file_index; 
        int line_number;  
    };

private:

    struct line_struct {
        std::string line; 
        bool is_printed = false; 
    };

    struct file_struct {
        std::string file_name; 
        std::vector <line_struct> line_vec;
    }; 

    std::vector <std::string> filenames; 
    std::vector <file_struct> file_vec; 
    std::vector <word_struct> vect_word_struct; 

    std::list <word_struct> word_list;
    std::list <word_struct> *chained_table; //hash_table

    int length_chained_table; 
    int total_elems; 

    std::ofstream output_file;

    bool need_expand();
    void reset_printed_bools(int hash_value); 
    void print_not_found(std::string keyword, std::string &query);
    void search(std::string keyword, std::string query);
    void search(std::string query, int hash_value);
    std::string get_word_to_search(std::string word, std::string keyword);
    std::string to_lowercase(std::string word);
    int get_hash(word_struct the_word_struct, int size_to_hash);
    void write_to_file(word_struct &list_elem);
    void insert(word_struct word);
    void expand();
};

#endif
