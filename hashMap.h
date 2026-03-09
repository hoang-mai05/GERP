/*
    hashmap.h
    Hoang Mai Stacey Liang
    COMP 15 HW 6 Gerp

    hashmap.h is the class declaration of hashMap class that defines the 
    storage of our sentence structs, and the different data structures to do so

*/

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include <utility>
#include <string>
#include <vector>
#include "sentence.h"

using namespace std;


class hashMap {
    public:

        // Constructor and Destructor
        hashMap();
        ~hashMap();

        void insertHash(string& word, Sentence& s);
        vector <Sentence> getHashVector(string word);
        
    private:

        void    rehash();
        void    linearProbe(int& index, string& word, Sentence& s);
        int     rehashCollision(int& index, 
                                pair<string, vector<Sentence>>* newHashMap);

        int     hashSize;
        int     numKeys;
        double  loadFactor;
        pair<string, vector<Sentence>>* hashVector; 

};

#endif
