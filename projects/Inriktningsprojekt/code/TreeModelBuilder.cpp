#include "TreeModelBuilder.h"

void TreeModelBuilder::buildTreeModel(std::vector<Segment> treeSegments)
{
	indices.clear();
	vertices.clear();
	//Gör en cylinder för varje segment och pusha back den i vertices 
	for (int i = 0; i < treeSegments.size(); i++) {
		cylinder = new Cylinder(treeSegments[i].thickness, treeSegments[i].thickness, treeSegments[i].length, 6, 6, true);
		cylinder->formatData(indices, vertices, (i * 504));

		//indices måste bli indices + sissta indexet i indices ??

		/*
		//Fixa positionen så med transform * pos
		gl_Position = projection * view * transform * vec4(pos, 1);
		FragPos = vec3(transform * vec4(pos, 1));
	


		//Rotera normaler så här
		vs_normal = mat3(transform) * vertex_normal;
		
		
		*/



		delete cylinder;


	}
}
