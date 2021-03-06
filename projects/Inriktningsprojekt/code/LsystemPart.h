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

	void SetSuccessor(std::string modified) {
		successor = modified;
	}

	void SetPreAndSuc(char predecessor_, std::string successor_)
	{
		predecessor = predecessor_;
		successor = successor_;
	}

	bool operator==(LsystemPart& other) {
		return predecessor == other.getPredecessor() && successor == other.getSuccessor();
	}



};