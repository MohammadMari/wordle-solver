#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "guess.h"
#include "time.h"
#include "wordList.h"

using namespace std;

void addWords(wordList*& list);

int main()
{
	ifstream wordListFile;
	wordListFile.open("5letterwords.txt");

	srand(time(NULL));

	wordList* list = nullptr;

	addWords(list);	

	for (int i = 0; i < 7; i++)
	{
		guess guessWords;
		if (guessWords.guessWord(list))
		{
			cout << "Yay!" << endl;
			break;
		}
		guessWords.filterList(list);
	}


	wordListFile.close();
	return 0;
}


void addWords(wordList*& list)
{
	ifstream wordListFile;
	wordListFile.open("5letterwords.txt");

	while (!wordListFile.eof())
	{
		string line;
		getline(wordListFile, line);

		if (!list)
			list = new wordList(line);
		else
			list->push_back(line);
	}
}