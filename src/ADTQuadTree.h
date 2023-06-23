#ifndef ADTQuadTree_h
#define ADTQuadTree_h

#include <vector>
#include "utilities/Point.h"
#include "utilities/PointData.h"

class ADTQuadTree {
	
	// Returns amount of points saved in the QuadTree
	virtual int totalPoints() = 0;

	// Returns the total amount of nodes, white ones and black ones
	virtual int totalNodes() = 0;

	// Inserts a new point p in the QuadTree, associating it with the given information
	virtual void insert(Point p) = 0;

	// Returns a container (as parameter) with every PointList in QuadTree which has
	// every Point in QuadTree, for each value returns
	// its coordinates and its associated value
	virtual void list(std::vector<PointList*> &v) = 0;

	// Returns the amount of points in a certain region of the plane, with
	// p as the center and d as the radius
	virtual int countRegion(Point p, int d) = 0;

	// Returns the estimated population in a certain region of the plane
	// with p as the center and d as the radius
	virtual int aggregateRegion(Point p, int d) = 0;	

};

#endif