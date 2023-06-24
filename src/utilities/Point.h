#ifndef Point_h
#define Point_h

#include <iostream>
#include "PointData.h"

class Point {
	public:
		double x;
		double y;
		// This will store the data related to the cities
		PointData* pointdata;
		Point();
		Point(double x, double y);
		Point(PointData data);
		void print();
		void set(double x, double y);
		void setX(double x);
		void setY(double y);
		int compare(Point q) const;
		int compare(Point *q) const;
		void operator=(Point q);
		void print() const;
};

#endif