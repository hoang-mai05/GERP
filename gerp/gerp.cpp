/*
    gerp.cpp
    Hoang Mai, Stacey Liang
    COMP 15 HW 6 Gerp

    gerp.cpp is a function implementation of the gerp.h file
    that indexes a given directory and responds to the user query
*/

#include "gerp.h"
#include "FSTree.h"
#include "DirNode.h"
#include <cctype>
#include <functional>
#include <fstream>
#include <sstream>

using namespace std;

/*  name:       constructor
    purpose:    Initialize a Gerp object
    arguments:  None
    returns:    None
    effects:    Initialize numFiles to 0
*/
Gerp::Gerp() {
    numFiles = 0;
}

/*  name:       run
    purpose:    Execute the gerp program by processing the contents of the 
                files in the specified directory and initiating the query loop
    arguments:  A string representing the name of a directory and a string
                reference representing the output filename
    returns:    None
    effects:    None
*/
void Gerp::run(string directory, string &outputFile) 
{
    
    ofstream outstream;
    outstream.open(outputFile);
    if (not outstream.is_open()) {
        cerr << "Could not open output file" << endl;
        return;
    }    
    
    // Check if the directory exists
    try {
        processFiles(directory);
    }
    catch (const runtime_error &e) {
        cerr << "Could not build index, reason:" << endl;
        cerr << e.what() << "\n";
        return;
    }

    // Initiate query loop
    query(outstream);
    
}

/*  name:       query
    purpose:    Ask the user for an input and perform the query commands
    arguments:  An ofstream reference for output
    returns:    None
    effects:    None
*/
void Gerp::query(ofstream &output) 
{
    cout << "Query? ";
    string command, word, filename;
    cin >> command; // Store Command 

    while (command != "@q" and command != "@quit" and not cin.eof()) {
        // Insensitive Case
        if (command == "@i" or command == "@insensitive") { 
            cin >> word; // Take next Input from the User
            word = stripNonAlphaNum(word); 
            handleAnyString(word, output, false);
        // File Case
        } else if (command == "@f") {
            cin >> filename;
            try {
                handleFileCase(filename, output);
            } catch (const runtime_error &e) {
                cerr << e.what() << "\n";
                return;
            }
        // Sensitive Case
        } else {
            word = stripNonAlphaNum(command);
            handleAnyString(word, output, true);
        }
        cout << "Query? ";
        cin >> command;
    }
    cout << "Goodbye! Thank you and have a nice day." << endl;
}

/*  name:       handleAnyString       
    purpose:    Search for the provided string and print all the lines in the
                indexed files where the string appears
    arguments:  A string to search for, an ofstream reference for output, 
                and a boolean value for case sensitivity.
    returns:    None    
    effects:    None
*/
void Gerp::handleAnyString(string word, ofstream &output, bool sensitive) 
{
    string lowercase;
    for (char c : word) {
        lowercase += tolower(c);  // Convert word to lower case
    }


    // Retrieve the vector of Sentence structs from hash map
    vector <Sentence> wordBank = HM.getHashVector(lowercase); 
    //checkNotFound(word, wordBank, output, sensitive);

    for (size_t i = 0; i < wordBank.size(); i++) {
        int fileNum = wordBank[i].fileIndex;
        int lineNum = wordBank[i].lineIndex; 

        // Validate whether the line should be printed 
        bool printLine = 
        not vectorFiles[fileNum][lineNum].second and 
        (not sensitive or (sensitive and (word == wordBank[i].word)));

        if (printLine) {
            output << vectorFiles[fileNum][0].first << ":" << lineNum;
            output << ": " << vectorFiles[fileNum][lineNum].first << endl;
            vectorFiles[fileNum][lineNum].second = true;
            resetChecker.push_back({fileNum, lineNum});
        }
    }
    checkNotFound(word, resetChecker, output, sensitive); 

    resetSeen();
}

/*  name:       checkNotFound       
    purpose:    Check if the input word is not found in the hash map
    arguments:  A string reference representing the word to check, a vector 
                reference to the word bank, an ofstream reference for 
                output, and a boolean indicating case sensitivity.
    returns:    None    
    effects:    None
*/
void Gerp::checkNotFound(string& word, vector<pair<int, int>>& checker, 
                         ofstream &output, bool sensitive) {

    // Empty wordBank indicates the word is not found in the hash map
    if (checker.empty()) {
        output << word << " Not Found.";
        if (sensitive) {
            output << " Try with @insensitive or @i.";
        }
        output << endl;       
    }    
}

