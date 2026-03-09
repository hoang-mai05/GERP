/*
    gerp.h
    Hoang Mai Stacey Liang
    COMP 15 HW 6 Gerp

    gerp.h is a class declaration of the gerp.h file
    that indexes a given directory and responds to the user query
*/

#ifndef __GERP_H
#define __GERP_H

#include "hashMap.h"
#include "sentence.h"
#include "DirNode.h"
#include <functional>
#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <utility>

using namespace std;

class Gerp {

    public:
        Gerp();
        void run(string directory, string &outputFile);
        
    private:

        vector<vector<pair<string,bool>>> vectorFiles;
        vector<pair<int, int>> resetChecker;

        void processFiles(string directory); 
        void query(ofstream &output);

        // Query Helper Functions
        void handleAnyString(string word, ofstream &output, bool sensitive);
        void checkNotFound(string& word, vector<pair<int, int>> &checker, 
                           ofstream &output, bool sensitive);
        void handleFileCase(string filename, ofstream &output);

        void resetSeen();

        void traverseDirectory(string directory, DirNode *node);
        void indexContent(const string& path);
        void processLine(string& line, const int& fileIndex, int& lineIndex);
        string stripNonAlphaNum(string input);

        int numFiles;
        hashMap HM;
};

#endif
