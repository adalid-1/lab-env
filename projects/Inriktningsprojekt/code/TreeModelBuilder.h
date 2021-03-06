
#include "core/app.h"
#include <iostream>
#include <vector>
#include "Cylinder.h"
#include "LsystemInterpreter.h"

class TreeModelBuilder {
	Cylinder* cylinder;
	public:

	std::vector<float> vertices;
	std::vector<GLuint> indices; 

	void buildTreeModel(std::vector<Segment> treeSegments);

};