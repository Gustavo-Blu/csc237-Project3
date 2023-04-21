#pragma once

#include <iostream>
#include <vector>
#include "WordData.h"
#include "WordList.h"

class WordSTLseq : public WordList
{
	std::vector<WordData> m_Words;

public:
	WordSTLseq();

	bool incMatch(std::string word);

	void parseIntoList(std::ifstream& infile);

	void printIteratively();

	void printRecursively();
	void printRecursivelyWorker(std::vector<WordData>::reverse_iterator curr);
};