#ifndef Node_H
#define Node_H

#include <vector>
#include "utilities/Boundary.h"
#include "utilities/PointList.h"

class Node {
public:
	Node();
    Node(Boundary *b, int l);
	Node(Point *ul, Point *br, int l);
    ~Node();
    int totalPoints() const;
    int totalNodes() const;
    void insert(Point *p);
	// void insert(PointList *pl);
    void list(std::vector<PointList*> &v) const;
    int countRegion(Boundary *b) const;
	int agreggateRegion(Boundary *b) const;
	void showPoints() const;

private:
	int level_;
	PointList *pl_; // Linked List of Points
	Boundary *boundary_;
    //Array of, at most, 4 child nodes who represent the upperleft, upperright, lowerleft and lowerright subareas respectively.
	Node *children_[4]; 
	void subdivide();
	// void appendPoint(Point p);

};

#endif