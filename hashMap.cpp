/*
    hashMap.cpp
    Hoang Mai Stacey Liang
    COMP 15 HW 6 Gerp

    hashMap.cpp is a class implementation of the hashMap.h file
    that stores a pair that represents the word and a vector of sentence 
    structs
*/
#include "hashMap.h"
#include <functional>
#include <iostream>
using namespace std;

/*  name:       constructor   
    purpose:    Initialize a hashMap object
    arguments:  None
    returns:    None
    effects:    Initialize hashSize, loadFactor, numKeys, and hashVector
*/
hashMap::hashMap() {
    hashSize = 89; 
    loadFactor = 0;
    numKeys = 0;

    // Array dynamically allocated on heap
    hashVector = new pair<string, vector<Sentence>> [hashSize]; 
}

/*  name:       destructor
    purpose:    Free the memory allocated by the hashMap object
    arguments:  None
    returns:    None
    effects:    Deallocate the hashVector from heap memory
*/
hashMap::~hashMap() {
    delete [] hashVector;
}

/*  name:       rehash
    purpose:    Resize the hash map and redistribute the elements within it
    arguments:  None
    returns:    None
    effects:    Update hashSize and resize hashVector
*/
void hashMap::rehash() {
    int oldSize = hashSize;
    hashSize = hashSize * 2; 
    
    // Create a new Vector that will store the old Hash Table 
    pair<string, vector<Sentence>> *newHashMap = 
    new pair<string, vector<Sentence>> [hashSize];    
    
    // Variables that temporarily store our old data
    string current; 
    int index;
    vector <Sentence> currSentence;

    for (int i = 0; i < oldSize; i++) {
        current = hashVector[i].first;
        currSentence = hashVector[i].second;

        if (not current.empty()) { // Avoid transferring empty slots
            index = hash<string>{}(current) % hashSize;

            if (not newHashMap[index].second.empty()) { // 2x Collision Case
                index = rehashCollision(index, newHashMap);
            }

            newHashMap[index].second = currSentence;
            newHashMap[index].first = current;
        }
    }

    delete [] hashVector;
    hashVector = newHashMap;
}

/*  name:       rehashCollision       
    purpose:    Handle collisions that occur during the rehashing process
    arguments:  A reference to an integer indicating the current index and a
                pointer to the new hash table being populated
    returns:    An integer representing the new index which is not occupied 
    effects:    None
*/
int hashMap::rehashCollision(int& index, 
                             pair<string, vector<Sentence>>* newHashMap) {
    while (not newHashMap[index % hashSize].second.empty()) {
        index++;    
    }  
     
    // Return the mod Size because we don't want to seg fault by accessing an 
    // index outside our array!
    return index % hashSize;
}

/*  name:       insertHash       
    purpose:    Insert a word with its associated Sentence struct into hash map
    arguments:  A string reference for the word to insert and a Sentence struct
                reference for the associated sentence information
    returns:    None    
    effects:    Modify the hash map by adding the word and its sentence info
*/
void hashMap::insertHash(string& word, Sentence& s) {

    if (loadFactor > 0.7) {
        rehash();
    }
    
    int index = hash<string>{}(word) % hashSize;
    // Check if pair is currently empty
    if (hashVector[index].second.empty()) {
        hashVector[index].second.push_back(s);
        hashVector[index].first = word;
    } else {
        if (word == hashVector[index].first) {
            hashVector[index].second.push_back(s);
        } else {
            linearProbe(index, word, s);
        }
    }
    
    // Increase the amount of keys and the load factor accordingly
    numKeys++;
    loadFactor = static_cast<float>(numKeys) / static_cast<float>(hashSize);
}

/*  name:       linearProbe       
    purpose:    Handle collision with linear probing
    arguments:  A reference to an integer indicating the current index, a 
                string reference for the word to insert and a Sentence struct
                reference for the associated sentence information
    returns:    None    
    effects:    Modify the hash map by adding the word and its sentence info
*/
void hashMap::linearProbe(int& index, string& word, Sentence& s) {
    
    // Vector is Not Empty and The Current index is not the word 
    while ((not hashVector[index].second.empty()) 
            and (hashVector[index].first != word)) {
        index++;
        
        // Wrap around when index is out of bound
        if (index >= hashSize) {
            index = index - hashSize;
        }

        // Index contains no values 
        if (hashVector[index].second.empty()) {
            hashVector[index].second.push_back(s);
            hashVector[index].first = word; 
        // Same Word Instance        
        } else if (hashVector[index].first == word){
            hashVector[index].second.push_back(s);
        }
    }
}

/*  name:       getHashVector       
    purpose:    Get the vector of Sentence structs associated with a specific 
                word in the hash map.
    arguments:  A string representing the key 
    returns:    A vector of Sentence structs corresponding to the provided word
    effects:    None
*/
vector <Sentence> hashMap::getHashVector(string word) {
    vector <Sentence> emptyCase;

    // Check if a given query, stripped of non-alpha characters is empty
    if (word.length() == 0) {
        return emptyCase;
    }

    int index = hash<string>{}(word) % hashSize;
    int temp = index;
    
    while (hashVector[index % hashSize].first != word) {
        index = (index + 1) % hashSize;
        if (index == temp) {
            return emptyCase; // Wraps around the entire array once so it 
                              // does not exist in our directory
        }
    }
    return hashVector[index % hashSize].second;
}

