#ifndef PointList_h
#define PointList_h

#include <vector>
#include "Point.h"

class PointList {
	public:
	 	double x, y;
		std::vector<Point*> container;
		PointList();
		PointList(Point *p);
		int population();
		bool isEmpty();
		bool sameCoordsAs(Point p);
		void append(Point *p);
		void append(PointList *pl);
		Point* top();
		void pop();
		unsigned size() const;
		void print() const;

	private:
		unsigned population_;
};

#endif