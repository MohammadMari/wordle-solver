#pragma once
#include <string>

using namespace std;

class wordStrength
{
public:
	wordStrength() {};
	wordStrength(string word, wordStrength* parent = nullptr)
	{
		this->word = word;
		this->parent = parent;
		//calcWordStrength();
	}
	void calcWordStrength();
	string word;
	float strength = 0;
	wordStrength* child = nullptr;
	wordStrength* parent = nullptr;

};
