#ifndef QuadTree_h
#define QuadTree_h

#include "ADTQuadTree.h"

class QuadTree : ADTQuadTree{
public:
	int totalPoints();
	int totalNodes();
	void insert(Point p, int data);
	void list();
	int countRegion(Point p, int d);
	int aggregateRegion(Point p, int d);

private:
	Node* root;
	int num_elements;

};

#endif

