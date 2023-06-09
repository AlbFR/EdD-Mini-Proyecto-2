#ifndef Node_H
#define Node_H

#include <vector>
#include "utilities.h"
#include "Point.h"

class Node {
public:
    Node(Boundary);
    ~Node();
    int totalPoints();
    int totalNodes();
    void insert(Point p);
    std::vector<Node> list();
    int countRegion();

private:
	Point *p_;
	// (Point a, Point b)
	Boundary boundary_;
    //Array of, at most, 4 child nodes who represent the upperleft, upperright, lowerleft and lowerright subareas respectively.
	Node* children_[4]; 
	void subdivide();

};

#endif