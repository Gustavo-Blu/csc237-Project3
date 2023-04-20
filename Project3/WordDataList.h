#pragma once
// File: WordDataList.h
// Container of WordData objects. 
// Printing can be iterative or recursive. 


#ifndef WORDDATALIST_H
#define WORDDATALIST_H
#include <string>
#include "WordList.h"
#include "WordData.h"

class WordDataList : public WordList {
private:
	WordData m_TheWords[10];
	int m_NumWords;

	// Look for a match and increment if found
	bool incMatch(std::string temp);

	// Function to actually perform recursive print
	void printRecursivelyWorker(int numWords);

	// Function to actually perform recursive print using pointer
	void printPtrWorker(int numWords);


public:
	WordDataList();

	// Put a string of strings into the list object
	virtual void parseIntoList(std::ifstream& inf);

	// Print the data iteratively
	virtual void printIteratively();

	// Print the data recursively
	virtual void printRecursively();

	// Print the data recursively with a pointer
	virtual void printPtr();

};

#endif