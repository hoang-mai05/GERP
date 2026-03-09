/*
    unit_tests.h
    Hoang Mai, Stacey Liang
    11/10/2024
    
    CS 15 HW 6 Gerp

    Test the class implementations for processing.cpp to see if the prodcued 
    result matches expected result
*/

#include <cassert>
#include <string>
#include "processing.h"
#include "gerp.h"
#include "hashMap.h"
#include <iostream>
#include "sentence.h"
#include <functional>

using namespace std;

////////////////////// Test Function: stripNonAlphaNum ////////////////////

// /* Test checks a normal word without Non-AlphaNumeric Characters */
// void normal_checker() {
//     string normal = "Computer";

//     string temp = stripNonAlphaNum(normal);

//     assert(temp == "Computer");
// }

// /* Test checks removing just front non-alphanumeric characters */
// void front_checker() {
//     string front = "&#@*(!&#(*))Computer";

//     string temp = stripNonAlphaNum(front);

//     assert(temp == "Computer");
// }

// /*  Test checks removing just the back non-alphanumeric characters  */
// void back_checker() {
//     string back = "Computer!&*@(#*&)";

//     string temp = stripNonAlphaNum(back);

//     assert(temp == "Computer");
// }

// /*  Test checks general case of removing front and back characters  */
// void general_checker() {
//     string general = "!&(*@#)Computer!@&*()";

//     string temp = stripNonAlphaNum(general);

//     assert(temp == "Computer");
// }

// /*  Test makes sure non-Alpha in between remain in between */
// void between_checker() {
//     string between = "!@#CS-15!@&()";

//     string temp = stripNonAlphaNum(between);

//     assert(temp == "CS-15");
// }

// /* Test checks only non-alpha characters */
// void only_nonalpha_checker() {
//     string nonalpha = "!@#";

//     string temp = stripNonAlphaNum(nonalpha);

//     cout << temp << endl;
//     assert(temp == "");
// }

void singleChar() {
    string nonalpha = "i!@#";

    string temp = stripNonAlphaNum(nonalpha);

    assert(temp == "i");
}


// ////////////////////// Test Function: traverseDirectory //////////////////

// /*  Test traverseDirectory on a directory containing only files */
// void onlyFiles() {
//     traverseDirectory("onlyFiles");
// }

// /*  Test traverseDirectory on a directory containing only subdirectories */
// void onlySubDirectories() {
//     traverseDirectory("onlySubDir");
// }

// /*  Test traverseDirectory on an empty a directory*/
// void empty() {
//     traverseDirectory("empty");
// }

// /*  Test traverseDirectory on tinyData*/
// void tinyData() {
//     traverseDirectory("tinyData");
// }

// /*  Test traverseDirectory on smallGutenberg*/
// void smallGutenberg() {
//     traverseDirectory("smallGutenberg");
// }

// /*  Test traverseDirectory on mediumGutenberg*/
// void mediumGutenberg() {
//     traverseDirectory("mediumGutenberg");
// }

// //////////////////////////////////////////

// void test_storing_file_content() {
//     Gerp g;
//     g.processFiles("tinyData");
//     vector<vector<string>> test = g.get_vectorFiles();

//     assert(test[1][1] == "i wish this was gibberish");
//     assert(test[4][0] == "tinyData/a/you");
//     assert(test[3][4] == "about");
//     assert(test[3][2] == "");
// }

// void test_hash() {
//     hashMap hm;
//     Sentence s;
//     string input[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m",
//     "n","o","p","q","r","s","t","u","v","w","x","y","z"};    

    
//     for (int i=0; i < 26; i++) {
//         cout << input[i] << "  ";
//         cout << hash<string>{}(input[i]) % hm.gethashSize() << endl;
//     }
//     cout << endl;

//     // hm.insertHash(input[0], s);
//     // hm.insertHash(input[1], s);
//     // hm.insertHash(input[2], s);
//     // hm.insertHash(input[3], s);
//     // hm.insertHash(input[4], s);
//     // hm.insertHash(input[5], s);
//     // hm.insertHash(input[6], s);
//     // hm.insertHash(input[7], s);
//     // // hm.insertHash(input[8], s);

//     for (int i=0; i < 26; i++) {
//         hm.insertHash(input[i], s);
//     }

//     hm.printHashMap();
// }

// void test_hash_tinyData() {
//     Gerp g;
//     g.processFiles("tinyData");

//     g.gethash().printHashMap();
// }



