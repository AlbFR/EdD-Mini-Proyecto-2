#include "QuadTree.h"

QuadTree::QuadTree(Boundary b) {
	root = new Node(b);
}

int QuadTree::totalPoints() {
	return root->totalPoints();
}

int QuadTree::totalNodes() {
	return root->totalNodes();
}

void QuadTree::insert(Point p) {
	root->insert(p);
	num_elements++;
}

void QuadTree::list() {
	
}

int QuadTree::countRegion(Point p, int d) {
	Boundary *b = new Boundary(p, d);
	return root->countRegion(b);
}

int QuadTree::aggregateRegion(Point p, int d) {
	Boundary *b = new Boundary(p, d);
	return root->agreggateRegion(b);
}