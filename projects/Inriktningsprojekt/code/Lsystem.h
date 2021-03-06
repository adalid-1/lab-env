#pragma once
#include "core/app.h"
#include <string>
#include <vector>
#include <iostream>
#include "LsystemInterpreter.h";
#include "LsystemPart.h"
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "GraphicsNode.h"

struct Line {
	float start[3];
	float end[3];



};

class Lsystem {

	//========================
	//Private variables
	//========================

	float degrees;
	//Starting variable
	char axiom;
	//All variables
	char variables[2] = { 'A', 'B' };
	//Rules example: A ->  AB, B -> BA[B]
	std::vector <  LsystemPart  > rules;
	//Sentence built from the rules
	std::string sentence;
	//generations
	int n = 3;

	//========================
	//Tree building functions
	//========================

	//Checks if there is a rule for the given char
	std::string findRule(char c);
	//Builds a new sentence and replaces letters according to the rules given
	std::string applyRulesToSentence(std::string sentence);


	//Input: S(set of selected sub - structures)
//Output : P(set of generated productions)

	float randomNr(float input, int range);


public:
	//Constructors
	Lsystem();
	//Builds the sentence from the rules
	void buildTree(int n, int angleRandRange, int branchRandRange);
	//Getters
	std::string getSentence();
	std::vector<LsystemPart> getRules() {
		return rules;
	}

	LsystemInterpreter lSysInt; 
	void setRules(std::vector<LsystemPart> ruleSet);
	void setN(int newN);
	int getN();

	std::vector<LsystemPart> generateProductions(std::vector<LsystemPart> inputSet);
	void setupGraphicsNodes(std::vector<GraphicsNode>& nodeList, std::vector<GraphicsNode>& LeafList, GraphicsNode LeafNode, GraphicsNode Gnode, int randAngleRange, int randLengthRange);

};

/*
Commands
F(d)	Move forward a step of length d.
f(d)	Move  forward  a  step  of  length d without  drawing  a line.
+(δ)	Turn left by angle δ around the Yaxis.
-(δ)	Turn right by angle δ around the Yaxis.
&(δ)	Pitch down by angle δ around the Xaxis. 
^(δ)	Pitch upby angle δaround the Xaxis.
\(δ)	Roll left by angleδaround the Zaxis.
/(δ)	Roll rightby angleδaround the Zaxis.
[		Push the current state of the turtle to stack.
]		Pop the current state of the turtle from stack.
*/