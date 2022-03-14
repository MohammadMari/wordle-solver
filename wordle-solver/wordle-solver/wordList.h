#pragma once
#include "wordStrength.h"


class wordList
{
public:
	wordList(string word);
	void push_back(string word);
	void remove(wordStrength* word);
	
	wordStrength* head = nullptr;
};