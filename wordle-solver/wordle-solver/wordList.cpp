#include "wordList.h"
#include <iostream>



wordList::wordList(string word)
{
	if (!head)
		head = new wordStrength(word);
}

void wordList::push_back(string word)
{
	wordStrength* parent = head;

	while (parent->child)
		parent = parent->child;

	parent->child = new wordStrength(word, parent);
}

void wordList::remove(wordStrength* word)
{
	if (word == head)
	{
		wordStrength* temp = word;
		head = word->child;
		head->parent = nullptr;
		free(temp);
	}
	else
	{
		word->parent->child = word->child;
		word->child->parent = word->parent;
		free(word);
	}
}
