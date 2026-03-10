# Project Gerp!

**Project Gerp!** is a high-performance information retrieval system utilized to index large directories of files and respond to user queries in the linux environment. The program mimics the functionality of the Unix ```grep``` command but utilizes a pre-indexed data structure to provide $O(1)$ word lookups.

---
## Features

**Efficient Indexing:** Traverses complex directory trees to index all file contents
**Fast Querying**: Uses a custom Hash Map implementation to achieve constant time complexity for word searches.
**Flexible Search:** Supports both case-sensitive and case-insensitive (```@i```) queries.
**Dynamic Output:** Allows users to redirect query results to different files on the fly using the ```@f``` command.

---

## Architectural Overview
The system is built upon a nested data structure designed for both speed and storage efficiency:
### 1. File Content Storage
The program stores the entirety of the directory's text in a nested vector structure:
  *  ```vector < vector < pair <string,bool> > > ```
    *  The outer vector represents the files
    *  The inner vector represents the lines within a specfied file
    *  Our lowest data structure contains a pair. The first component is a string that represents string of a unique line Content of a particular file. The boolean variable represents whether or not the line has been seen or not.

### 2. The Hash Map
A custom ```hash``` map indexes every unique word:

**Key:** A string (stripped of non-alphanumeric characters and lowercased).
**Value:** A ```vector``` of ```Sentence``` structs, which act as "coordinates" (file index and line index) to the actual text.

Note that we use Linear Probing for handling hash collisions.

---

## Getting Started 
### Compilation
To build the executable, run:
```make gerp```
### Usage
Run the program by providing the input directory and an initial output file:
```./gerp inputDirectory outputFile ```
### Query Commands
Once running, the program accepts the following commands:
 * ```word:``` Performs a case-sensitive search for "word".
 * ```@i word``` or ```@insensitive word```: Performs a case-insensitive search.
 * ```@f newOutputFile```: Switches the current output stream to a new file.
 * ```@q``` or ```@quit```: Exits the program.
---
There is an additional ```README``` file in the folder depicting the specifications of each function
