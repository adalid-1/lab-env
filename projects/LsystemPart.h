#pragma once

#include "core/app.h"
#include "GLFW/glfw3.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class LsystemPart {

	char predecessor;
	std::string successor;

	float randomNr(float input, int range) {
		if (range == 0)
		{
			return input;
		}
		//don´t seed in here
		//srand((unsigned)time(0));
		// random nr between  and range
		float randomNumber = (rand() % range);
		return input + randomNumber;
	}

public:
	LsystemPart(char predecessor_, std::string successor_)
	{
		predecessor = predecessor_;
		successor = successor_;
	}

	std::string getSuccessor() { return successor; }
	char getPredecessor() { return predecessor; }

	void modifySuccessor(char newChar, int index) {
		successor[index] = newChar;
	}

	void SetPreAndSuc(char predecessor_, std::string successor_)
	{
		predecessor = predecessor_;
		successor = successor_;
	}

	bool operator==(LsystemPart& other) {
		return predecessor == other.getPredecessor() && successor == other.getSuccessor();
	}

	/*
	Part instructions for interpreter?
	*/

	//Input: S(set of selected sub - structures)
	//Output : P(set of generated productions)
	std::vector<LsystemPart> generateProductions(std::vector<LsystemPart> inputSet) {
		int n1 = inputSet.size();
		//create frequencyarray
		std::unordered_map<char, int> frequencyArray;
		for (int i = 0; i < n1; i++) {

			frequencyArray[inputSet[i].getPredecessor()] = frequencyArray[inputSet[i].getPredecessor()] + 1;
		}
		//Remove duplicates from vector
		std::vector<LsystemPart> inputSetUnique = inputSet;
		inputSetUnique.erase(std::unique(inputSetUnique.begin(), inputSetUnique.end()), inputSetUnique.end());
		int n2 = inputSet.size();
		for (int i = 0; i < n2; i++) {
			for (int letter = 0; letter <= inputSet[i].getSuccessor().length(); letter++)
			{
				int index = randomNr(0, n1);
				
				char predecessor = inputSet[index].getPredecessor();
				inputSetUnique[i].modifySuccessor(predecessor, letter);


			}
		}
		/*
		8 n2 ← size of S;
		9 for i = 0 to n2 - 1 do
		10 foreach letter s in S[i].successor do
		11	randomly select a predecessor s0 based on its probability F[S[i].predecessor] / n1;
		12	replace s in S[i].successor with s0;
		13	end
		14 end
		15
		P ← S;

		*/
		return inputSetUnique;
	}
};