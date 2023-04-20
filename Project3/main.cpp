/****************************************************************/
/*   Author:         Dr. Spiegel                                */
/*   Course:         CIS237                                     */
/*   Filename:       app.cpp                                    */
/*   Purpose:        This Example inputs a string and demon-    */
/*                   strates how to store it using a subclass   */
/*                   of an abstract base class that incorporates*/
/*                   virtual functions to enable polymorphism   */
/*                   If a file name is                          */
/*                   input through the command line all of the  */
/*                   options will be done automatically for the */
/*                   first line of the file                     */
/****************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "WordList.h"
#include "WordDataList.h"
#include "WordCList.h"
// #include "WordData.h"        app only knows about the lists!

void displayMenu();
void printEverything(ifstream& inf, WordList* TheList, WordList* CList);


int main(int argc, char* argv[])
{
	std::ifstream inf;
	WordList* TheList = new WordDataList;
	WordList* CList = new WordCList;

	if (argc > 1) //if there was an input on the command line
	{
		inf.open(argv[1]); //try and open the file
		if (inf.fail())       //if the file does not open
		{                    //terminate
			std::cout << "Sorry, the file failed to open." << std::endl;
			return 0;
		}
		printEverything(inf, TheList, CList);
		return 0;
	}

	char selection;
	std::string fileName;

	cout << "Please enter a file name: ";
	getline(cin, fileName);

	inf.open(fileName.c_str());

	// TheList is a pointer to a WordList that is pointed to a WordList subclass
	TheList->parseIntoList(inf);
	CList->parseIntoList(inf);

	while (true)
	{
		displayMenu();
		std::cin >> selection;

		switch (selection)
		{
		case '1':
			TheList->printIteratively();
			break;
		case '2':
			TheList->printRecursively();
			break;
		case '3':
			TheList->printPtr();
			break;
		case '4':
			CList->printIteratively();
			break;
		case '5':
			CList->printRecursively();
			break;
		case '6':
			std::cout << "Goodbye" << std::endl;
			return 0;
		default:
			std::cout << "I cannot understand " << selection << ". Try again." << std::endl;
			break;
		}
	}
}

void displayMenu()
{
	std::cout << std::endl;
	std::cout << "How do you want to print your sentence elements?" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "1. Object Array Iterative" << std::endl;
	std::cout << "2. Object Array Recursive" << std::endl;
	std::cout << "3. Object Array Pointer Recursive" << std::endl;
	std::cout << "4. Circular List Iterator" << std::endl;
	std::cout << "5. Circular List Iterator" << std::endl;
	std::cout << "6. Quit" << std::endl;
}

void printEverything(ifstream& inf, WordList* TheList, WordList* CList)
{
	TheList->parseIntoList(inf);
	TheList->printIteratively();
	TheList->printRecursively();
	TheList->printPtr();

	CList->parseIntoList(inf);
	CList->printIteratively();
	CList->printRecursively();
}