/*  name:       handleFileCase       
    purpose:    Close the current output file and open a new one
    arguments:  A string representing the new output file name
    returns:    None    
    effects:    None
*/
void Gerp::handleFileCase(string filename, ofstream &output) {
    output.close();
    output.open(filename);
    if (not output.is_open()) {
        throw runtime_error("Could not open " + filename);
    }
}

/*  name:       resetSeen
    purpose:    Reset the "already printed" indicator for each line
    arguments:  None
    returns:    none    
    effects:    Set the boolean values of each line in vectorFiles to false
*/
void Gerp::resetSeen() {

    for (size_t i = 0; i < resetChecker.size(); i++) {
        int fileNum = resetChecker.at(i).first;
        int lineNum = resetChecker.at(i).second;        
        vectorFiles[fileNum][lineNum].second = false;
    }
    resetChecker.clear();
}

/*  name:       processFiles
    purpose:    Process the files in the specified directory
    arguments:  String representing the name of a directory
    returns:    None
    effects:    None
*/
void Gerp::processFiles(string directory) {
    FSTree DirTree(directory);
    DirNode* root = DirTree.getRoot();
    traverseDirectory(directory, root);
}

/*  name:       traverseDirectory    
    purpose:    Generate full file paths of all the files in the directory and 
                pass them to 'indexContent' helper function.
    arguments:  A string representing the current path and a DirNode pointer to 
                the current directory node
    returns:    None    
    effects:    None
*/
void Gerp::traverseDirectory(string directory, DirNode *node) {
    if (node->isEmpty()) {
        return;
    }

    // If the node contains files, process each file
    if (node->hasFiles()) {
        for (int i = 0; i < node->numFiles(); i++) {
            numFiles++;
            string path = directory + "/" + node->getFile(i);
            indexContent(path);
        }
    }

    // If the node contains subdirectories, process each subdirectory
    if (node->hasSubDir()) {
        for (int i = 0; i < node->numSubDirs(); i++) {
            string newString = directory + "/" + node->getSubDir(i)->getName();
            traverseDirectory(newString, node->getSubDir(i));
        }
    }
}   

/*  name:       indexContent             
    purpose:    Store the contents of the file at the specified path and 
                process each line using the helper function, 'processLine'.
    arguments:  A constant reference to a string representing the path
    returns:    None    
    effects:    Populate vectorFiles
*/
void Gerp::indexContent(const string& path) 
{
    ifstream instream(path);

    if (not instream.is_open()) {
        throw runtime_error("Could not open " + path);
    }

    // Create a vectorLines for this file
    vector<pair<string,bool>> vectorLines;

    // Add vectorLines to the vector of files
    vectorFiles.push_back(vectorLines); 

    // Store the file path as the first entry in the vector for this file
    vectorFiles[numFiles-1].push_back({path,false});

    string line;
    int numLine = 0;
    while (getline(instream, line)) {
        numLine++;
        vectorFiles[numFiles-1].push_back({line,false}); // Store each line
        processLine(line, numFiles-1, numLine);          // Process each line
    }
    instream.close();
}

/*  name:       processLine     
    purpose:    Process a single line and insert each word into a hash map 
                with its associated sentence information
    arguments:  A reference to a string representing the line to process, 
                and references to two integers representing the line position
    returns:    None    
    effects:    Update the hash map with new words and sentence information
*/
void Gerp::processLine(string& line, const int& fileIndex, int& lineIndex) {

    // Store information about line position in Sentence struct
    Sentence s;
    s.fileIndex = fileIndex;
    s.lineIndex = lineIndex;

    istringstream sentenceStream(line);
    string word;
    while(sentenceStream >> word) {
        word = stripNonAlphaNum(word); 
        s.word = word;  
        for (char& c : word) {
            c = tolower(c);  
        }

        // Insert word with its associated Sentence struct into hash map
        HM.insertHash(word, s);
    }
}

/*  name:       stripNonAlphaNum
    purpose:    Remove all leading and trailing non-alphanumeric characters
    arguments:  Input string from the user
    returns:    The input without the Lead/Trail NonAlpha characters
    effects:    None
*/
string Gerp::stripNonAlphaNum(string input)
{   
    size_t size = input.length();
    // Iterate through string, find first instance of Alphanumeric Char 
    for(size_t i = 0; i < size; i++) {
        if ((input[i] >= '0' and input[i] <= '9') or 
            (input[i] >= 'A' and input[i] <= 'Z') or
            (input[i] >= 'a' and input[i] <= 'z'))
        {
            input = input.substr(i, size);
            size = input.length();
            // Iterate from the back now, find Alphanumeric Char
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

