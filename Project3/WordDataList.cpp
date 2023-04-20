// File: WordDataList.cpp
// Container of WordData objects 
//   Implementations of member functions including inherited pure virtual functions.

#include <sstream>
#include <iostream>
#include "WordDataList.h"

WordDataList::WordDataList()
{
	m_NumWords = 0;
}

bool WordDataList::incMatch(std::string temp)
{
	for (int i = 0; i < m_NumWords; i++)
	{
		if (temp == m_TheWords[i].getWord())
		{
			m_TheWords[i].incCount();
			return true;
		}
	}
	return false;
}

void WordDataList::parseIntoList(std::ifstream& inf)
{
	std::string temp;

	while (inf >> temp)
	{
		if (!incMatch(temp) && m_NumWords < 10)
		{
			m_TheWords[m_NumWords].setWord(temp);
			m_TheWords[m_NumWords++].setCount(1);
		}
	}
}

void WordDataList::printIteratively()
{
	std::cout << "--------------------------" << std::endl;
	std::cout << "|Object  Array  Iterative |" << std::endl;
	std::cout << "|Word         Occurrences |" << std::endl;
	std::cout << "--------------------------" << std::endl;

	for (int i = 0; i < m_NumWords; i++)
		std::cout << " " << m_TheWords[i] << std::endl;
}

void WordDataList::printRecursivelyWorker(int numWords)
{
	if (numWords == 1)
	{
		std::cout << "--------------------------" << std::endl;
		std::cout << "|Object  Array  Iterative |" << std::endl;
		std::cout << "|Word         Occurrences |" << std::endl;
		std::cout << "--------------------------" << std::endl;
		std::cout << " " << m_TheWords[numWords - 1] << std::endl;
		return;
	}

	printRecursivelyWorker(numWords - 1);
	std::cout << " " << m_TheWords[numWords - 1] << std::endl;
}

void WordDataList::printRecursively()
{
	printRecursivelyWorker(m_NumWords);
}

void WordDataList::printPtrWorker(int numWords)
{
	if (!numWords)
	{
		std::cout << "--------------------------" << std::endl;
		std::cout << "|Object  Array  Iterative |" << std::endl;
		std::cout << "|Word         Occurrences |" << std::endl;
		std::cout << "--------------------------" << std::endl;
		return;
	}

	printPtrWorker(numWords - 1);
	std::cout << " " << *(m_TheWords + (numWords - 1)) << std::endl;
}

void WordDataList::printPtr()
{
	printPtrWorker(m_NumWords);
}




