#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "guess.h"
#include "time.h"

using namespace std;



int main()
{
	ifstream wordListFile;
	wordListFile.open("5letterwords.txt");

	srand(time(NULL));

	// TODO: Make linked list instead 
	vector<string> wordList;

	//we enter all words in the vector
	while (!wordListFile.eof())
	{
		string line;
		getline(wordListFile, line);
		wordList.push_back(line);
	}


	for (int i = 0; i < 7; i++)
	{
		guess guessWords;
		if (guessWords.guessWord(&wordList))
		{
			cout << "Yay!" << endl;
			break;
		}
		guessWords.filterList(wordList);
	}


	wordListFile.close();
	return 0;
}