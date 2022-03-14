#pragma once
#include <vector>
#include <string>

using namespace std;

struct letterPos
{
	letterPos(char letter, int pos)
	{
		this->letter = letter;
		this->pos = pos;
	}

	char letter;
	int pos = -1;
};


class guess
{
public:
	vector<letterPos> absoluteLetter; // green letters
	vector<letterPos> inWordLetter; // yellow letters
	vector<char> wrongLetters; // gray letters

	bool guessWord(vector<string>* wordList);
	void filterList(vector<string>& wordList);
};