#ifndef QuadTree_h
#define QuadTree_h

#include "ADTQuadTree.h"
#include "Node.h"

class QuadTree: public ADTQuadTree {
public:
	QuadTree();
	QuadTree(Boundary *b);
	int totalPoints();
	int totalNodes();
	void insert(Point p);
	void list(std::vector<PointList> &v);
	int countRegion(Point p, int d);
	int aggregateRegion(Point p, int d);

private:
	Node* root;

};

#endif

