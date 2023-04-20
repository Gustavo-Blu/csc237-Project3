/***************************************
 *    File:    WordData.cpp            *
 *    Purpose:                         *
 *                                     *
 ***************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "WordData.h"

WordData::WordData(string word /*= ""*/, int count /*= 1*/)
{
	setWordData(word, count);
}

void WordData::setWord(std::string word)
{
	m_Word = word;
}

void WordData::setCount(int count)
{
	m_Count = count;
}

void WordData::setWordData(string word, int count)
{
	setWord(word);
	setCount(count);
}

std::string WordData::getWord() const
{
	return m_Word;
}

int WordData::getCount() const
{
	return m_Count;
}

void WordData::incCount(int inc /*= 1*/)
{
	m_Count += inc;
}

std::ostream& operator<<(ostream& output, const WordData& words)
{
	output << words.getWord() << "\t\t" << words.getCount();
	return output;
}
