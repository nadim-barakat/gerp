# /*
#  * Makefile 	
#  * Nadim Barakat, Iris Yang 
#  * 4/22/2022
#  * CS 15 Proj 3 GERP 
#  * 
#  * This allows for the compilation of all of our 
#  * classes that interact together. What is most 
#  * important is that the user can compile gerp by 
#  * just calling "make". It can then be run by calling 
#  * ./gerp [directory] [outputfile] 
#  * 
#  * To run our unit_tests program, the user just needs to 
#  * type unit_tests and all the functions there will run. 

# this is needed to have make follow symlinks in dependency lists 
MAKEFLAGS += -L 



CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

gerp: main.o hash_table.o DirNode.o FSTreeTraversal.o FSTree.o interact.o 
	${CXX} ${LDFLAGS} -o $@ $^


main.o: main.cpp DirNode.o FSTree.o FSTreeTraversal.o hash_table.o 
	$(CXX) $(CXXFLAGS) -c main.cpp
treeTraversal: FSTreeTraversal.o DirNode.o FSTree.o
	${CXX} ${LDFLAGS} -o $@ $^

FSTreeTraversal.o: FSTreeTraversal.cpp
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp  
stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp 

hash_table.o: hash_table.cpp hash_table.h 

interact.o: interact.cpp interact.h \
	DirNode.o FSTree.o FSTreeTraversal.o hash_table.o 
	$(CXX) $(CXXFLAGS) -c interact.cpp 

unit_test: unit_test_driver.o stringProcessing.o  \
FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) $^


provide: 
	provide comp15 proj3_gerp DirNode.h FSTree.h FSTreeTraversal.cpp \
	hash_table.cpp hash_table.h interact.cpp interact.h \
	stringProcessing.cpp stringProcessing.h testing_main.cpp Makefile \ 
	README unit_tests.h


clean: 
	rm hash_table.o stringProcessing.o FSTreeTraversal.o 
