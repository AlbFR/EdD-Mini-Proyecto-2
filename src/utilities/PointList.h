#ifndef PointList_h
#define PointList_h

#include <vector>
#include "Point.h"

class PointList {
	public:
	 	double x, y;
		std::vector<Point> container;
		PointList();
		PointList(Point p);
		~PointList();
		int population();
		bool isEmpty();
		bool sameCoordsAs(Point p);
		long long append(Point p);
		// long long append(PointList *pl);
		Point top();
		void pop();
		unsigned size() const;
		void print() const;

	private:
		unsigned long long population_;
};

#endif