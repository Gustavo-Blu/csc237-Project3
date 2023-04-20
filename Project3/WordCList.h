#pragma once

#include <iostream>
#include "WordData.h"
#include "LinkedList.h"
#include "WordList.h"

class WordCList : public WordList
{
private:
	LinkedList<WordData> m_Words;
public:
	WordCList();

	bool incMatch(std::string word);

	void parseIntoList(std::ifstream& infile);

	void printIteratively();

	void printRecursively();
	void printRecursivelyWorker(ListIterator<WordData>& curr);
};