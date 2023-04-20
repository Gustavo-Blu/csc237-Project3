#pragma once

/****************************************************************/
/*   Filename:       WordData.h                                 */
/*   Purpose:        The Only Addition i made to this file was  */
/*                   an overloading of the << operator.         */
/****************************************************************/

#ifndef WORDDATA_H
#define WORDDATA_H
#include <iostream>
#include <string>

using namespace std;

class WordData {

private:
	//variables
	string m_Word;
	int m_Count;

public:

	//Constructor
	WordData(string word = "", int count = 1);

	//Sets
	void setWord(string word);
	void setCount(int count);

	//Set Whole WordData Object
	void setWordData(string word, int count);

	//Gets
	string getWord() const;
	int getCount() const;

	//Increment
	void incCount(int inc = 1);

	bool operator==(const WordData& data);
};

ostream& operator<<(ostream& output, const WordData& words);

#endif