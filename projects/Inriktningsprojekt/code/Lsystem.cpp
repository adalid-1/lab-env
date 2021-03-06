#include "Lsystem.h"






//Getters
std::string Lsystem::getSentence() {
	return sentence;
}

void Lsystem::setRules(std::vector<LsystemPart> ruleSet)
{
	rules = ruleSet;
}

void Lsystem::setN(int newN)
{
	n = newN;
}

int Lsystem::getN()
{
	return n;
}

std::vector<LsystemPart> Lsystem::generateProductions(std::vector<LsystemPart> inputSet)
{
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
		for (int letter = 0; letter <= inputSetUnique[i].getSuccessor().length(); letter++)
		{
			if (inputSetUnique[i].getSuccessor()[letter] == '[' || inputSetUnique[i].getSuccessor()[letter] == ']') {

			}
			else if (letter == 0) {
				inputSetUnique[i].modifySuccessor('A', letter);
			}
			else {

				int index = randomNr(0, n1);

				char predecessor = inputSet[index].getPredecessor();


				inputSetUnique[i].modifySuccessor(predecessor, letter);
			}

		}
	}

	return inputSetUnique;
}

void Lsystem::setupGraphicsNodes(std::vector<GraphicsNode>& nodeList, std::vector<GraphicsNode>& LeafList, GraphicsNode LeafNode, GraphicsNode Gnode, int randAngleRange, int randLengthRange)
{
	randAngleRange = 10;
	//randLengthRange = 0;
	//srand((unsigned)time(0));
	nodeList.clear();
	LeafList.clear();
	lSysInt.segmentList.clear();
	// if pressed we compile the shaders
	buildTree(n, randAngleRange, randLengthRange);


	for (int i = 0; i <lSysInt.segmentList.size(); i++) {

		//std::cout << treeGenerator.lSysInt.positions[i].getX() << " " << treeGenerator.lSysInt.positions[i].getY() * 2.f << " " << treeGenerator.lSysInt.positions[i].getZ() << std::endl;
		GraphicsNode temp = GraphicsNode();


		temp.getPtrsFromOtherNode(Gnode);
		
		//temp.setup();

		if (lSysInt.segmentList[i].hasLeaf) {
			GraphicsNode tempLeaf = GraphicsNode();
			tempLeaf.getPtrsFromOtherNode(LeafNode);
			//tempLeaf.transform = lSysInt.segmentList[i].transform;
			tempLeaf.transform.setPosition(lSysInt.segmentList[i].position1);
			std::cout << "x: " << lSysInt.segmentList[i].position1.getX() << "y: " << lSysInt.segmentList[i].position1.getY() << "z: " << lSysInt.segmentList[i].position1.getZ() << endl;
			Matrix4D scale = Matrix4D();
			scale.set(15, 15.f);
			//scale.set(5,1/ 15.f);
			//scale.set(10, 1 / 5.f);
			LeafNode.transform = LeafNode.transform * scale;
			tempLeaf.transform = tempLeaf.transform * scale;
			std::cout << "let there be  leaves!" << std::endl;
			LeafList.push_back(tempLeaf);
		}

		//treeGenerator.lSysInt.posRot[i].set(0, 0.5);
		//treeGenerator.lSysInt.segmentList[i].transform.setPosition(treeGenerator.lSysInt.positions[i]);
		//treeGenerator.lSysInt.segmentList[i].transform = treeGenerator.lSysInt.segmentList[i].transform * scalingMat;
		temp.transform = lSysInt.segmentList[i].transform;
		//temp.transform.setPosition(treeGenerator.lSysInt.positions[i]);
		nodeList.push_back(temp);

		
		
	}


	std::cout << (getSentence()) << std::endl;




	for (int i = 0; i < getRules().size(); i++) {

		std::cout << "Rule nr: " << i << " " << getRules()[i].getSuccessor() << " " << getRules()[i].getPredecessor() << std::endl;
	}

}

float Lsystem::randomNr(float input, int range)
{
	if (range == 0)
	{
		return input;
	}

	float randomNumber = (rand() % range);
	return input + randomNumber;
}

Lsystem::Lsystem() {
	

	axiom = 'A';
	sentence = axiom;
	

	rules;

	//rules = { { "A", "ABA" }, { "B", "BBB" }, {"C", "CA" } };
	//Rules: (A->ABA) (B->BBB)
}

std::string Lsystem::findRule(char c)
{
	for (int i = 0; i < rules.size(); i++)
	{
		if (c == rules[i].getPredecessor())
		{
			//returns rule if found
			return rules[i].getSuccessor();
		}
	}
	//Otherwise "noRule"
	return "noRule";
}

//Builds a new sentence and replaces letters according to the rules given
std::string Lsystem::applyRulesToSentence(std::string sentence)
{

	std::string newSentence = "";
	for (int i = 0; i < sentence.length(); i++)
	{
		char c = sentence[i];
		std::string rule = findRule(c);

		if (rule != "noRule")
		{
			newSentence += rule;
		}
		else
		{
			newSentence += sentence[i];
		}
	}
	return newSentence;
}

void Lsystem::buildTree(int n, int angleRandRange, int branchRandRange )
{
	
	sentence = axiom;
	//makeBranches();
	for (int i = 0; i < n; i++)
	{
		sentence = applyRulesToSentence(sentence);
	}

	lSysInt.setSentence(sentence);
	lSysInt.calculatePoints(angleRandRange, branchRandRange);
}
