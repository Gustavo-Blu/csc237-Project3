#pragma once
// File: WordList.h
// Abstract base class for containers of word data
// Known subclasses:
//      WordDataList
// Coming soon: ParallelArrayWordList, WordVectorList, ...

#ifndef WORDLIST_H
#define WORDLIST_H
#include <fstream>
#include <string>

class WordList {
public:

	// Place the line of text into the data structure
	virtual void parseIntoList(std::ifstream& infile) = 0;

	// Print the data iteratively
	virtual void printIteratively() = 0;

	// Print the data recursively
	virtual void printRecursively() = 0;

	// Print the data recursively with a pointer
	virtual void printPtr() {}   // not pure virtual; why?

};

#endif