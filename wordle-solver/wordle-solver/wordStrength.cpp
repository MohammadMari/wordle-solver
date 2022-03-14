#include "wordStrength.h"

//https://www.lexico.com/explore/which-letters-are-used-most

#define E 11.1607
#define A 8.4966
#define R 7.5809
#define I 7.5448
#define O 7.1635 
#define T 6.9509 
#define N 6.6544 
#define S 5.7351 
#define L 5.4893 
#define C 4.5388 
#define U 3.6308 
#define D 3.3844
#define P 3.1671
#define M 3.0129
#define H 3.0034
#define G 2.4705
#define B 2.0720
#define F 1.8121
#define Y 1.7779
#define W 1.2899
#define K 1.1016
#define V 1.0074
#define X 0.2902
#define Z 0.2722
#define J 0.1965
#define Q 0.1962


float letterStrength(char letter)
{

	float letStr[26] = { A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z };
	return letStr[letter - 97];
}

void wordStrength::calcWordStrength()
{
	strength = 0;

	for (int i = 0; i < word.size(); i++)
	{
		for (int j = 0; j < word.size(); j++)
		{
			if (j == i)
				continue;

			if (word.at(i) == word.at(j))
				strength -= letterStrength(word.at(i));
		}

		strength += letterStrength(word.at(i));
	}
}
