#include <iostream>
#include "WordSTLSeq.h"

WordSTLseq::WordSTLseq()
{

}

bool WordSTLseq::incMatch(std::string word)
{
	if (m_Words.empty())
		return false;

	auto curr = m_Words.begin();

	while (curr != m_Words.end())
	{
		if (curr->getWord() == word)
		{
			curr->incCount();
			return true;
		}

		++curr;
	}


	return false;
}

void WordSTLseq::parseIntoList(std::ifstream& infile)
{
	std::string temp;

	infile.clear();
	infile.seekg(0);

	while (infile >> temp)
	{
		if (!incMatch(temp))
		{
			WordData* data = new WordData(temp, 1);
			m_Words.push_back(*data);
		}
	}
}

void WordSTLseq::printIteratively()
{
	std::cout << "-------------------------" << std::endl;
	std::cout << "|STL  Vector  Iterative |" << std::endl;
	std::cout << "|Word       Occurrences |" << std::endl;
	std::cout << "-------------------------" << std::endl;

	for (auto i = m_Words.begin(); i != m_Words.end(); ++i)
	{
		std::cout << " " << *i << std::endl;
	}
}

void WordSTLseq::printRecursively()
{
	std::vector<WordData>::reverse_iterator curr = m_Words.rbegin();
	printRecursivelyWorker(curr);
}

void WordSTLseq::printRecursivelyWorker(std::vector<WordData>::reverse_iterator curr)
{
	if (*curr == *m_Words.begin())
	{
		std::cout << "-------------------------" << std::endl;
		std::cout << "|STL  Vector  Recursive |" << std::endl;
		std::cout << "|Word       Occurrences |" << std::endl;
		std::cout << "-------------------------" << std::endl;

		std::cout << " " << *curr << std::endl;
		return;
	}

	std::vector<WordData>::reverse_iterator data = curr;
	printRecursivelyWorker(++curr);

	std::cout << " " << *data << std::endl;
}
