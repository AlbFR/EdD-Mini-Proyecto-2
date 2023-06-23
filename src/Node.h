#ifndef Node_H
#define Node_H

#include <vector>
#include "utilities/Boundary.h"
#include "utilities/Point.h"

class Node {
public:
    Node(Boundary *b);
	Node(Point *ul, Point *br);
    ~Node();
    int totalPoints() const;
    int totalNodes() const;
    void insert(Point &p);
	void insert(PointList *pl);
    void list(std::vector<PointList*> &v) const;
    int countRegion(Boundary *b) const;
	int agreggateRegion(Boundary *b) const;
	void showPoints() const;

private:
	PointList *pl_; // Linked List of Points
	Boundary *boundary_;
    //Array of, at most, 4 child nodes who represent the upperleft, upperright, lowerleft and lowerright subareas respectively.
	Node *children_[4]; 
	void subdivide();
	// void appendPoint(Point p);

};

#endif