#include "QuadTree.h"

QuadTree::QuadTree() {
	std::cerr << "Cannot initializa a QuadTree withoud a boundary" << std::endl;
}

QuadTree::QuadTree(Boundary *b) {
	root = new Node(b, 0);
	num_points = 0;
}

int QuadTree::totalPoints() {
	return root->pointsAmount();
}

int QuadTree::totalNodes() {
	return root->nodesAmount();
}

void QuadTree::insert(Point p) {
	if(p.pointdata == nullptr)
		std::cerr << "The Points must contain information to be inserted in the QuadTree." << std::endl;

	root->insert(p);
	num_points++;
}

void QuadTree::list(std::vector<PointList> &v) {
	root->list(v);	
}

int QuadTree::countRegion(Point p, int d) {
	Boundary *b = new Boundary(&p, d);
	return root->countRegion(b);
}

int QuadTree::aggregateRegion(Point p, int d) {
	Boundary *b = new Boundary(&p, d);
	return root->agreggateRegion(b);
}