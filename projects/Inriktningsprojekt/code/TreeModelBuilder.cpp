#include "TreeModelBuilder.h"

void TreeModelBuilder::buildTreeModel(std::vector<Segment> treeSegments, bool shadedSmooth)
{
	indices.clear();
	vertices.clear();
	//Gör en cylinder för varje segment och pusha back den i vertices 
	for (int i = 0; i < treeSegments.size(); i++) {
		cylinder = new Cylinder(treeSegments[i].thickness , treeSegments[i].thickness, treeSegments[i].length, 6, 6, shadedSmooth);
		cylinder->formatData(indices, vertices, i, treeSegments[i].transform);

		delete cylinder;


	}
}
