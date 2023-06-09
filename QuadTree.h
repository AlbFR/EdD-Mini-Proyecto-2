#ifndef QuadTree_h
#define QuadTree_h

#include "ADTQuadTree.h"
#include "Node.h"

class QuadTree: ADTQuadTree {
public:
	QuadTree(Boundary);
	int totalPoints();
	int totalNodes();
	void insert(Point p);
	void list();
	int countRegion(Point p, int d);
	int aggregateRegion(Point p, int d);

private:
	Node* root;
	int num_elements;

};

#endif

