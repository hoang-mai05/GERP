/*
    main.cpp
    Hoang Mai Stacey Liang

    COMP 15 HW 6 Gerp

    main will serve as the boilerplate for our Gerp implementation.
    In other words, main takes a given directory, indexes them, and does
    various functions given a user input query.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "gerp.h"

using namespace std;

/*  name:           main()
    purpose:        File Driver for the Gerp Functionalities
    arguments:      Argument line and number of Arguments
    return:         0 if main's implementation is correct
    effects:        Exit function if arguments from the exectuble are Incorrect
*/
int main(int argc, char *argv[])
{
    /* Make sure that the number of arguments from the executable are correct */
    if (argc < 3 or argc > 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        exit(EXIT_FAILURE);
    }

    string directory = argv[1];
    string output = argv[2];

    Gerp g;
    g.run(directory, output);

    return 0;
}
