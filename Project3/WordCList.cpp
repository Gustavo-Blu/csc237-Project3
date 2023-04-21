#include <iostream>
#include "WordCList.h"

WordCList::WordCList() : m_Words(*(new LinkedList<WordData>)) {}

bool WordCList::incMatch(std::string word)
{
	if (m_Words.empty())
		return false;

	if (word == m_Words.m_Tail->m_Data.getWord()) {
		m_Words.m_Tail->m_Data.incCount();
		return true;
	}

	Node<WordData>* curr = m_Words.m_Tail->m_Next;

	while (curr != m_Words.m_Tail)
	{
		if (curr->m_Data.getWord() == word) {
			//std::cout << "it was correct?";
			curr->m_Data.incCount();
			return true;
		}
		curr = curr->m_Next;
	}


	return false;

}

void WordCList::parseIntoList(std::ifstream& infile)
{
	std::string temp;
	infile.clear();
	infile.seekg(0);

	while (infile >> temp)
	{
		//std::cout << "in the while loop\n";
		if (!incMatch(temp))
		{
			//std::cout << "couldnt find the word\n";
			WordData* data = new WordData(temp, 1);
			m_Words.insert(*data);
		}
	}
}

void WordCList::printIteratively()
{
	std::cout << "---------------------------" << std::endl;
	std::cout << "|Circular  List  Iterator |" << std::endl;
	std::cout << "|Word         Occurrences |" << std::endl;
	std::cout << "---------------------------" << std::endl;

	ListIterator<WordData> lt(m_Words);

	for (lt.begin(); !lt.isLastNode(); lt.next())
		std::cout << " " << lt.value() << std::endl;

	std::cout << " " << lt.value() << std::endl;
}

void WordCList::printRecursively()
{
	std::cout << "---------------------------" << std::endl;
	std::cout << "|Circular  List  Recursive|" << std::endl;
	std::cout << "|Word         Occurrences |" << std::endl;
	std::cout << "---------------------------" << std::endl;

	ListIterator<WordData> data(m_Words);
	printRecursivelyWorker(data);
}

void WordCList::printRecursivelyWorker(ListIterator<WordData>& data)
{
	if (data.isLastNode())
	{
		std::cout << " " << data.value() << std::endl;
		return;
	}

	WordData temp = data.value();
	data.next();
	printRecursivelyWorker(data);

	std::cout << " " << temp << std::endl;

}
