###
### Makefile for Gerp Project
###
### Author:  Hoang Mai Stacey Liang

CXX      = clang++ 
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -O2
LDFLAGS  = -g3 

## 
## Build up your Makefile in a similar manner as for Zap. Feel free 
## to use that Makefile to guide you! Note, you do NOT need rules for
## FSTree.o and DirNode.o as those (pre-compiled) object files are 
## provided to you.
## 
## At the end, you can delete this comment!
## 

gerp: main.o gerp.o processing.o DirNode.o FSTree.o hashMap.o
	$(CXX) ${LDFLAGS} -o gerp main.o processing.o DirNode.o FSTree.o hashMap.o gerp.o

gerp.o: gerp.h gerp.cpp hashMap.o sentence.h
	$(CXX) ${CXXFLAGS} -c gerp.cpp

hashMap.o: hashMap.h hashMap.cpp sentence.h
	$(CXX) ${CXXFLAGS} -c hashMap.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds processing.o
processing.o: processing.h processing.cpp DirNode.o FSTree.o
	$(CXX) ${CXXFLAGS} -c processing.cpp 

# This rule builds the unit test
unit_test: unit_test_driver.o processing.o DirNode.o FSTree.o gerp.o hashMap.o sentence.h
	$(CXX) $(CXXFLAGS) $^ 

##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out
