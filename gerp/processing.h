#ifndef __PROCESSING_H
#define __PROCESSING_H

#include <string>
#include "DirNode.h"
using namespace std;

string stripNonAlphaNum(string input);
void traverseDirectory(string directory);
void traverseDirectoryHelper(string directory, DirNode *node);

#endif 
