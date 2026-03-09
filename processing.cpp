/*
    processing.cpp
    Hoang Mai, Stacey Liang
    COMP 15 HW 6 Gerp

    processing.cpp is a function implemention of the processing.h file
    that strips Non-Alphanumeric Characters and traverses through
    a given directory
*/
#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"
#include <iostream>

/*  name:       stripNonAlphaNum
    purpose:    Remove all leading and trailing non-alphanumeric characters
    arguments:  Input string from the user
    returns:    The input without the Lead/Trail NonAlpha characters
    effects:    None
*/
string stripNonAlphaNum(string input)
{   
    size_t size = input.length();
    /*  Iterate through string, find first instance of Alphanumeric Char */
    for(size_t i = 0; i < size; i++) {
        if ((input[i] >= '0' and input[i] <= '9') or 
            (input[i] >= 'A' and input[i] <= 'Z') or
            (input[i] >= 'a' and input[i] <= 'z'))
        {
            input = input.substr(i, size);
            size = input.length();
            /*  Iterate from the back now, find Alphanumeric Char */
            for (size_t j = size - 1; j >= 0; j--) {
                if ((input[j] >= '0' and input[j] <= '9') or 
                    (input[j] >= 'A' and input[j] <= 'Z') or
                    (input[j] >= 'a' and input[j] <= 'z'))
                {
                    input = input.substr(0, j + 1);
                    return input;
                } 
            }
        }
    }
    return "";
}

/*  name:       traverseDirectory
    purpose:    Print the full paths of all the files in the directory
    arguments:  String representing the name of a directory
    returns:    None
    effects:    None
*/
void traverseDirectory(string directory) 
{
    FSTree DirTree(directory);
    DirNode* root = DirTree.getRoot();
    traverseDirectoryHelper(directory, root);
}

/*  name:       traverseDirectoryHelper
    purpose:    Print the full paths of all the files in the directory
    arguments:  A string representing the current path and a DirNode pointer to 
                the current directory node.
    returns:    None
    effects:    None
*/
void traverseDirectoryHelper(string directory, DirNode *node) 
{
    if (node->isEmpty()) {
        return;
    }

    if (node->hasFiles()) {
        for (int i = 0; i < node->numFiles(); i++) {
            cout << directory + "/" + node->getFile(i) << endl;
        }
    }

    if (node->hasSubDir()) {
        for (int i = 0; i < node->numSubDirs(); i++) {
            string newString = directory + "/" + node->getSubDir(i)->getName();
            traverseDirectoryHelper(newString, node->getSubDir(i));
        }
    }
}
