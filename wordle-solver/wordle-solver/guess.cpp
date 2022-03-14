#include "guess.h"
#include "wordList.h"
#include <iostream>

bool guess::guessWord(wordList *wordList)
{

	// TODO: Find a better word to guess, a word that doesn't have many repeat charcters and all.
	//		 Maybe sort vector by best word to guess first? (you want to use a linked list if you do this)
	//		 Also a better way to get the green and yellow characters would be nice.


	string wordToGuess = wordList->head->word;

	cout << "Guess: " << wordToGuess << endl;

	char input;
	cout << "Correct word?(Y/N): ";

	cin >> input;

	if (tolower(input) == 'y')
		return true;

	string green;
	cout << "Enter green letters and index: ";
	cin.ignore();
	getline(cin, green);

	vector<char> greenChars;
	vector<int> greenInt;

	//we assume inputted info is formatted correctly, we just check to see if its a number or letter, and then we just add it to a vector
	for (int i = 0; i < green.size(); i++)
	{
		if (isalpha(green.at(i)))
			greenChars.push_back(green.at(i));
		else if (isdigit(green.at(i)))
			greenInt.push_back(green.at(i) - 48);
	}


	//because they should be in the right order, we can just push back the letter and index into our vector like this
	for (int i = 0; i < greenChars.size(); i++)
		absoluteLetter.push_back(letterPos(greenChars.at(i), greenInt.at(i)));


	//do the same thing for yellow.
	vector<char> yellowChars;
	vector<int> yellowInt;

	string yellow;
	cout << "Enter yellow letters seperated by space: ";
	getline(cin, yellow);


	for (int i = 0; i < yellow.size(); i++)
	{
		if (isalpha(yellow.at(i)))
			yellowChars.push_back(yellow.at(i));
		else if (isdigit(yellow.at(i)))
			yellowInt.push_back(yellow.at(i) - 48);
	}

	for (int i = 0; i < yellowChars.size(); i++)
		inWordLetter.push_back(letterPos(yellowChars.at(i), yellowInt.at(i)));


	//we get all the letters that are actually in our word (yellow and green letters)
	vector<char> foundLetters;

	for (letterPos inWord : inWordLetter)
		foundLetters.push_back(inWord.letter);

	for (letterPos inWord : absoluteLetter)
		foundLetters.push_back(inWord.letter);


	//now we make a list of all the wrong letters.
	for (int i = 0; i < wordToGuess.size(); i++)
	{
		char curLetter = wordToGuess.at(i);

		bool found = false;
		for (char letter : foundLetters)
		{
			if (curLetter != letter)
				continue;
			found = true;
		}

		if (!found)
			wrongLetters.push_back(wordToGuess.at(i));
	}


	return false;
}


void guess::filterList(wordList*& list)
{
	// TODO: Fix clearing things with repeat letters.
	//		 Ex. You guess a word with two of the same letters, 
	//			 only one is in the word, we need to get rid of all 
	//			 words with two or more of that letter.

	//first we loop through all the green letters we found
	for (letterPos green : absoluteLetter)
	{

		wordStrength* curWordNode = list->head;

		while (curWordNode->child) 
		{
			string curWord = curWordNode->word;

			//some of the lists i've used had weird characters randomly so im making sure that the word is all good.
			if (curWord.size() < 5)
			{
				wordStrength* remove = curWordNode;
				curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
				list->remove(remove);
				continue;
			}

			char curLetter = curWord.at(green.pos);

			// green pos has an index and a character
			// we know that this character is for sure in this position
			// for all words that dont have this charcter in this position, we get rid of.
			if (green.letter != curLetter)
			{
				wordStrength* remove = curWordNode;
				curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
				list->remove(remove);
				continue;
			}
			
			curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
		}
		
	}

	// loop through yellow letters
	for (letterPos yellow : inWordLetter)
	{
		wordStrength* curWordNode = list->head;

		while (curWordNode->child)
		{
			string curWord = curWordNode->word;
			if (curWord.size() < 5) // get rid of the bad words in our list
			{
				wordStrength* remove = curWordNode;
				curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
				list->remove(remove);
				continue;
			}

			// if a character is yellow, its in the word but not at this position
			// here we are getting rid of every word that has that character in the same position
			if (yellow.letter == curWord.at(yellow.pos))
			{
				wordStrength* remove = curWordNode;
				curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
				list->remove(remove);
				continue;
			}


			// here we get rid of all words that don't have this letter
			bool found = false;

			for (int j = 0; j < curWord.size(); j++)
			{
				if (curWord.at(j) == yellow.letter)
					found = true;
			}

			if (!found)
			{
				wordStrength* remove = curWordNode;
				curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
				list->remove(remove);
				continue;
			}

			curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
		}
	}


	// we loop through all the characters that aren't in this word
	for (char wrong : wrongLetters)
	{
		wordStrength* curWordNode = list->head;

		while (curWordNode->child)
		{
			string curWord = curWordNode->word;

			if (curWord.size() < 5) // make sure word is good
			{
				wordStrength* remove = curWordNode;
				curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
				list->remove(remove);
				continue;
			}


			bool removed = false;
			// we loop through the word, we check and see if this letter is in the word, if it is, we get rid of it.
			for (int j = 0; j < curWord.size(); j++)
			{
				if (wrong == curWord.at(j))
				{
					wordStrength* remove = curWordNode;
					curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
					list->remove(remove);
					removed = true;
					break;
				}
			}

			if(!removed)
				curWordNode = curWordNode->child ? curWordNode->child : curWordNode;
		}
	}
}