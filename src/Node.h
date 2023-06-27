#ifndef Node_H
#define Node_H

#include <vector>
#include "utilities/Boundary.h"
#include "utilities/PointList.h"

struct UpdateInfo {
	long long population;
	unsigned nodes;
};

class Node {
public:
	Node();
    Node(Boundary *b, int l);
	Node(Point *ul, Point *br, int l);
    ~Node();
	int pointsAmount() const;
    int nodesAmount() const;
    UpdateInfo* insert(Point p);
    void list(std::vector<PointList> &v) const;
    int countRegion(Boundary *b) const;
	int agreggateRegion(Boundary *b) const;
	void showPoints() const;

private:
	// Distance from the node to the root
	int level_;
	PointList *pl_;
	unsigned num_points_;
	unsigned num_nodes_;
	long long population_;
	Boundary *boundary_;
    //Array of, at most, 4 child nodes who represent the upperleft, upperright, lowerleft and lowerright subareas respectively.
	Node *children_[4]; 
	void subdivide();

};

#endif