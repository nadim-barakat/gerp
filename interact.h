/*
 * interact.h 
 * Nadim Barakat, [Partner Name]
 * 4/22/2022
 * CS 15 Proj 3 GERP 
 * 
 * The interact.h class allows for the user to make an 
 * instance of the class in a main function and then 
 * use gerp. Gerp will allow the user to search for 
 * words using certain constraints from a directory. When 
 * interact is called, it will search the hash_table class 
 * for that word and and write that output to the specified
 * output file. 
 * 
 * An instance can be made using the directory name 
 * and the name of the output file that the user wants to 
 * write to. This is all the information the user needs to 
 * provide to run the interact class as everything else 
 * in terms of handling the commands is taken care of 
 * behind the scenes. 
 * 
 *
 */

#ifndef INTERACT_H_
#define INTERACT_H_

class interact {
public:
    interact(std::string directory, std::string output_file);
    void command_loop(std::istream &cmd);
private:
    hash_table table;
};

#endif
